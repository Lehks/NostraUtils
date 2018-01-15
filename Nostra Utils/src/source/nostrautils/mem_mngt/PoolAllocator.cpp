#include "nostrautils\mem_mngt\PoolAllocator.hpp"

namespace NOU::NOU_MEM_MNGT
{

	Memory::Memory(sizeType memSize) :
		m_memSize(memSize),
		m_memSizePtr(&memSize)
	{}

	sizeType Memory::getMemSize()
	{
		return m_memSize;
	}

	sizeType* Memory::getMemSizePtr()
	{
		return m_memSizePtr;
	}

	NOU::NOU_MEM_MNGT::GenericAllocationCallback<const Memory*> PoolAllocator::s_allocator;

	NOU::NOU_DAT_ALG::Vector<const Memory*> PoolAllocator::s_poolAllocator(1, s_allocator);

	sizeType* PoolAllocator::memoryBlock = new sizeType[30];


	PoolAllocator::~PoolAllocator()
	{
		delete[] memoryBlock;
	}
	sizeType PoolAllocator::getPoolAllocatorSize()
	{
		return s_poolAllocator.size();
	}
}