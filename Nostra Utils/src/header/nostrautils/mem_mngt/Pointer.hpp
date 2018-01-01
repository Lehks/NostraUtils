#ifndef NOU_DAT_ALG_POINTER_HPP
#define NOU_DAT_ALG_POINTER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\Utils.hpp"

namespace NOU::NOU_MEM_MNGT
{
	/**
	\tparam T The type of object to delete.

	\brief A deleter that calls <tt>delete<tt>.
	*/
	template<typename T>
	NOU_FUNC void defaultDeleter(T *t);

	/**
	\tparam T The type of object to delete.

	\brief A deleter that calls <tt>delete[]<tt>.
	*/
	template<typename T>
	NOU_FUNC void defaultArrayDeleter(T *t);

	/**
	\tparam T The type of object to delete.

	\brief A deleter that calls nostra::utils::mem_mngt::deallocateUninitialized.
	*/
	template<typename T>
	NOU_FUNC void uninitializedDeleter(T *t);

	/**
	\tparam T The type of object to delete.

	\brief A deleter that calls no functions at all. This can be used if a pointer wrapps around a pointer to
	       memory that does not need to be freed.
	*/
	template<typename T>
	NOU_FUNC void nullDeleter(T *t);

	/**
	\tparam The type of the object that this smart pointer should point to.

	\brief The common parent class of all smart pointers.

	\details
	The common parent class of all smart pointers. This class has all member functions that support the usual
	pointer operations, but does not manage memory.

	\note
	This class is not meant to be used directly by a user.
	*/
	template<typename T>
	class SmartPtrTempl
	{
	public:
		/**
		\brief The type of the object that the pointer points to.
		*/
		using Type = T;

	protected:
		/**
		\brief The pointer that the smart pointer is wrapping around.
		*/
		Type*      m_ptr;

	public:
		/**
		\param ptr     The pointer to wrap around.

		\brief Constructs a new SmartPtrTempl and initializes it's internal pointer with the passed parameter.
		*/
		SmartPtrTempl(T *ptr);

		/**
		\return The raw pointer.

		\brief Returns the pointer that this smart pointer wraps around.
		*/
		Type* rawPtr();

		/**
		\return The raw pointer.

		\brief Returns the pointer that this smart pointer wraps around.
		*/
		const Type* rawPtr() const;

		/**
		\return rawPtr()[\p index]
		*/
		Type& operator [] (sizeType index);

		/**
		\return rawPtr()[\p index]
		*/
		const Type& operator [] (sizeType index) const;

		/**
		\return rawPtr()->
		*/
		Type* operator -> ();

		/**
		\return rawPtr()->
		*/
		const Type* operator -> () const;

		/**
		\return *(rawPtr())
		*/
		Type& operator * ();

		/**
		\return *(rawPtr())
		*/
		const Type& operator * () const;

		/**
		\return &(rawPtr())
		*/
		Type** operator & ();

		/**
		\return &(rawPtr())
		*/
		const Type* const * operator & () const;

		/**
		\return True, if the internal pointer is not null, false if it is.
		*/
		operator boolean () const;

		/**
		\return rawPtr() <= other.rawPtr()
		*/
		boolean operator <= (const SmartPtrTempl &other);

		/**
		\return rawPtr() >= other.rawPtr()
		*/
		boolean operator >= (const SmartPtrTempl &other);

		/**
		\return rawPtr() < other.rawPtr()
		*/
		boolean operator > (const SmartPtrTempl &other);

		/**
		\return rawPtr() > other.rawPtr()
		*/
		boolean operator < (const SmartPtrTempl &other);

		/**
		\return rawPtr() == other.rawPtr()
		*/
		boolean operator == (const SmartPtrTempl &other);

		/**
		\return rawPtr() != other.rawPtr()
		*/
		boolean operator != (const SmartPtrTempl &other);
	}; 

	/**
	\tparam T The type of object to delete.

	\brief If a function pointer is passed to a smart pointer as a deleter, this function pointer must have
	this signature. Also, if a class type is passed as a deleter, the function call operator must be
	overloaded in a way that the class can be called as if it was a function of this type.
	*/
	template<typename T>
	using DeleterFunc = void(*) (typename SmartPtrTempl<T>::Type*);

	/**
	\tparam The type of the object that this smart pointer should point to.
	\tparam The type of the deleter. This type needs to have the function call operator overloaded. This
	        operator needs to be defined as
			\code{.cpp}
			void operator () (T*);
			\endcode

	\brief The common parent class of all smart pointers that delete their memory.

	\details
	The common parent class of all smart pointers. This class has all member functions that support the usual
	pointer operations, but does not manage memory.

	\note
	This class is not meant to be used directly by a user.
	*/
	template<typename T, typename DELETER>
	class NOU_CLASS ManagedPtrTemplate
	{
	public:
		/**
		\brief The type of the object that the pointer points to.
		*/
		using Type = typename SmartPtrTempl<T>::Type;

	protected:
		/**
		\brief The deleter that is used by the other pointer types. However, this deleter needs to be called
		manually by every smart pointer, it is just stored here.
		*/
		DELETER m_deleter; //not called!

	public:
		/**
		\param deleter The deleter.

		\brief Constructs a new ManagedPtrTemplate and initializes it's deleter with the passed parameter.
		*/
		ManagedPtrTemplate(DELETER deleter);

