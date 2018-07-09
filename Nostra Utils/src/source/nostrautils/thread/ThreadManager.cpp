#include "nostrautils/thread/ThreadManager.hpp"
#include "nostrautils/dat_alg/Vector.hpp"
#include "nostrautils/dat_alg/BinaryHeap.hpp"
#include "nostrautils/dat_alg/ObjectPool.hpp"
#include "nostrautils/core/Assertions.hpp"
#include "nostrautils/dat_alg/HashMap.hpp"

#include <iostream>

namespace NOU::NOU_THREAD
{
	constexpr typename ThreadManager::Priority ThreadManager::TaskInformation::INVALID_ID;

	constexpr uint32 ThreadManager::DEFAULT_THREAD_COUNT;

	constexpr sizeType ThreadManager::DEFAULT_TASK_CAPACITY;

	ThreadManager::TaskInformation::TaskInformation(Priority id) :
		m_id(id)
	{}

	ThreadManager::TaskInformation::TaskInformation() :
		m_id(INVALID_ID)
	{}

	void ThreadManager::threadLoop(ThreadManager *threadManager, ThreadDataBundle **threadDataPtr, 
		Mutex *startupMutex, ConditionVariable *startupVariable, boolean *startupDone)
	{
		ThreadDataBundle *threadData;

		{
			Lock lock(*startupMutex);

			threadData = *threadDataPtr;
		}

		*startupDone = true;
		startupVariable->notifyAll();

		while (!(threadManager->m_shouldShutdown))
		{
			UniqueLock lock(threadData->m_mutex);
			threadData->m_variable.wait(lock, [threadData, threadManager]() 
			{ 
				//wait for new task or thread manager shutdown
				return threadData->m_taskReady || threadManager->m_shouldShutdown; 
			});

			//if the manager should shutdown, the method will be stopped from looping.
			if (threadManager->m_shouldShutdown)
				return;

			internal::AbstractTask *t = threadData->m_taskHandlerPair.task;

			threadData->m_taskHandlerPair.task->execute();

			//Set to false for the next iteration, must be set to true by the thread manager
			threadData->m_taskReady = false;

			threadManager->giveBackThread(*threadData);
		}
	}



	ThreadManager::ThreadDataBundle::ThreadDataBundle(ThreadWrapper &&thread) :
		m_thread(NOU_CORE::move(thread)),
		m_taskHandlerPair(nullptr, nullptr), //m_taskHandlerPair will be initialized later
		m_taskReady(false)
	{}

	ThreadManager::ThreadDataBundle::ThreadDataBundle(ThreadDataBundle&& tdb) :
		m_thread(NOU_CORE::move(tdb.m_thread)),
		m_taskHandlerPair(NOU_CORE::move(tdb.m_taskHandlerPair)),
		m_taskReady(tdb.m_taskReady)
	{}

	NOU_FUNC ThreadManager& getThreadManager()
	{
		return ThreadManager::get();
	}

	ThreadManager& ThreadManager::get()
	{
		static ThreadManager instance;
		return instance;
	}

	typename ThreadManager::ObjectPoolPtr<typename ThreadManager::ThreadDataBundle> 
		ThreadManager::makeThreadPool()
	{
		// -1, b/c that is the main execution thread
		sizeType threadPoolCapacity = ThreadWrapper::maxThreads() == 0 ? DEFAULT_THREAD_COUNT - 1 : 
			ThreadWrapper::maxThreads() - 1;

		//since DEFAULT_THREAD_COUNT is 2, the threadPoolCapacity will never be smaller than 2
		threadPoolCapacity = NOU_CORE::max<sizeType>(threadPoolCapacity, DEFAULT_THREAD_COUNT);

		return ObjectPoolPtr<ThreadDataBundle>(new NOU_DAT_ALG::ObjectPool<ThreadDataBundle>
			(threadPoolCapacity, NOU_MEM_MNGT::GenericAllocationCallback<
				NOU_DAT_ALG::ObjectPool<ThreadDataBundle>::AllocType>::get()),
			NOU_MEM_MNGT::defaultDeleter);
	}

