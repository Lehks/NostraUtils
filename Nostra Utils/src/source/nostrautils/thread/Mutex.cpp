#include "nostrautils\thread\Mutex.hpp"
#include "nostrautils\core\ErrorHandler.hpp"

namespace NOU::NOU_THREAD
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

	ReadWriteMutex::ReadWriteMutex() :
		m_lock(Lock::NONE)
	{}

	void ReadWriteMutex::readLock()
	{
		switch (m_lock)
		{
		case Lock::NONE:
			m_lock = Lock::READ;
			//fall-through
		case Lock::READ:
			return;

		case Lock::WRITE:
			m_mutex.lock();
			return;
		}
	}

	void ReadWriteMutex::writeLock()
	{
		switch (m_lock)
		{
		case Lock::NONE:
			m_lock = Lock::WRITE;
			return;

		case Lock::READ:
		case Lock::WRITE:
			m_mutex.lock();
			return;
		}
	}

	boolean ReadWriteMutex::tryReadLock()
	{
		if (!isWriteLocked())
		{
			readLock();
			return true;
		}

		return false;
	}

	boolean ReadWriteMutex::tryWriteLock()
	{
		if (!isLocked())
		{
			writeLock();
			return true;
		}

		return false;
	}

	void ReadWriteMutex::unlock()
	{
		NOU_COND_PUSH_DBG_ERROR(m_lock == Lock::NONE, NOU_CORE::getErrorHandler(),
			NOU_CORE::ErrorCodes::MUTEX_ERROR, "A mutex that was not locked has been unlocked.");

		m_lock = Lock::NONE;
		m_mutex.unlock();
	}

	void ReadWriteMutex::unlockToRead()
	{
		if (m_lock == Lock::WRITE)
		{
			m_mutex.unlock();
			m_lock = Lock::READ;
		}
		else
		{
			NOU_PUSH_DBG_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::MUTEX_ERROR,
				"A mutex was unlocked to read, but it was not write locked.");
		}
	}

	typename ReadWriteMutex::Lock ReadWriteMutex::getLockLevel() const
	{
		return m_lock;
	}

	boolean ReadWriteMutex::isLocked() const
	{
		return m_lock != Lock::NONE;
	}

	boolean ReadWriteMutex::isReadLocked() const
	{
		return m_lock == Lock::READ;
	}

	boolean ReadWriteMutex::isWriteLocked() const
	{
		return m_lock == Lock::WRITE;
	}

	ReadWriteMutex::UnderlyingType& ReadWriteMutex::getUnderlying()
	{
		return m_mutex;
	}

	const ReadWriteMutex::UnderlyingType& ReadWriteMutex::getUnderlying() const
	{
		return m_mutex;
	}
}