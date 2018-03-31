#ifndef	NOU_DAT_ALG_UNINITIALIZED_HPP
#define	NOU_DAT_ALG_UNINITIALIZED_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Utils.hpp"
#include "nostrautils/core/ErrorHandler.hpp"

/** 
\file    dat_alg\Uninitialized.hpp
\author  Lukas Reichmann
\since   0.0.1
\version 1.0
\brief   This file contains a container that can store an object that is meant to be initialized later.
*/

namespace NOU::NOU_DAT_ALG
{
	/**
	\tparam T The type of object that will be stored in the class.

	\brief This container allocates (stack-) memory for an object without necessary calling the constructor.

	\details
	This container allocates (stack-) memory for an object without necessary calling the constructor.
	If no constructor has been called yet, the container is in an invalid state (isValid() will return false).
	While the container is in that state, it is forbidden to work with the stored object (since there is no 
	actual object, just data junk). Doing so will set an INVALID_OBJECT error in the error handler.

	Once the container was validated, it can be invalidated again using destroy().

	An instance of this class that has a primitive type is pointless, since primitive types provide such an 
	uninitialized behavior by default.
	*/
	template<typename T>
	class NOU_CLASS Uninitialized final
	{
	private:
		/**
		\brief The data that stores the object.
		*/
		byte    m_dataChunk[sizeof(T)] alignas (T);

		/**
		\brief True, if the object has been initialized, false if not.
		*/
		boolean m_constructorCalled;

	public:
		/**
		\brief Constructs a new instance in an invalid state.
		*/
		Uninitialized();

		/**
		\param args  The arguments that will be passed to the constructor of the stored object.
		\tparam ARGS The type of the arguments.

		\brief Constructs a new instance in a valid state using the passed arguments to createFile
		an instance of the stored class.

		\details
		Constructs a new instance in a valid state using the passed arguments to createFile
		an instance of the stored class. It is not recommended to use this constructor since
		it bypasses the use of an Uninitialized instance.
		*/
		template<typename... ARGS>
		Uninitialized(ARGS&&... args);

		/**
		\param other The instance to copy the data from.

		\brief The copy constructor.
		*/
		Uninitialized(const Uninitialized<T> &other);

		/**
		\param other The instance to move the data from.

		\brief The move constructor.
		*/
		Uninitialized(Uninitialized<T> &&other);

		/**
		\brief Destroys an instance of an Uninitialized.

		\details
		Destroys an instance of an Uninitialized. This also calls the destructor
		of the stored object, if it was initialized.
		*/
		~Uninitialized();

		/**
		\return True, if the object stored in the container is valid, false
		if not.
		\brief  Returns true, if the object stored in the container is valid,
		false if not.
		*/
		boolean isValid() const;

		/**
		\brief Manually sets the state of the instance to the valid state.

		\details
		Manually sets the state of the instance to the valid state. This can be used to e.g. enhance 
		compatibility with functions that return values via the parameter list.

		E.g.:
		\code
		Uninitialized<String> str;

		/*
		 * void someFunction(String *str) is an exemplary function that writes the result to the string that
		 * was passed to it (it constructs a new string and does not work with any potentially already 
		 * pre-constructed that are passed to it).
		 *\/
		someFunction(str.data());
		str.makeValid();
		\endcode

		In this example, assuming that the construction of a String object is rather expensive (e.g. if 
		dynamic allocations have to be done), using an Uninitialized is also a performance boost.

		\warning 
		This method should only be with care, as it can lead to objects not being destructed or destructors 
		getting called on unallocated memory.
		*/
		void makeValid();

		/**
		\brief Deconstructs the stored object.

		\details
		Deconstructs the stored object. If there is no valid object stored, nothing will happen. After calling
		this method, isValid() will return false.
		*/
		void destroy();

		/**
		\param args  The arguments that will be passed to the constructor of the stored object.
		\tparam ARGS The type of the arguments.

		\brief Initializes the stored object with the constructor that matches the types
		of the passed arguments.

		\details
		Initializes the stored object with the constructor that matches the types of the
		passed arguments.
		This method does the same as the operator =.
		*/
		template<typename... ARGS>
		void set(ARGS&&... args);

		/**
		\return A pointer to the stored object.
		\brief  Returns a pointer to the stored object.
		*/
		T* data();

		/**
		\return A const pointer to the stored object.
		\brief  Returns a const pointer to the stored object.
		*/
		const T* data() const;

		/**
		\return A pointer to the stored object.
		\brief  Returns a pointer to the stored object for direct access of
		methods.
		*/
		T* operator -> ();

		/**
		\return A const pointer to the stored object.
		\brief  Returns a const pointer to the stored object for direct
		access of methods.
		*/
		const T* operator -> () const;

		/**
		\return A reference to the stored object.
		\brief  Returns a reference to the stored object.
		*/
		T& operator * ();

