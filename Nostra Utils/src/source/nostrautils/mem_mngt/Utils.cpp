#include "nostrautils/mem_mngt/Utils.hpp"

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
#include <Windows.h>
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#include <stdlib.h>
#endif

namespace NOU::NOU_MEM_MNGT
{
	byte* alignedAlloc(sizeType bytes, sizeType alignment)
	{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
		return reinterpret_cast<byte*>(_aligned_malloc(bytes, alignment));
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
		byte *ret;

		//on success, posix_memalign returns 0, otherwise a nonzero value. if no success, return nullptr
		return posix_memalign(reinterpret_cast<void**>(&ret), alignment, bytes) == 0 ? ret : nullptr;
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