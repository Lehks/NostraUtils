#ifndef NOU_THREAD_MUTEX_HPP
#define	NOU_THREAD_MUTEX_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"

#include <mutex>

namespace NOU::NOU_THREAD
{
	/**
	\brief A mutex with very little overhead, but also limited capabilities. This mutex can only be locked and
	       unlocked. As of now, this class is merly a wrapper for std::mutex.
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

	template<typename T>
	class NOU_CLASS Protection
	{
	public:
		using StoredType = T;

	private:

		Mutex m_mutex;
		StoredType m_stored;

	public:
		explicit Protection(StoredType&& stored);

		template<typename... ARGS>
		explicit Protection(ARGS... args);

		StoredType& get();
		const StoredType& get() const;

		void lock();
		void unlock();
		boolean tryLock();

		Mutex& getMutex();
		const Mutex& getMutex() const;

		StoredType* operator -> ();
		const StoredType* operator -> () const;

		StoredType& operator * ();
		const StoredType& operator * () const;
	};

	/**
	\todo implement
	*/
	template<typename T>
	class NOU_CLASS ReadWriteProtection
	{

	};

	template<typename T>
	template<typename... ARGS>
	Protection<T>::Protection(ARGS... args) :
		m_stored(NOU_CORE::forward<ARGS>(args)...)
	{}

	template<typename T>
	Protection<T>::Protection(StoredType&& stored) :
		m_stored(NOU_CORE::forward<StoredType>(stored))
	{}

	template<typename T>
	typename Protection<T>::StoredType& Protection<T>::get()
	{
		return m_stored;
	}

	template<typename T>
	const typename Protection<T>::StoredType& Protection<T>::get() const
	{
		return m_stored;
	}

	template<typename T>
	void Protection<T>::lock()
	{
		m_mutex.lock();
	}

	template<typename T>
	void Protection<T>::unlock()
	{
		m_mutex.unlock();
	}

	template<typename T>
	boolean Protection<T>::tryLock()
	{
		return m_mutex.tryLock();
	}

	template<typename T>
	Mutex& Protection<T>::getMutex()
	{
		return m_mutex;
	}

	template<typename T>
	const Mutex& Protection<T>::getMutex() const
	{
		return m_mutex;
	}

	template<typename T>
	typename Protection<T>::StoredType* Protection<T>::operator -> ()
	{
		return &m_stored;
	}

	template<typename T>
	const typename Protection<T>::StoredType* Protection<T>::operator -> () const
	{
		return &m_stored;
	}

	template<typename T>
	typename Protection<T>::StoredType& Protection<T>::operator * ()
	{
		return get();
	}

	template<typename T>
	const typename Protection<T>::StoredType& Protection<T>::operator * () const
	{
		return get();
	}
}

#endif