	typename ThreadManager::ObjectPoolPtr<NOU_CORE::ErrorHandler> ThreadManager::makeHandlerPool()
	{
		//capacity() b/c must store the same amounts of handlers as there are threads
		return ObjectPoolPtr<NOU_CORE::ErrorHandler>(new NOU_DAT_ALG::ObjectPool<NOU_CORE::ErrorHandler>
			(m_threads->capacity()), NOU_MEM_MNGT::defaultDeleter);
	}

	NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<typename ThreadManager::TaskErrorHandlerPair>> 
		ThreadManager::makeTaskHeap()
	{
		return NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair>>
			(new NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair> (true, DEFAULT_TASK_CAPACITY),
				NOU_MEM_MNGT::defaultDeleter);
	}


	NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::HashMap<typename ThreadWrapper::ID,
		NOU_CORE::ErrorHandler*>> ThreadManager::makeHandlersMap()
	{
		using MapPtr = decltype(m_handlersMap);

		//+ 1 b/c this map also stores the handler of the main thread
		auto ret = NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::HashMap<typename ThreadWrapper::ID,
			NOU_CORE::ErrorHandler*>>(new NOU_DAT_ALG::HashMap<typename ThreadWrapper::ID, 
				NOU_CORE::ErrorHandler*>(m_threads->capacity() + 1), NOU_MEM_MNGT::defaultDeleter);

		ret->map(std::this_thread::get_id(), &NOU_CORE::ErrorHandler::getMainThreadHandler());

		return ret;
	}


	ThreadManager::TaskInformation ThreadManager::enqueueTask(internal::AbstractTask *task, int32 priority,
		NOU_CORE::ErrorHandler *handler)
	{
		/**
		 * No need to lock, since enqueueTask() is called by pushTask() which already locks the
		 * m_taskHeapAccessMutex.
		 */

		//store task and handler as-is, do not appoint a handler from the pool to a task that comes with an 
		//nullptr as error handler
		return TaskInformation(m_tasks->enqueue(priority, TaskErrorHandlerPair(task, handler)));
	}

	boolean ThreadManager::addThread()
	{
		if (m_threads->size() != m_threads->capacity())
		{
			Mutex startupVariableMutex;
			ConditionVariable startupVariable;
			Mutex startupMutex;
			boolean startupDone = false;

			{
				Lock startupLock(startupMutex);

				ThreadDataBundle *threadDataPtr;
				ThreadDataBundle &threadData = m_threads->emplaceObject(NOU_CORE::move(
					ThreadWrapper(threadLoop, this, &threadDataPtr, &startupMutex, &startupVariable, 
						&startupDone)));
				threadDataPtr = &threadData;
			}

			UniqueLock startupVariableLock(startupVariableMutex);
			startupVariable.wait(startupVariableLock, [&startupDone]() { return startupDone; });

			m_handlers->pushObject(NOU_CORE::ErrorHandler());

			return true;
		}

		return false;
	}

	void ThreadManager::executeTaskWithThread(TaskErrorHandlerPair task, ThreadDataBundle &threadData)
	{
		//If the set handler is nullptr, the task is supposed to run with a handler from the handler pool
		if (task.handler == nullptr)
		{
			NOU_ASSERT(m_handlers->remainingObjects() > 0);

			task.handler = &m_handlers->get();
		}

		//map handler to thread id
		m_handlersMap->map(threadData.m_thread.getID(), task.handler);

		threadData.m_taskHandlerPair = task;
		threadData.m_taskReady = true;
		threadData.m_variable.notifyAll();
	}

	ThreadManager::ThreadManager() : 
		m_shouldShutdown(false),
		m_threads(makeThreadPool()),
		m_handlers(makeHandlerPool()),
		m_tasks(makeTaskHeap()),
		m_handlersMap(makeHandlersMap())
	{
		static_assert(NOU_CORE::AreSame<typename 
			NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair>::PriorityTypePart, Priority>::value);
	}

	ThreadManager::~ThreadManager()
	{
		m_shouldShutdown = true;

		Lock threadLock(m_threadPoolAccessMutex);

		m_threads->foreach([](ThreadDataBundle& tdb) 
		{ 
			//if the thread method is currently waiting for a new task, this will make it stop waiting and
			//return instead 
			tdb.m_variable.notifyAll(); 

			if (tdb.m_thread.joinable()) 
			{ 
				tdb.m_thread.join(); 
			} 
		});
	}

