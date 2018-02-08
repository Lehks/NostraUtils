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

	}

	ThreadManager::ThreadManager() : 
		m_threads(new NOU_DAT_ALG::Vector<ThreadType>
			(ThreadWrapper::maxThreads() == 0 ? DEFAULT_THREAD_COUNT : ThreadWrapper::maxThreads(), 
				m_threadAllocator), NOU_MEM_MNGT::defaultDeleter),
		//capacity() b/c must store the same amounts of handlers as there are threads
		m_handlers(new NOU_DAT_ALG::Vector<NOU_CORE::ErrorHandler> 
			(m_threads->capacity(), m_handlerAllocator), NOU_MEM_MNGT::defaultDeleter),
		//add default task capacity as soon as it is supported by the binary heap
		m_tasks(new NOU_DAT_ALG::BinaryHeap<AbstractTask*>
		(true, m_taskAllocator), NOU_MEM_MNGT::defaultDeleter)
	{

	}
}