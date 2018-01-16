#include "nostrautils\thread\Mutex.hpp"
#include "nostrautils\core\ErrorHandler.hpp"

namespace NOU::NOU_THREAD
{
	void Mutex::readLock()
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

	void Mutex::writeLock()
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

	boolean Mutex::tryReadLock()
	{
		if (!isWriteLocked())
		{
			readLock();
			return true;
		}

		return false;
	}

	boolean Mutex::tryWriteLock()
	{
		if (!isLocked())
		{
			writeLock();
			return true;
		}

		return false;
	}

	void Mutex::unlock()
	{
		NOU_COND_PUSH_DBG_ERROR(m_lock == Lock::NONE, NOU_CORE::getErrorHandler(),
			NOU_CORE::ErrorCodes::MUTEX_ERROR, "A mutex that was not locked has been unlocked.");

		m_lock = Lock::NONE;
		m_mutex.unlock();
	}

	void Mutex::unlockToRead()
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

	typename Mutex::Lock Mutex::getLockLevel() const
	{
		return m_lock;
	}

	boolean Mutex::isLocked() const
	{
		return m_lock != Lock::NONE;
	}

	boolean Mutex::isReadLocked() const
	{
		return m_lock == Lock::READ;
	}

	boolean Mutex::isWriteLocked() const
	{
		return m_lock == Lock::WRITE;
	}

	Mutex::UnderlyingType& Mutex::getUnderlying()
	{
		return m_mutex;
	}

	const Mutex::UnderlyingType& Mutex::getUnderlying() const
	{
		return m_mutex;
	}
}