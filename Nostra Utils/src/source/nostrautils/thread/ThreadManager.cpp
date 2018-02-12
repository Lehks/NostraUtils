#include "nostrautils\thread\ThreadManager.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include "nostrautils\core\Assertions.hpp"

namespace NOU::NOU_THREAD
{
	ThreadManager ThreadManager::s_instance;

	NOU_FUNC ThreadManager& getThreadManager()
	{
		return ThreadManager::getInstance();
	}

	ThreadManager& ThreadManager::getInstance()
	{
		return s_instance;
	}

	typename ThreadManager::ObjectPoolPtr<typename ThreadManager::ThreadType> ThreadManager::makeThreadPool()
	{
		// -1, b/c that is the main execution thread
		sizeType threadPoolCapacity = ThreadWrapper::maxThreads() == 0 ? DEFAULT_THREAD_COUNT - 1 : 
			ThreadWrapper::maxThreads() - 1;

		return ObjectPoolPtr<ThreadType>(new NOU_DAT_ALG::ObjectPool<ThreadType>(threadPoolCapacity, 
			m_threadAllocator), NOU_MEM_MNGT::defaultDeleter);
	}

	typename ThreadManager::ObjectPoolPtr<NOU_CORE::ErrorHandler> ThreadManager::makeHandlerPool()
	{
		//capacity() b/c must store the same amounts of handlers as there are threads
		return ObjectPoolPtr<NOU_CORE::ErrorHandler>(new NOU_DAT_ALG::ObjectPool<NOU_CORE::ErrorHandler>
			(m_threads->capacity(), m_handlerAllocator), NOU_MEM_MNGT::defaultDeleter);
	}

	NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<typename ThreadManager::TaskErrorHandlerPair>> 
		ThreadManager::makeTaskHeap()
	{
		return NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair>>
			(new NOU_DAT_ALG::BinaryHeap<TaskErrorHandlerPair> (true, DEFAULT_TASK_CAPACITY, m_taskAllocator),
				NOU_MEM_MNGT::defaultDeleter);
	}

	void ThreadManager::pushTask(AbstractTask *task, int32 priority, NOU_CORE::ErrorHandler *handler)
	{
		/*
         * If the priority is smaller than the priority at the root of the heap, the manager will try to 
		 * execute it immediately if a thread is available.
         */

		//if the priority is smaller than the first one in the heap (aka. this would be the first task to 
		//execute anyway)
		if (priority <= m_tasks->priorityAt(0)) 
		{
			Lock lock(m_threadPoolAccessMutex);

			//if a thread is available, execute task immediately, otherwise enqueue in heap
			if (m_threads->remainingObjects() > 0)
			{
				executeTaskWithThread(TaskErrorHandlerPair(task, handler), m_threads->get());
			}
		}

		//if the task would not be the first one in the heap and no thread is available
		enqueueTask(task, priority, handler);
	}

	void ThreadManager::enqueueTask(AbstractTask *task, int32 priority, NOU_CORE::ErrorHandler *handler)
	{
		//store task and handler as-is, do not appoint a handler from the pool to a task that comes with an 
		//nullptr as error handler
		m_tasks->enqueue(TaskErrorHandlerPair(task, handler), priority);
	}

	void ThreadManager::executeTaskWithThread(TaskErrorHandlerPair task, ThreadType &thread)
	{
		//If the set handler is nullptr, the task is supposed to run with a handler from the handler pool
		if (task.dataTwo == nullptr)
		{
			NOU_ASSERT(m_handlers->remainingObjects() > 0);

			task.dataTwo = &m_handlers->get();
		}

		//set task for execution in thread
	}

	ThreadManager::ThreadManager() : 
		m_threads(makeThreadPool()),
		m_handlers(makeHandlerPool()),
		m_tasks(makeTaskHeap())
	{}

	ThreadManager::~ThreadManager()
	{
		
	}

	void ThreadManager::giveBackThread(ThreadType &thread)
	{
		Lock lock(m_threadPoolAccessMutex);

		//if there is a task left, execute it immediately with the thread, otherwise put it back in the pool
		if (m_tasks->size() > 0)
		{
			TaskErrorHandlerPair &task = m_tasks->get();
			m_tasks->dequeue();

			executeTaskWithThread(task, thread);
		}
		else
		{
			m_threads->giveBack(thread);
		}
	}
}