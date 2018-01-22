#include "nostrautils\thread\Lock.hpp"
#include "nostrautils\core\Utils.hpp"

namespace NOU::NOU_THREAD
{
	Lock::Lock() : 
		m_needsUnlocking(false),
		m_mutex(nullptr)
	{}

	Lock::Lock(Mutex &mutex) :
		m_needsUnlocking(true),
		m_mutex(&mutex)
	{
		m_mutex->tryLock();
	}

	Lock::Lock(Lock&& other) :
		m_needsUnlocking(true),
		m_mutex(other.m_mutex)
	{
		other.m_needsUnlocking = false;
	}
	
	Lock::~Lock()
	{
		if (m_needsUnlocking)
			m_mutex->unlock();
	}
}