	void ThreadManager::giveBackThread(ThreadDataBundle &thread)
	{
		{ 
			Lock taskLock(m_taskHeapAccessMutex); //open scope of Lock taskLock
			
			if (  m_tasks->size() > 0)
			{
				//give back handler b/c the task may have it's own handler & executeTaskWithThread() 
				//will get a new one from the pool.
				giveBackHandler(*thread.m_taskHandlerPair.handler);

				TaskErrorHandlerPair &task = m_tasks->get();
				m_tasks->dequeue();

				executeTaskWithThread(task, thread);
			}
			else
			{
				Lock threadLock(m_threadPoolAccessMutex);

				m_threads->giveBack(thread);

				giveBackHandler(*thread.m_taskHandlerPair.handler);
			}
		}
	}

	void ThreadManager::giveBackHandler(NOU_CORE::ErrorHandler &handler)
	{
		if (m_handlers->isPartOf(handler))
		{
			while (handler.getErrorCount() > 0) //clear handler from all errors
				handler.popError();

			m_handlers->giveBack(handler);
		}
	}

	ThreadManager::TaskInformation ThreadManager::pushTask(internal::AbstractTask *task, Priority priority,
		NOU_CORE::ErrorHandler *handler)
	{
		/*
		* If the priority is smaller than the priority at the root of the heap, the manager will try to
		* execute it immediately if a thread is available.
		*/

		Lock taskLock(m_taskHeapAccessMutex);

		//if the priority is smaller than the first one in the heap or there is no task in the heap (aka. 
		//this would be the first task to execute anyway)
		if (m_tasks->size() == 0 || priority <= m_tasks->priorityAt(0))
		{
			Lock threadLock(m_threadPoolAccessMutex);

			//if a thread is available or a new one could still be created, execute task immediately, 
			//otherwise enqueue in heap
			if (m_threads->remainingObjects() > 0 || addThread())
			{
				executeTaskWithThread(TaskErrorHandlerPair(task, handler), m_threads->get());
				return TaskInformation(TaskInformation::INVALID_ID);
			}
		}

		//if the task would not be the first one in the heap and no thread is available
		return enqueueTask(task, priority, handler);
	}

	boolean ThreadManager::removeTask(const TaskInformation &taskInfo)
	{
		if (taskInfo.m_id != TaskInformation::INVALID_ID)
		{
			Lock taskLock(m_taskHeapAccessMutex);
			
			if (m_tasks->checkIfPresent(taskInfo.m_id))
			{
				m_tasks->deleteById(taskInfo.m_id);

				return true;
			}
		}

		return false;
	}

	sizeType ThreadManager::maximumAvailableThreads() const
	{
		//No need to lock, since the capacity of an object pool never changes.
		return m_threads->capacity();
	}

	sizeType ThreadManager::currentlyAvailableThreads()
	{
		Lock lock(m_threadPoolAccessMutex);

		/*
		 * + (m_threads->capacity() - m_threads->size()) b\c remainingObjects() only returns the amount of 
		 * remaining objects that have already been pushed, this returns the total value of remaining threads, 
		 * even if not all threads have been pushed yet
		 */
		return m_threads->remainingObjects() + (m_threads->capacity() - m_threads->size());
	}

	NOU_CORE::ErrorHandler& ThreadManager::getErrorHandlerByThreadId(ThreadWrapper::ID id)
	{
		return *(m_handlersMap->get(id));
	}

	sizeType ThreadManager::currentlyPreparedThreads()
	{
		Lock lock(m_threadPoolAccessMutex);

		return m_threads->remainingObjects();
	}

	sizeType ThreadManager::prepareThread(sizeType count)
	{
		Lock lock(m_threadPoolAccessMutex);

		sizeType ret = 0; //use ret as a counter of how many threads have been created

		for (; ret < count; ret++)
		{
			//try to create a thread. if it fails, break the loop and return the amount of created threads
			if (!addThread()) 
				break;
		}

		return ret;
	}
}