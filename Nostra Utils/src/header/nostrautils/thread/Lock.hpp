#ifndef NOU_THREAD_LOCK_HPP
#define NOU_THREAD_LOCK_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\thread\Mutex.hpp"

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

		/**
		\brief If true, the destructor will unlock the mutex, if false it will not.
		*/
		boolean m_needsUnlocking;

	public:
		/**
		\brief Constructs without any mutex. Nothing will happen.
		*/
		Lock();

		/**
		\param mutex The mutex to lock.

		\brief If not already locked, will lock the mutex.
		*/
		Lock(Mutex &mutex);

		/**
		\brief other The Lock to move from.

		\brief Moves one lock to another one. The one that was moved from will not trigger the unlock.
		*/
		Lock(Lock&& other);

		Lock(const Lock&) = delete;

		/**
		\brief If needed, will unlock the mutex.
		*/
		~Lock();
	};

	/**
	\brief A class that stores a reference to a mutex. Upon construction, the mutex will be locked and upon
	destruction it will be unlocked.
	*/
	class NOU_CLASS UniqueLock final
	{
	public:
		using UnderlyingType = std::unique_lock<std::mutex>;

	private:
		/**
		\brief The managed mutex.
		*/
		UnderlyingType m_lock;

	public:
		UniqueLock() = default;

		UniqueLock(Mutex &mutex);

		UniqueLock(UniqueLock&& other) = default;

		UniqueLock(const UniqueLock&) = delete;

		UnderlyingType& getUnderlying();

		const UnderlyingType& getUnderlying() const;
	};
}

#endif