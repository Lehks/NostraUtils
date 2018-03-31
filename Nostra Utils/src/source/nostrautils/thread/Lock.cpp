#include "nostrautils/thread/Lock.hpp"
#include "nostrautils/core/Utils.hpp"

namespace NOU::NOU_THREAD
{
	Lock::Lock(Mutex &mutex, boolean lock) :
		m_mutex(&mutex)
	{
		if(lock)
			m_mutex->lock();
	}

	Lock::~Lock()
	{
		m_mutex->unlock();
	}

	UniqueLock::UniqueLock(Mutex &mutex) :
		m_lock(mutex.getUnderlying())
	{}

	typename UniqueLock::UnderlyingType& UniqueLock::getUnderlying()
	{
		return m_lock;
	}

	const typename UniqueLock::UnderlyingType& UniqueLock::getUnderlying() const
	{
		return m_lock;
	}
}