		/**
		\return A const reference to the stored object.
		\brief  Returns a const reference to the stored object.
		*/
		const T& operator * () const;

		/**
		\param args  The arguments that will be passed to the constructor of the stored object.
		\tparam ARGS The type of the arguments.
		\return      A reference to itself.

		\brief Initializes the stored object with the constructor that matches the types
		of the passed arguments.

		\details
		Initializes the stored object with the constructor that matches the types of the
		passed arguments.
		This operator does the same as set().
		*/
		template<typename... ARGS>
		Uninitialized& operator = (ARGS&&... args);


		/**
		\param other The instance to copy the data from.

		\brief The copy assignment operator.
		*/
		Uninitialized& operator = (const Uninitialized &other);

		/**
		\param other The instance to move the data from.

		\brief The move assignment operator.
		*/
		Uninitialized& operator = (Uninitialized &&other);

		/**
		\return The stored object.
		\brief Implicitly converts the instance to a reference to the stored object.
		*/
		operator T& ();

		/**
		\return The stored object.
		\brief Implicitly converts the instance to a const reference to the stored object.
		*/
		operator const T& () const;
	};

	template<typename T>
	Uninitialized<T>::Uninitialized() : m_constructorCalled(false)
	{}

	template<typename T>
	template<typename... ARGS>
	Uninitialized<T>::Uninitialized(ARGS&&... args) : m_constructorCalled(true)
	{
		new ((T*)(m_dataChunk)) T(NOU_CORE::forward<ARGS...>(args...));
	}

	template<typename T>
	Uninitialized<T>::Uninitialized(const Uninitialized<T> &other) : 
		m_constructorCalled(other.m_constructorCalled)
	{
		if (isValid()) //only copy if valid obj
			new ((T*)(m_dataChunk)) T(*other);
	}

	template<typename T>
	Uninitialized<T>::Uninitialized(Uninitialized<T> &&other) : 
		m_constructorCalled(other.m_constructorCalled)
	{
		if (isValid()) //only move if valid obj
			new ((T*)(m_dataChunk)) T(NOU_CORE::move(*other));
	}

	template<typename T>
	Uninitialized<T>::~Uninitialized()
	{
		destroy();
	}

	template<typename T>
	boolean Uninitialized<T>::isValid() const
	{
		return m_constructorCalled;
	}

	template<typename T>
	void Uninitialized<T>::makeValid()
	{
		m_constructorCalled = true;
	}

	template<typename T>
	void Uninitialized<T>::destroy()
	{
		if (isValid())
		{
			data()->~T();
			m_constructorCalled = false;
		}
	}

	template<typename T>
	template<typename... ARGS>
	void Uninitialized<T>::set(ARGS&&... args)
	{
		if (m_constructorCalled)
			data()->~T();

		new ((T*)(m_dataChunk)) T(NOU_CORE::forward<ARGS>(args)...);

		m_constructorCalled = true;
	}

	template<typename T>
	T* Uninitialized<T>::data()
	{
			NOU_COND_PUSH_DBG_ERROR(!isValid(), NOU_CORE::getErrorHandler(), 
				NOU_CORE::ErrorCodes::INVALID_OBJECT, "The object is not initialized yet.");

		return (T*)(m_dataChunk);
	}

	template<typename T>
	const T* Uninitialized<T>::data() const
	{
		NOU_COND_PUSH_DBG_ERROR(!isValid(), NOU_CORE::getErrorHandler(),
			NOU_CORE::ErrorCodes::INVALID_OBJECT, "The object is not initialized yet.");

		return (T*)(m_dataChunk);
	}

	template<typename T>
	T* Uninitialized<T>::operator -> ()
	{
		return data();
	}

	template<typename T>
	const T* Uninitialized<T>::operator -> () const
	{
		return data();
	}

	template<typename T>
	T& Uninitialized<T>::operator * ()
	{
		return *data();
	}

	template<typename T>
	const T& Uninitialized<T>::operator * () const
	{
		return *data();
	}

	///\cond

	template<typename T>
	template<typename... ARGS>
	Uninitialized<T>& Uninitialized<T>::operator = (ARGS&&... args)
	{
		set(NOU_CORE::forward<ARGS>(args)...);

		return *this;
	}

	template<typename T>
	Uninitialized<T>& Uninitialized<T>::operator = (const Uninitialized &other)
	{
		if (other.isValid())
			set(*other);

		m_constructorCalled = other.m_constructorCalled;

		return *this;
	}

	template<typename T>
	Uninitialized<T>& Uninitialized<T>::operator = (Uninitialized &&other)
	{
		if (other.isValid())
			set(NOU_CORE::move(*other));

		m_constructorCalled = other.m_constructorCalled;

		return *this;
	}

	template<typename T>
	Uninitialized<T>::operator T& ()
	{
		return *data();
	}

	template<typename T>
	Uninitialized<T>::operator const T& () const
	{
		return *data();
	}

	///\endcond
}

#endif