#include "nostrautils/thread/ThreadWrapper.hpp"

namespace NOU { namespace NOU_THREAD
{
	uint32 ThreadWrapper::maxThreads()
	{
		return std::thread::hardware_concurrency();
	}
	
	ThreadWrapper::ThreadWrapper(ThreadWrapper &&other) :
		m_thread(NOU_CORE::move(other.m_thread))
	{}
	
	typename ThreadWrapper::UnderylingType& ThreadWrapper::getUnderlying()
	{
		return m_thread;
	}
	
	const typename ThreadWrapper::UnderylingType& ThreadWrapper::getUnderlying() const
	{
		return m_thread;
	}

	void ThreadWrapper::join()
	{
		m_thread.join();
	}

	void ThreadWrapper::detach()
	{
		m_thread.detach();
	}

	boolean ThreadWrapper::joinable() const
	{
		return m_thread.joinable();
	}
	
	typename ThreadWrapper::ID ThreadWrapper::getID() const
	{
		return m_thread.get_id();
	}
} //Namespace NOU_DAT_ALG
} //Namespace NOU
