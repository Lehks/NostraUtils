#include "nostrautils\thread\ThreadManager.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"

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

	void ThreadManager::threadLoop(ThreadManager &manager)
	{
		UniqueLock lock(manager.m_taskQueueMutex);
		manager.m_threadLoopVariable.wait(lock, [&manager] { return manager.m_tasks->size() == 0; });


	}

	typename ThreadManager::ObjectPoolPtr<typename ThreadManager::ThreadType> ThreadManager::makeThreadPool()
	{
		sizeType threadPoolCapacity = ThreadWrapper::maxThreads() == 0 ? DEFAULT_THREAD_COUNT : 
			ThreadWrapper::maxThreads();

		return ObjectPoolPtr<ThreadType>(new NOU_DAT_ALG::ObjectPool<ThreadType>(threadPoolCapacity, 
			m_threadAllocator), NOU_MEM_MNGT::defaultDeleter);
	}

	typename ThreadManager::ObjectPoolPtr<NOU_CORE::ErrorHandler> ThreadManager::makeHandlerPool()
	{
		//capacity() b/c must store the same amounts of handlers as there are threads
		return ObjectPoolPtr<NOU_CORE::ErrorHandler>(new NOU_DAT_ALG::ObjectPool<NOU_CORE::ErrorHandler>
			(m_threads->capacity(), m_handlerAllocator), NOU_MEM_MNGT::defaultDeleter);
	}

	NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<AbstractTask*>> ThreadManager::makeTaskHeap()
	{
		return NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::BinaryHeap<AbstractTask*>>
			(new NOU_DAT_ALG::BinaryHeap<AbstractTask*> (true, DEFAULT_TASK_CAPACITY, m_taskAllocator), 
				NOU_MEM_MNGT::defaultDeleter);
	}

	ThreadManager::ThreadManager() : 
		m_threads(makeThreadPool()),
		m_handlers(makeHandlerPool()),
		m_tasks(makeTaskHeap())
	{

	}
}