		/**
		\return The deleter.

		\brief Returns the deleter.
		*/
		DELETER deleter() const;

	};

	/**
	\tparam The type of the object that this smart pointer should point to.
	*/
	template<typename T, typename DELETER = void(*)(typename SmartPtrTempl<T>::Type*)>
	class NOU_CLASS UniquePtr final :  public SmartPtrTempl<T>, public ManagedPtrTemplate<T, DELETER>
	{
	public:
		using Type = typename SmartPtrTempl<T>::Type;

	public:
		UniquePtr(Type *ptr = nullptr, DELETER deleter = defaultDeleter);
		UniquePtr(UniquePtr &&other);

		~UniquePtr();

		UniquePtr& operator = (UniquePtr &&other);
	};

	template<typename T>
	void defaultDeleter(T *t)
	{
		delete t;
	}

	template<typename T>
	void defaultArrayDeleter(T *t)
	{
		delete[] t
	}

	template<typename T>
	void uninitializedDeleter(T *t)
	{
		deallocateUninitialized(t);
	}

	template<typename T>
	void nullDeleter(T *t)
	{
		//Do nothing
	}

	template<typename T>
	SmartPtrTempl<T>::SmartPtrTempl(T *ptr) :
		m_ptr(ptr)
	{}

	template<typename T>
	typename SmartPtrTempl<T>::Type* SmartPtrTempl<T>::rawPtr()
	{
		return m_ptr;
	}

	template<typename T>
	const typename SmartPtrTempl<T>::Type* SmartPtrTempl<T>::rawPtr() const
	{
		return m_ptr;
	}

	template<typename T>
	typename SmartPtrTempl<T>::Type& SmartPtrTempl<T>::operator [] (sizeType index)
	{
		return m_ptr[index];
	}

	template<typename T>
	const typename SmartPtrTempl<T>::Type& SmartPtrTempl<T>::operator [] (sizeType index) const
	{
		return m_ptr[index];
	}

	template<typename T>
	typename SmartPtrTempl<T>::Type* SmartPtrTempl<T>::operator -> ()
	{
		return m_ptr;
	}

	template<typename T>
	const typename SmartPtrTempl<T>::Type* SmartPtrTempl<T>::operator -> () const
	{
		return m_ptr;
	}

	template<typename T>
	typename SmartPtrTempl<T>::Type& SmartPtrTempl<T>::operator * ()
	{
		return *m_ptr;
	}

	template<typename T>
	const typename SmartPtrTempl<T>::Type& SmartPtrTempl<T>::operator * () const
	{
		return *m_ptr;
	}

	template<typename T>
	typename SmartPtrTempl<T>::Type** SmartPtrTempl<T>::operator & ()
	{
		return &m_ptr;
	}

	template<typename T>
	const typename SmartPtrTempl<T>::Type* const * SmartPtrTempl<T>::operator & () const
	{
		return &m_ptr;
	}

	template<typename T>
	SmartPtrTempl<T>::operator boolean () const
	{
		return m_ptr != nullptr;
	}

	template<typename T>
	boolean SmartPtrTempl<T>::operator <= (const SmartPtrTempl<T> &other)
	{
		return m_ptr <= other.m_ptr;
	}

	template<typename T>
	boolean SmartPtrTempl<T>::operator >= (const SmartPtrTempl<T> &other)
	{
		return m_ptr >= other.m_ptr;
	}

	template<typename T>
	boolean SmartPtrTempl<T>::operator > (const SmartPtrTempl<T> &other)
	{
		return m_ptr > other.m_ptr;
	}

	template<typename T>
	boolean SmartPtrTempl<T>::operator < (const SmartPtrTempl<T> &other)
	{
		return m_ptr < other.m_ptr;
	}

	template<typename T>
	boolean SmartPtrTempl<T>::operator == (const SmartPtrTempl<T> &other)
	{
		return m_ptr == other.m_ptr;
	}

	template<typename T>
	boolean SmartPtrTempl<T>::operator != (const SmartPtrTempl<T> &other)
	{
		return m_ptr != other.m_ptr;
	}

	template<typename T, typename DELETER>
	ManagedPtrTemplate<T, DELETER>::ManagedPtrTemplate(DELETER deleter) :
		m_deleter(deleter)
	{}

	template<typename T, typename DELETER>
	DELETER ManagedPtrTemplate<T, DELETER>::deleter() const
	{
		return m_deleter;
	}

	template<typename T, typename DELETER>
	UniquePtr<T, DELETER>::UniquePtr(Type *ptr, DELETER deleter) :
		SmartPtrTempl(ptr),
		ManagedPtrTemplate(deleter)
	{}

	template<typename T, typename DELETER>
	UniquePtr<T, DELETER>::UniquePtr(UniquePtr<T, DELETER> &&other) :
		UniquePtr(other.rawPtr(), other.deleter())
	{
		other.m_ptr = nullptr;
	}

	template<typename T, typename DELETER>
	UniquePtr<T, DELETER>::~UniquePtr()
	{
		m_deleter(m_ptr);
	}

	template<typename T, typename DELETER>
	UniquePtr<T, DELETER>& UniquePtr<T, DELETER>::operator = (UniquePtr<T, DELETER> &&other)
	{
		this->~UniquePtr();

		m_ptr = other.rawPtr();
		other.m_ptr = nullptr;

		return *this;
	}
}

#endif