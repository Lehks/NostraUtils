#include "nostrautils\thread\ThreadManager.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include "nostrautils\core\Assertions.hpp"

#include <iostream>

NOU::NOU_THREAD::Mutex logMutex;

namespace NOU::NOU_THREAD
{
	ThreadManager::TaskInformation::TaskInformation(Priority id) :
		m_id(id)
	{}

	ThreadManager::TaskInformation::TaskInformation() :
		m_id(INVALID_ID)
	{}

	void ThreadManager::threadLoop(ThreadManager *threadManager, ThreadDataBundle **threadDataPtr, 
		Mutex *startupMutex, ConditionVariable *startupVariable, boolean *startupDone)
	{
		static thread_local int i = 0;

		ThreadDataBundle *threadData;

		{
			Lock lock(*startupMutex);

			threadData = *threadDataPtr;
		}

		*startupDone = true;
		startupVariable->notifyAll();

		while (!(threadManager->m_shouldShutdown))
		{
			UniqueLock lock(threadData->mutex);
			threadData->variable.wait(lock, [threadData]() { return threadData->taskReady; });

			i++;

			AbstractTask *t = threadData->taskHandlerPair.task;

			threadData->taskHandlerPair.task->execute();

			//Set to false for the next iteration, must be set to true by the thread manager
			threadData->taskReady = false;

			threadManager->giveBackThread(*threadData);
		}
	}



	ThreadManager::ThreadDataBundle::ThreadDataBundle(ThreadWrapper &&thread) :
		thread(NOU_CORE::move(thread)),
		taskHandlerPair(nullptr, nullptr), //taskHandlerPair will be initialized later
		taskReady(false)
	{}

	ThreadManager::ThreadDataBundle::ThreadDataBundle(ThreadDataBundle&& tdb) :
		thread(NOU_CORE::move(tdb.thread)),
		taskHandlerPair(NOU_CORE::move(tdb.taskHandlerPair)),
		taskReady(tdb.taskReady)
	{}

	//ThreadManager ThreadManager::s_instance;

	NOU_FUNC ThreadManager& getThreadManager()
	{
		return ThreadManager::getInstance();
	}

	ThreadManager& ThreadManager::getInstance()
	{
		static ThreadManager instance;
		return instance;
	//	return s_instance;
	}

	typename ThreadManager::ObjectPoolPtr<typename ThreadManager::ThreadDataBundle> 
		ThreadManager::makeThreadPool()
	{
		// -1, b/c that is the main execution thread
		sizeType threadPoolCapacity = ThreadWrapper::maxThreads() == 0 ? DEFAULT_THREAD_COUNT - 1 : 
			ThreadWrapper::maxThreads() - 1;

		return ObjectPoolPtr<ThreadDataBundle>(new NOU_DAT_ALG::ObjectPool<ThreadDataBundle>
			(threadPoolCapacity, NOU_MEM_MNGT::GenericAllocationCallback<
				NOU_DAT_ALG::ObjectPool<ThreadDataBundle>::AllocType>::getInstance()),
			NOU_MEM_MNGT::defaultDeleter);
	}

	typename ThreadManager::ObjectPoolPtr<NOU_CORE::ErrorHandler> ThreadManager::makeHandlerPool()
	{
		//capacity() b/c must store the same amounts of handlers as there are threads
		return ObjectPoolPtr<NOU_CORE::ErrorHandler>(new NOU_DAT_ALG::ObjectPool<NOU_CORE::ErrorHandler>
			(m_threads->capacity(), NOU_MEM_MNGT::GenericAllocationCallback<
				NOU_DAT_ALG::internal::ObjectPoolChunk<NOU_CORE::ErrorHandler>>::getInstance()), 
			NOU_MEM_MNGT::defaultDeleter);
	}

	NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<typename ThreadManager::TaskErrorHandlerPair>> 
		ThreadManager::makeTaskHeap()
	{
		return NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair>>
			(new NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair> (true, DEFAULT_TASK_CAPACITY, 
				NOU_MEM_MNGT::GenericAllocationCallback<NOU_DAT_ALG::Pair<uint64, TaskErrorHandlerPair>>
					::getInstance()),
				NOU_MEM_MNGT::defaultDeleter);
	}

	ThreadManager::TaskInformation ThreadManager::enqueueTask(AbstractTask *task, int32 priority, 
		NOU_CORE::ErrorHandler *handler)
	{
		/**
		 * No need to lock, since enqueueTask() is called by pushTask() which already locks the
		 * m_taskHeapAccessMutex.
		 */

		//store task and handler as-is, do not appoint a handler from the pool to a task that comes with an 
		//nullptr as error handler
		return TaskInformation(m_tasks->enqueue(TaskErrorHandlerPair(task, handler), priority));
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

		threadData.taskHandlerPair = task;
		threadData.taskReady = true;
		threadData.variable.notifyAll();
	}

	ThreadManager::ThreadManager() : 
		m_shouldShutdown(false),
		m_threads(makeThreadPool()),
		m_handlers(makeHandlerPool()),
		m_tasks(makeTaskHeap())
	{
		static_assert(NOU_CORE::AreSame<typename 
			NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair>::PriorityTypePart, Priority>::value);
	}

	ThreadManager::~ThreadManager()
	{
		m_shouldShutdown = true;

		Lock threadLock(m_threadPoolAccessMutex);

		m_threads->foreach([](ThreadDataBundle& tdb) { if (tdb.thread.joinable()) { tdb.thread.join(); } });
	}

	void ThreadManager::giveBackThread(ThreadDataBundle &thread)
	{
		//if there is a task left, execute it immediately with the thread, otherwise put it back in the pool
		if (Lock taskLock(m_taskHeapAccessMutex);  m_tasks->size() > 0)
		{
			//give back handler b/c the task may have it's own handler & executeTaskWithThread() 
			//will get a new one from the pool.
			giveBackHandler(*thread.taskHandlerPair.handler);

			TaskErrorHandlerPair &task = m_tasks->get();
			m_tasks->dequeue();

			executeTaskWithThread(task, thread);
		}
		else
		{
			Lock threadLock(m_threadPoolAccessMutex);

			m_threads->giveBack(thread);

			giveBackHandler(*thread.taskHandlerPair.handler);
		}
	}

	void ThreadManager::giveBackHandler(NOU_CORE::ErrorHandler &handler)
	{
		if (m_handlers->isPartOf(handler))
		{
			while (handler.getErrorCount() > 0)
				handler.popError();

			m_handlers->giveBack(handler);
		}
	}

	ThreadManager::TaskInformation ThreadManager::pushTask(AbstractTask *task, Priority priority,
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
			
			if (/*replace with check if taskInfo.m_id is in the heap*/true)
			{
				//remove task from heap

				return true;
			}
		}

		return false;
	}
}