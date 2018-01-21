#ifndef	NOU_MEM_MNGT_ALLOCATION_CALLBACK_HPP
#define	NOU_MEM_MNGT_ALLOCATION_CALLBACK_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\Utils.hpp"

/**
\file mem_mngt/AllocationCallback.hpp

\author  Lukas Reichmann
\version 1.0.0
\since   1.0.0

\brief A file that contains the nostra::utils::mem_mngt::AllocationCallback interface. 
\see   nostra::utils::mem_mngt::AllocationCallback
\see   nostra::utils::mem_mngt::GenericAllocationCallback
*/

namespace NOU::NOU_MEM_MNGT
{
	/**
	\tparam T The type of objects to allocate.

	\brief A class that defines a unified interface that is used to allocate and deallocate memory.
	*/
	template<typename T>
	class NOU_CLASS AllocationCallback
	{
	public:

		virtual AllocationCallback() = default;

		/**
		\param amount The amount of objects to allocate.

		\return A pointer to the allocated memory.

		\brief Allocates enough memory to hold \p amount instances of the type \p T.

		\details
		Allocates enough memory to hold \p amount instances of the type \p T. This function may or may not 
		call constructors. Alltough the behaviour of calling constructors may change from allocation callback 
		to allocation callback, it must be consistent along the usage of the same allocator class.
		The memory allocated with this function must be deallocatable using the deallocate() function of the 
		same allocation callback.
		*/
		virtual T* allocate(sizeType amount = 1) = 0;

		/**
		\param data The block of memory to deallocate.

		\brief Deallocates memory that was previously allocated by the same allocation callback. 

		\details
		Deallocates memory that was previously allocated by the same allocation callback. This function
		may or may not call destructors. Alltough the behaviour of calling destructors may change from 
		allocation callback to allocation callback, it must be consistent along the usage of the same 
		allocator class.

		\note 
		It is only requiered that the same allocation callback that allocated memory can also deallocate the
		same memory, however it is allowed for an allocation callback to also deallocate the memory of another
		callback. This behavior is never defined and may or may not result in a propper deallocation.
		*/
		virtual void deallocate(T *data) = 0;
	};

	/**
	\tparam T The type of objects to allocate.

	\brief An allocation callback that calls the functions allocateUninitialized() and 
	       deallocateUninitialized(). This callback does not call any constructors or destructors.

	\details
	An allocation callback that calls the functions allocateUninitialized() and deallocateUninitialized(). 
	This callback does not call any constructors or destructors. 
	Since this callback always calls the same functions, it is not necessary to create new instances. 
	Therefore, the class a static member that can be used. This can be accessed using getInstance().
	*/
	template<typename T>
	class NOU_CLASS GenericAllocationCallback final : public AllocationCallback<T>
	{
	private:
		/**
		\brief A static instance of this class.
		*/
		static GenericAllocationCallback s_instance;

	public:
		/**
		\return s_instance

		\brief Returns the static instance of this class.
		*/
		static GenericAllocationCallback<T>& getInstance();

		/**
		\param amount The amount of objects to allocate.

		\return A pointer to the allocated block of memory.

		\brief An implementation of AllocationCallback::allocate() that uses the function 
		       allocateUninitialized().
		*/
		virtual T* allocate(sizeType amount = 1) override;

		/**
		\param data The memory to deallocate.

		\brief An implementation of AllocationCallback::deallocate() that uses the function 
		       deallocateUninitialized().
		*/
		virtual void deallocate(T *data) override;
	};

	/**
	\tparam T The type of objects to allocate.

	\brief An allocation callback that calls the functions from GenericAllocationCallback<T>, but also 
	       tracks the amount of allocations and deallocations.
	*/
	template<typename T>
	class NOU_CLASS DebugAllocationCallback final : public AllocationCallback<T>
	{
	private:
		/**
		\brief A counter for the allocations and deallocations. May be negative (if there were more 
		       deallocations than allocations).
		*/
		int64 m_counter;

	public:
		/**
		\brief Constructs a new DebugAllocationCallback.
		*/
		DebugAllocationCallback();

		/**
		\param amount The amount of objects to allocate.

		\return A pointer to the allocated block of memory.

		\brief An implementation of AllocationCallback::allocate() that uses 
		       DebugAllocationCallback<T>::allocate().
		*/
		virtual T* allocate(sizeType amount = 1) override;

		/**
		\param data The memory to deallocate.

		\brief An implementation of AllocationCallback::deallocate() that uses 
		       DebugAllocationCallback<T>::deallocate().
		*/
		virtual void deallocate(T *data) override;

		/**
		\return m_counter

		\brief Returns m_counter.
		*/
		int64 getCounter() const;
	};

	template<typename T>
	GenericAllocationCallback<T> GenericAllocationCallback<T>::s_instance;

	template<typename T>
	GenericAllocationCallback<T>& GenericAllocationCallback<T>::getInstance()
	{
		return s_instance;
	}

	template<typename T>
	T* GenericAllocationCallback<T>::allocate(sizeType amount)
	{
		return allocateUninitialized<T>(amount);
	}

	template<typename T>
	void GenericAllocationCallback<T>::deallocate(T *data)
	{
		return deallocateUninitialized(data);
	}

	template<typename T>
	DebugAllocationCallback<T>::DebugAllocationCallback() :
		m_counter(0)
	{}

	template<typename T>
	T* DebugAllocationCallback<T>::allocate(sizeType amount)
	{
		m_counter++;
		return GenericAllocationCallback<T>::getInstance().allocate(amount);
	}

	template<typename T>
	void DebugAllocationCallback<T>::deallocate(T *data)
	{
		GenericAllocationCallback<T>::getInstance().deallocate(data);
		m_counter--;
	}

	template<typename T>
	int64 DebugAllocationCallback<T>::getCounter() const
	{
		return m_counter;
	}
}

#endif