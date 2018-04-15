#include "nostrautils/thread/Mutex.hpp"

namespace NOU { namespace NOU_THREAD
{
	void Mutex::lock()
	{
		m_mutex.lock();
	}

	void Mutex::unlock()
	{
		m_mutex.unlock();
	}

	boolean Mutex::tryLock()
	{
		return m_mutex.try_lock();
	}

	typename Mutex::UnderlyingType& Mutex::getUnderlying()
	{
		return m_mutex;
	}
	
	const typename Mutex::UnderlyingType& Mutex::getUnderlying() const
	{
		return m_mutex;
	}
} //Namespace NOU_DAT_ALG
} //Namespace NOU