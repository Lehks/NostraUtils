#ifndef NOU_THREAD_LOCK_HPP
#define NOU_THREAD_LOCK_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\thread\Mutex.hpp"

#include <mutex>

/**
\file thread/Lock.hpp

\author  Lukas Reichmann
\version 0.0.1
\since   1.0.0

\brief A file that contains the several locks that are provided by NOU.
*/

namespace NOU::NOU_THREAD
{
	/**
	\brief A class that stores a reference to a mutex. Upon construction, the mutex will be locked and upon 
	       destruction it will be unlocked.
	*/
	class NOU_CLASS Lock final //implement way to manage multiple mutexes at once.
	{
	private:
		/**
		\brief The managed mutex.
		*/
		Mutex *m_mutex;

	public:
		/**
		\param mutex The mutex to lock.

		\brief If not already locked, this will lock the mutex.
		*/
		Lock(Mutex &mutex, boolean lock = true);

		/**
		\brief Not copy construct-able.
		*/
		Lock(const Lock&) = delete;

		/**
		\brief This will unlock the mutex.
		*/
		~Lock();
	};

	/**
	\brief A class that stores a reference to a mutex. Upon construction, the mutex will be locked and upon
	       destruction it will be unlocked.

	\details
	For implementation specific reasons, this lock is necessary when using ConditionVariable. Unless 
	explicitly needed for such variable, Lock is a better alternative.
	*/
	class NOU_CLASS UniqueLock final
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
		UniqueLock(Mutex &mutex);

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
		UnderlyingType& getUnderlying();

		/**
		\return The underlying lock.

		\brief Returns the underlying lock.
		*/
		const UnderlyingType& getUnderlying() const;
	};
}

#endif