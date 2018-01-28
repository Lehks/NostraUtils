#ifndef NOU_DAT_ALG_POINTER_HPP
#define NOU_DAT_ALG_POINTER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\Utils.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\core\Meta.hpp"

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
	\tparam T The type of object to delete.

	\brief A Deleter for Smart Pointers that wrapps nostra::utils::mem_mngt::AllocationCallback::deallocate.
	This version does store it's Callback, so the Callback will be stored in the class itself.

	\details
	Alltough this class is designed to work with childclasses of nostra::utils::mem_mngt::AllocationCallback,
	it works with all classes that have a <tt>.deallocate()</tt> member function.
	*/
	template<typename T, typename ALLOCATOR>
	class NOU_CLASS AllocationCallbackDeleter
	{
	private:
		/**
		\brief The AllocationCallback.
		*/
		ALLOCATOR m_allocator;

	public:
		/**
		\param allocator The AllocationCallback that will be used.

		\brief Constructs a new AllocationCallbackDeleter.
		*/
		AllocationCallbackDeleter(ALLOCATOR &allocator);

		virtual ~AllocationCallbackDeleter() = default;

		/**
		\return m_allocator.

		\brief Returns m_allocator.
		*/
		const ALLOCATOR& getAllocator() const;

		/**
		\return m_allocator.

		\brief Returns m_allocator.
		*/
		ALLOCATOR& getAllocator();

		/**
		\param data A pointer to the data that will be deallocated.

		\brief Calls nostra::utils::mem_mngt::AllocationCallback::deallocate.
		*/
		void operator () (T *data);
	};

	/**
	\tparam T The type of object to delete.

	\brief A Deleter for Smart Pointers that wrapps nostra::utils::mem_mngt::AllocationCallback::deallocate.
	This version does not store it's Callback, so the Callback that was passed to the constructor must
	be alive for the entire time that this Deleter is used.
	*/
	template<typename T>
	class NOU_CLASS AllocationCallbackRefDeleter
	{
	private:
		/**
		\brief The AllocationCallback.
		*/
		NOU_MEM_MNGT::AllocationCallback<T> &m_allocator;

	public:
		/**
		\param allocator The AllocationCallback that will be used.

		\brief Constructs a new AllocationCallbackRefDeleter.
		*/
		AllocationCallbackRefDeleter(NOU_MEM_MNGT::AllocationCallback<T> &allocator);

		virtual ~AllocationCallbackRefDeleter() = default;

		/**
		\return m_allocator.

		\brief Returns m_allocator.
		*/
		const NOU_MEM_MNGT::AllocationCallback<T>& getAllocator() const;

		/**
		\return m_allocator.

		\brief Returns m_allocator.
		*/
		NOU_MEM_MNGT::AllocationCallback<T>& getAllocator();

		/**
		\param data A pointer to the data that will be deallocated.

		\brief Calls nostra::utils::mem_mngt::AllocationCallback::deallocate.
		*/
		void operator () (T *data);
	};

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
	class NOU_FUNC SmartPtrTempl
	{
	public:
		/**
		\brief The processed, actually used, type of the object that the pointer points to.
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

		virtual ~SmartPtrTmpl() = default;

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
		\brief The processed, actually used, type of the object that the pointer points to.
		*/
		using Type = typename SmartPtrTempl<T>::Type;

		static_assert(NOU_CORE::IsInvocable<DELETER, Type*>::value);

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

		virtual ~ManagedPtrTemplate() = default;

		/**
		\return The deleter.

		\brief Returns the deleter.
		*/
		DELETER deleter() const;

	};

	/**
	\tparam T       The type of the object that this smart pointer should point to.
	\tparam DELETER The type of the deleter. See nostra::utils::mem_mngt::ManagedPtrTemplate for the
	requirements that such a deleter must obey.

	\brief A smart pointer that does not allow any other smart pointers to point to it's own pointer.
	*/
	template<typename T, typename DELETER = DeleterFunc<T>>
	class NOU_CLASS UniquePtr final : public SmartPtrTempl<T>, public ManagedPtrTemplate<T, DELETER>
	{
	public:
		/**
		\brief The processed, actually used, type of the object that the pointer points to.
		*/
		using Type = typename SmartPtrTempl<T>::Type;

	public:
		/**
		\param ptr     The pointer that this smart pointer wraps around.
		\param deleter The deleter that will be used to delete the data that this pointer points to.

		\brief Constructs a new UniquePtr.
		*/
		UniquePtr(Type *ptr, DELETER deleter);

		/**
		\param other The pointer to move the data from.

		\brief Move the data from \p other to this instance.
		*/
		UniquePtr(UniquePtr &&other);

		/**
		\brief When called, deletes the data that this pointer points to.
		*/
		virtual ~UniquePtr();

		/**
		\param other The pointer to move the data from.

		\return A reference to the instance itself.

		\brief Move the data from \p other to this instance.
		*/
		UniquePtr& operator = (UniquePtr &&other);

		/**
		\param ptr The new pointer.
		\return A reference to the instance itself.

		\brief Sets a new pointer value. The old data will be deleted.
		*/
		UniquePtr& operator = (Type *ptr);
	};

	template<typename T>
	void defaultDeleter(T *t)
	{
		delete t;
	}

	template<typename T>
	void defaultArrayDeleter(T *t)
	{
		delete[] t;
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

	template<typename T, typename ALLOCATOR>
	AllocationCallbackDeleter<T, ALLOCATOR>::AllocationCallbackDeleter(ALLOCATOR &allocator) :
		m_allocator(allocator)
	{}

	template<typename T, typename ALLOCATOR>
	const ALLOCATOR& AllocationCallbackDeleter<T, ALLOCATOR>::getAllocator() const
	{
		return m_allocator;
	}

	template<typename T, typename ALLOCATOR>
	ALLOCATOR& AllocationCallbackDeleter<T, ALLOCATOR>::getAllocator()
	{
		return m_allocator;
	}

	template<typename T, typename ALLOCATOR>
	void AllocationCallbackDeleter<T, ALLOCATOR>::operator () (T *data)
	{
		m_allocator.deallocate(data);
	}

	template<typename T>
	AllocationCallbackRefDeleter<T>::
		AllocationCallbackRefDeleter(NOU_MEM_MNGT::AllocationCallback<T> &allocator) :
		m_allocator(allocator)
	{}

	template<typename T>
	const NOU_MEM_MNGT::AllocationCallback<T>& AllocationCallbackRefDeleter<T>::getAllocator() const
	{
		m_allocator.dellocate(data);
	}

	template<typename T>
	NOU_MEM_MNGT::AllocationCallback<T>& AllocationCallbackRefDeleter<T>::getAllocator()
	{
		m_allocator.dellocate(data);
	}

	template<typename T>
	void AllocationCallbackRefDeleter<T>::operator () (T *data)
	{
		m_allocator.deallocate(data);
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
		SmartPtrTempl<T>(ptr),
		ManagedPtrTemplate<T, DELETER>(deleter)
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
		ManagedPtrTemplate<T, DELETER>::m_deleter(SmartPtrTempl<T>::m_ptr);
	}

	template<typename T, typename DELETER>
	UniquePtr<T, DELETER>& UniquePtr<T, DELETER>::operator = (UniquePtr<T, DELETER> &&other)
	{
		this->~UniquePtr();

		SmartPtrTempl<T>::m_ptr = other.rawPtr();
		other.m_ptr = nullptr;

		return *this;
	}

	template<typename T, typename DELETER>
	UniquePtr<T, DELETER>& UniquePtr<T, DELETER>::operator = (Type *ptr)
	{
		ManagedPtrTemplate<T, DELETER>::m_deleter(SmartPtrTempl<T>::m_ptr);
		SmartPtrTempl<T>::m_ptr = ptr;

		return *this;
	}
}

#endif