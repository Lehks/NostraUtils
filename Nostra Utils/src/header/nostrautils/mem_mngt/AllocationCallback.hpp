#ifndef	NOU_MEM_MNGT_ALLOCATION_CALLBACK_HPP
#define	NOU_MEM_MNGT_ALLOCATION_CALLBACK_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/mem_mngt/Utils.hpp"

#include <iostream>

/**
\file mem_mngt/AllocationCallback.hpp

\author  Lukas Reichmann
\version 1.0.1
\since   1.0.0

\brief A file that contains some default allocation callbacks.
\see   nostra::utils::mem_mngt::GenericAllocationCallback
*/

namespace NOU::NOU_MEM_MNGT
{
	/**
	\tparam T The type of objects to allocate.

	\brief An allocation callback that calls the functions allocateUninitialized() and 
	       deallocateUninitialized().
	*/
	template<typename T>
	class GenericAllocationCallback final
	{
	public:
		/**
		\param amount The amount of objects to allocate.

		\return A pointer to the allocated block of memory.

		\brief An implementation of AllocationCallback::allocate() that uses the function 
		       allocateUninitialized().
		*/
		T* allocate(sizeType amount = 1);

		/**
		\param data The memory to deallocate.

		\brief An implementation of AllocationCallback::deallocate() that uses the function 
		       deallocateUninitialized().
		*/
		void deallocate(T *data);
	};

	/**
	\tparam T The type of objects to allocate.

	\brief An allocation callback that calls the functions from GenericAllocationCallback<T>, but also 
	       tracks the amount of allocations and deallocations.
	*/
	template<typename T>
	class DebugAllocationCallback final
	{
	private:
		/**
		\brief A counter for the allocations and deallocations. May be negative (if there were more 
		       deallocations than allocations).
		*/
		int64 m_counter;

		GenericAllocationCallback<T> m_callback;

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
		T* allocate(sizeType amount = 1);

		/**
		\param data The memory to deallocate.

		\brief An implementation of AllocationCallback::deallocate() that uses 
		       DebugAllocationCallback<T>::deallocate().
		*/
		void deallocate(T *data);

		/**
		\return m_counter

		\brief Returns m_counter.
		*/
		int64 getCounter() const;
	};

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
		return m_callback.allocate(amount);
	}

	template<typename T>
	void DebugAllocationCallback<T>::deallocate(T *data)
	{
		m_callback.deallocate(data);
		m_counter--;
	}

	template<typename T>
	int64 DebugAllocationCallback<T>::getCounter() const
	{
		return m_counter;
	}
}

#endif