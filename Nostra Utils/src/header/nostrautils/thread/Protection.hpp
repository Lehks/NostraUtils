#ifndef	NOU_THREAD_PROTECTION_HPP
#define	NOU_THREAD_PROTECTION_HPP

#include "nostrautils\thread\Mutex.hpp"
#include "nostrautils\thread\Lock.hpp"

namespace NOU::NOU_THREAD
{
	/**
	\tparam T The type of the variable that will be stored.

	\brief A class that is used by the protection class. See Protection::getLocked for further info.

	\see Protection::getLocked
	*/
	template<typename T>
	class NOU_CLASS ProtectedValue
	{
	public:
		/**
		\brief The type of the stored value.
		*/
		using StoredType = T;

	private:
		/**
		\brief A reference to the stored value.
		*/
		StoredType &m_stored;

		/**
		\brief The lock that is used to lock and undlock the access to the value.
		*/
		Lock m_lock;

	public:
		/**
		\param stored The a reference to the stored value.
		\param mutex  The mutex that is used to lock the access to the value.

		\brief Constructs a protected value from the passed reference and mutex.
		*/
		ProtectedValue(StoredType &stored, Mutex& mutex);

		/**
		\return The stored value.

		\brief Returns the stored value.
		*/
		StoredType& get();

		/**
		\return The stored value.

		\brief Returns the stored value.
		*/
		const StoredType& get() const;
	};

	/**
	\tparam T The type of the value that will be stored.

	\brief A class that can be used to make a certain value thread safe. This class can lock the access to
	       that value using a mutex that is bound to that variable.
	*/
	template<typename T>
	class NOU_CLASS Protection
	{
	public:
		/**
		\brief The type of the variable that will be stored.
		*/
		using StoredType = T;

	private:

		/**
		\brief The mutex that will be used to lock the access to the value.
		*/
		volatile Mutex m_mutex;

		/**
		\brief The stored value.
		*/
		StoredType m_stored;

	public:
		/**
		\brief stored The value that will be stored.

		\brief Constructs a new instance from a value of the stored type.
		*/
		explicit Protection(StoredType&& stored);

		/**
		\param args The arguments that will be passed to StoredType's constructor.

		\brief Constructs a new instance with an instance of the stored type that will be constructed from the
		       passed arguments.
		*/
		template<typename... ARGS>
		explicit Protection(ARGS... args);

		/**
		\return The stored value.

		\brief Returns the stored value. The access to that value will not be locked and does not wait if the
		       mutex is locked.
		*/
		StoredType& getUnlocked();

		/**
		\return The stored value.

		\brief Returns the stored value. The access to that value will not be locked and does not wait if the
		       mutex is locked.
		*/
		const StoredType& getUnlocked() const;

		/**
		\return A protected value that contains the actual value.

		\brief Returns a protected value instance that holds the actual value. The access to the value is now
		       locked.

		\details
		The value will be locked as long as the returned instance if ProtectedValue is alive. As long as it is
		locked, other threads must wait when calling getLocked() until the value is unlocked.
		*/
		ProtectedValue<StoredType> getLocked();

		/**
		\return A protected value that contains the actual value.

		\brief Returns a protected value instance that holds the actual value. The access to the value is now
		locked.

		\details
		The value will be locked as long as the returned instance if ProtectedValue is alive. As long as it is
		locked, other threads must wait when calling getLocked() until the value is unlocked.
		*/
		ProtectedValue<const StoredType> getLocked() const;

		/**
		\brief The value as returned by getUnlocked().

		\brief Returns the value as returned by getUnlocked().
		*/
		StoredType* operator -> ();

		/**
		\brief The value as returned by getUnlocked().

		\brief Returns the value as returned by getUnlocked().
		*/
		const StoredType* operator -> () const;

		/**
		\brief The value as returned by getUnlocked().

		\brief Returns the value as returned by getUnlocked().
		*/
		StoredType& operator * ();

		/**
		\brief The value as returned by getUnlocked().

		\brief Returns the value as returned by getUnlocked().
		*/
		const StoredType& operator * () const;
	};

	///\todo implement read/write protection

	template<typename T>
	ProtectedValue<T>::ProtectedValue(StoredType &stored, Mutex& mutex) :
		m_stored(stored),
		m_lock(mutex)
	{}

	template<typename T>
	typename ProtectedValue<T>::StoredType& ProtectedValue<T>::get()
	{
		return m_stored;
	}

	template<typename T>
	const typename ProtectedValue<T>::StoredType& ProtectedValue<T>::get() const
	{
		return m_stored;
	}

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
	typename Protection<T>::StoredType& Protection<T>::getUnlocked()
	{
		return m_stored;
	}

	template<typename T>
	const typename Protection<T>::StoredType& Protection<T>::getUnlocked() const
	{
		return m_stored;
	}

	template<typename T>
	ProtectedValue<typename Protection<T>::StoredType> Protection<T>::getLocked()
	{
		return ProtectedValue<StoredType>(m_stored, m_mutex);
	}

	template<typename T>
	ProtectedValue<const typename Protection<T>::StoredType> Protection<T>::getLocked() const
	{
		return ProtectedValue<const StoredType>(m_stored, m_mutex);
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
		return getUnlocked();
	}

	template<typename T>
	const typename Protection<T>::StoredType& Protection<T>::operator * () const
	{
		return getUnlocked();
	}
}

#endif