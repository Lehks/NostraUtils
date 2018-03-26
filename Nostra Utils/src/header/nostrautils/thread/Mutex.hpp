#ifndef NOU_THREAD_MUTEX_HPP
#define	NOU_THREAD_MUTEX_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"

#include <mutex>

namespace NOU::NOU_THREAD
{
	/**
	\brief A mutex with very little overhead, but also limited capabilities. This mutex can only be locked and
	       unlocked. As of now, this class is merely a wrapper for std::mutex.
	*/
	class NOU_CLASS Mutex
	{
	public:
		/**
		\brief The type of the mutex that is internally used.
		*/
		using UnderlyingType = std::mutex;

	private:
		/**
		\brief The mutex that is being wrapped around.
		*/
		UnderlyingType m_mutex;

	public:
		/**
		\brief Locks the mutex.
		*/
		void lock();

		/**
		\brief Unlocks the mutex.
		*/
		void unlock();

		/**
		\return True, if the mutex was locked, false if not (it was already locked in that case).

		\brief If the mutex is unlocked, it will be locked. Otherwise nothing will happen.
		*/
		boolean tryLock();

		/**
		\return The underlying mutex.

		\brief Returns the underlying mutex.
		*/
		UnderlyingType& getUnderlying();

		/**
		\return The underlying mutex.

		\brief Returns the underlying mutex.
		*/
		const UnderlyingType& getUnderlying() const;
	};

	/**
	\brief An advanced mutex that is built atop of nostra::utils::thread::Mutex. Instead of just being able to
	       lock and unlock, this mutex has three levels of being locked.
	
	\details
	An advanced mutex that is built atop of nostra::utils::thread::Mutex. Instead of just being able to lock 
	and unlock, this mutex has three levels of being locked.

	These three levels are (as represented by the enum Lock): 
	- NONE
	- READ
	- WRITE
	
	\todo Add levels
	*/
	class NOU_CLASS ReadWriteMutex
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
		ReadWriteMutex();

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