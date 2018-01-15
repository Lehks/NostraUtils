#include "nostrautils\mem_mngt\PoolAllocator.hpp"

namespace NOU::NOU_MEM_MNGT
{
	sizeType Memory::getMemSize()
	{
		return m_memSize;
	}

	sizeType* Memory::getMemSizePtr()
	{
		return m_memSizePtr;
	}
}