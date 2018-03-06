#include "nostrautils\thread\ThreadManager.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include "nostrautils\core\Assertions.hpp"

#include <iostream>

NOU::NOU_THREAD::Mutex logMutex;

#define NOU_DBG_INFO(msg) 															   \
{																					   \
	logMutex.lock();																   \
	std::cout << "[INFO#" << std::this_thread::get_id() << "] " << msg << std::endl;   \
	logMutex.unlock();																   \
}

namespace NOU::NOU_THREAD
{
	void ThreadManager::threadLoop(ThreadManager *threadManager, ThreadDataBundle **threadDataPtr, 
		Mutex *startupMutex, ConditionVariable *startupVariable)
	{
		ThreadDataBundle *threadData;

		{
			startupMutex->lock();

			threadData = *threadDataPtr;

			startupMutex->unlock();
		}

		startupVariable->notifyAll();

		NOU_DBG_INFO("Thread initialization complete.");

		while (!(threadManager->m_shouldShutdown))
		{
			UniqueLock lock(threadData->mutex);
			threadData->variable.wait(lock);


			NOU_DBG_INFO("Thread execution started.");
			threadData->taskHandlerPair.task->execute();
			NOU_DBG_INFO("Thread execution complete.");

			threadManager->giveBackThread(*threadData);
		}
	}



	ThreadManager::ThreadDataBundle::ThreadDataBundle(ThreadWrapper &&thread) :
		thread(NOU_CORE::move(thread)),
		taskHandlerPair(nullptr, nullptr) //taskHandlerPair will be initialized later
	{}

	ThreadManager::ThreadDataBundle::ThreadDataBundle(ThreadDataBundle&& tdb) :
		thread(NOU_CORE::move(tdb.thread)),
		taskHandlerPair(NOU_CORE::move(tdb.taskHandlerPair))
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

	void ThreadManager::pushTask(AbstractTask *task, int32 priority, NOU_CORE::ErrorHandler *handler)
	{
		NOU_DBG_INFO("Pushing task.");

		/*
         * If the priority is smaller than the priority at the root of the heap, the manager will try to 
		 * execute it immediately if a thread is available.
         */

		//if the priority is smaller than the first one in the heap or there is no task in the heap (aka. 
		//this would be the first task to execute anyway)
		if (m_tasks->size() == 0 || priority <= m_tasks->priorityAt(0)) 
		{
			Lock lock(m_threadPoolAccessMutex);

			//if a thread is available or a new one could still be created, execute task immediately, 
			//otherwise enqueue in heap
			if (m_threads->remainingObjects() > 0 || addThread())
			{
				executeTaskWithThread(TaskErrorHandlerPair(task, handler), m_threads->get());
				return;
			}
		}

		//if the task would not be the first one in the heap and no thread is available
		enqueueTask(task, priority, handler);
	}

	void ThreadManager::enqueueTask(AbstractTask *task, int32 priority, NOU_CORE::ErrorHandler *handler)
	{
		NOU_DBG_INFO("Pushing task in queue.");
		//store task and handler as-is, do not appoint a handler from the pool to a task that comes with an 
		//nullptr as error handler
		m_tasks->enqueue(TaskErrorHandlerPair(task, handler), priority);
	}

	boolean ThreadManager::addThread()
	{
		NOU_DBG_INFO("Trying to add thread.");
	
		if (m_threads->size() != m_threads->capacity())
		{
			NOU_DBG_INFO("Adding thread successful.");

			Mutex startupVariableMutex;
			ConditionVariable startupVariable;

			Mutex startupMutex;

			startupMutex.lock();

			ThreadDataBundle *threadDataPtr;
			ThreadDataBundle &threadData = m_threads->emplaceObject(NOU_CORE::move(ThreadWrapper(threadLoop, 
				this, &threadDataPtr, &startupMutex, &startupVariable)));
			threadDataPtr = &threadData;

			startupMutex.unlock();

			UniqueLock startupVariableLock(startupVariableMutex);
			startupVariable.wait(startupVariableLock);

			m_handlers->pushObject(NOU_CORE::ErrorHandler());

			NOU_DBG_INFO("While adding thread, added error handler.");

			return true;
		}

		NOU_DBG_INFO("Adding thread failed.");

		return false;
	}

	void ThreadManager::executeTaskWithThread(TaskErrorHandlerPair task, ThreadDataBundle &thread)
	{
		NOU_DBG_INFO("Executing task in thread.");

		//If the set handler is nullptr, the task is supposed to run with a handler from the handler pool
		if (task.handler == nullptr)
		{
			NOU_ASSERT(m_handlers->remainingObjects() > 0);

			task.handler = &m_handlers->get();
		}

		thread.taskHandlerPair = task;
		thread.variable.notifyAll();
	}

	ThreadManager::ThreadManager() : 
		m_shouldShutdown(false),
		m_threads(makeThreadPool()),
		m_handlers(makeHandlerPool()),
		m_tasks(makeTaskHeap())
	{}

	ThreadManager::~ThreadManager()
	{
		m_shouldShutdown = true;

		m_threads->foreach([](ThreadDataBundle& tdb) { if (tdb.thread.joinable()) { tdb.thread.join(); } });
	
		std::cout << "Thrd Destructor" << std::endl;
	}

	void ThreadManager::giveBackThread(ThreadDataBundle &thread)
	{
		NOU_DBG_INFO("Giving back thread #" << thread.thread.getID());
		NOU_DBG_INFO("Task queue size: " << m_tasks->size());

		Lock lock(m_threadPoolAccessMutex);

		//if there is a task left, execute it immediately with the thread, otherwise put it back in the pool
		if (m_tasks->size() > 0)
		{
			NOU_DBG_INFO("Not giving back thread, executing next task instead.");

			TaskErrorHandlerPair &task = m_tasks->get();
			m_tasks->dequeue();

			executeTaskWithThread(task, thread);
		}
		else
		{
			NOU_DBG_INFO("Thread was given back.");

			m_threads->giveBack(thread);

			if (m_handlers->isPartOf(*thread.taskHandlerPair.handler))
			{
				m_handlers->giveBack(*thread.taskHandlerPair.handler);
			}
		}
	}
}