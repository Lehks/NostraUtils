#ifndef NOU_THREAD_LOCK_HPP
#define NOU_THREAD_LOCK_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/thread/Mutex.hpp"

#include <mutex>

/**
\file thread/Lock.hpp

\author  Lukas Reichmann
\version 1.0.1
\since   1.0.0

\brief A file that contains the several locks that are provided by NOU.
*/

namespace NOU::NOU_THREAD
{
	/**
	\brief A class that stores a reference to a mutex. Upon construction, the mutex will be locked and upon 
	       destruction it will be unlocked.
	*/
	class Lock final //implement way to manage multiple mutexes at once.
	{
	private:
		/**
		\brief The managed mutex.
		*/
		Mutex *m_mutex;

	public:
		/**
		\param mutex The mutex to lock.
		\param lock  Defines whether the mutex should be locked or not. This can be used to adapt a lock from 
		             a different instance of the lock class (the destructor will unlock the mutex even if the 
					 mutex was not explicitly locked here).

		\brief If not already locked, this will lock the mutex.
		*/
		NOU_FUNC Lock(Mutex &mutex, boolean lock = true);

		/**
		\brief Not copy construct-able.
		*/
		NOU_FUNC Lock(const Lock&) = delete;

		/**
		\brief This will unlock the mutex.
		*/
		NOU_FUNC ~Lock();
	};

	/**
	\brief A class that stores a reference to a mutex. Upon construction, the mutex will be locked and upon
	       destruction it will be unlocked.

	\details
	For implementation specific reasons, this lock is necessary when using ConditionVariable. Unless 
	explicitly needed for such variable, Lock is a better alternative.
	*/
	class UniqueLock final
	{
	public:
		/**
		\brief The type of lock that is internally used.
		*/
		using UnderlyingType = std::unique_lock<std::mutex>;

	private:
		/**
		\brief The internal lock.
		*/
		UnderlyingType m_lock;

	public:
		/**
		\brief Constructs an instance without a mutex.
		*/
		UniqueLock() = default;

		/**
		\param mutex The mutex that will be locked.

		\brief Constructs an instance with the passed mutex.
		*/
		NOU_FUNC UniqueLock(Mutex &mutex);

		/**
		\brief other the lock to move.

		\brief Moves the lock.
		*/
		UniqueLock(UniqueLock&& other) = default;

		/**
		\brief Not copy construct-able.
		*/
		UniqueLock(const UniqueLock&) = delete;

		/**
		\return The underlying lock.

		\brief Returns the underlying lock.
		*/
		NOU_FUNC UnderlyingType& getUnderlying();

		/**
		\return The underlying lock.

		\brief Returns the underlying lock.
		*/
		NOU_FUNC const UnderlyingType& getUnderlying() const;
	};
}

#endif