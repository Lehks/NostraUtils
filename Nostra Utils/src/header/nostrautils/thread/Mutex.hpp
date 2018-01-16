#ifndef NOU_THREAD_MUTEX_HPP
#define	NOU_THREAD_MUTEX_HPP

#include "nostrautils\core\StdIncludes.hpp"

#include <mutex>

namespace NOU::NOU_THREAD
{
	class NOU_CLASS Mutex
	{
	public:
		enum class Lock
		{
			NONE,
			READ,
			WRITE
		};

		using UnderlyingType = std::mutex;

	private:
		Lock m_lock;
		UnderlyingType m_mutex;

	public:
		void readLock();
		void writeLock();

		boolean tryReadLock();
		boolean tryWriteLock();

		void unlock();
		void unlockToRead();

		Lock getLockLevel() const;

		boolean isLocked() const;
		boolean isReadLocked() const;
		boolean isWriteLocked() const;

		UnderlyingType& getUnderlying();
		const UnderlyingType& getUnderlying() const;
	};
}

#endif