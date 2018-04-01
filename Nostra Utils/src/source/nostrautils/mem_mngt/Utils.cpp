#include "nostrautils/mem_mngt/Utils.hpp"

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
#include <Windows.h>
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#include <stdlib.h>
#endif

#include <iostream>
#include <string.h>

namespace NOU::NOU_MEM_MNGT
{
	//Local function that calculates the next power of 2.
	sizeType nextPowerOfTwo(sizeType nr)
	{
		nr--;
		nr |= nr >> 1;
		nr |= nr >> 2;
		nr |= nr >> 4;
		nr |= nr >> 8;
		nr |= nr >> 16;
		nr++;

		return nr;
	}

	byte* alignedAlloc(sizeType bytes, sizeType alignment)
	{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		return reinterpret_cast<byte*>(_aligned_malloc(bytes, alignment));
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
		byte *ret = nullptr;

		alignment = alignment + (sizeof(void*) - ((alignment - (alignment / sizeof(void*)) * sizeof(void*)) % sizeof(void*)));

		alignment = nextPowerOfTwo(alignment);

		//on success, posix_memalign returns 0, otherwise a nonzero value. if no success, return nullptr
		int error = posix_memalign(reinterpret_cast<void**>(&ret), alignment, bytes);

		if (error == 0)
			return ret;
		else
			return nullptr;
#endif
	}

	void alignedFree(void *data)
	{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		_aligned_free(data);
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
		free(data);
#endif
	}

	void deallocateUninitialized(void *data)
	{
		alignedFree(data);
	}
}