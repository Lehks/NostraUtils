#ifndef	NOU_MEM_MNGT_UTILS_HPP
#define	NOU_MEM_MNGT_UTILS_HPP

#include "nostrautils\core\StdIncludes.hpp"

/**
\file mem_mngt/Utils.hpp

\author  Lukas Reichmann
\version 0.0.1
\since   1.0.0

\brief A file that contains utility functions that revolve around memory allocation.
*/

namespace NOU::NOU_MEM_MNGT
{
	/**
	\param bytes     The amount of bytes to allocate.
	\param alignment The alignment that the allocated memory block should have.

	\return A pointer to the allocated block of memory, or nullptr if the allocation was not successful.

	\brief Allocates a block of memory with a certain alignment.
	*/
	NOU_FUNC byte* alignedAlloc(sizeType bytes, sizeType alignment);

	/**
	\param data The block of memory to deallocate.

	\brief Deallocates the passed block of memory. This function should be used to deallocate data that was
	       allocated using alignedAlloc().
	*/
	NOU_FUNC void alignedFree(void *data);

	/**
	\tparam The type of object to allocate.

	\param The amount of objects to allocate.

	\return A pointer to the allocated block of memory, or nullptr if the allocation was not successful.

	\brief Allocates a block of memory that is large enough to hold \p amount objects of the type \p t.

	\details
	Allocates a block of memory that is large enough to hold \p amount objects of the type \p t. Internally,
	this function uses alignedAlloc().

	\warning The objects in the returned block of memory have not been constructed yet (use placement new to 
	         construct them).
	*/
	template<typename T>
	NOU_FUNC T* allocateUninitialized(sizeType amount);

	/**
	\param data The data to deallocate.

	\brief Deallocates a block of memory that was allocated using allocateUninitialized().

	\details 
	Deallocates a block of memory that was allocated using allocateUninitialized(). Internally, this function
	uses alignedFree(). This function only exists to have a function with a matching name with 
	allocateUninitialized().

	\warning
	This function does not call any destructors, this has to be done manually by a user.
	*/
	NOU_FUNC void deallocateUninitialized(void *data);

	template<typename T>
	NOU_FUNC T* allocateUninitialized(sizeType amount)
	{
		return static_cast<T*>(alignedAlloc(sizeof(T) * amount, alignof(T)));
	}
}

#endif