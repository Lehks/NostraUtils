#ifndef NOU_MEM_MNGT_POOL_ALLOCATOR_HPP
#define NOU_MEM_MNGT_POOL_ALLOCATOR_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\Vector.hpp"

namespace NOU::NOU_MEM_MNGT
{
	class NOU_CLASS Memory
	{
	private:

		sizeType m_memSize;

		sizeType* m_memSizePtr;

	public:
		Memory(sizeType memSize);

		sizeType getMemSize();

		sizeType* getMemSizePtr();
	};

	class NOU_CLASS PoolAllocator
	{
	private:

		static NOU::NOU_MEM_MNGT::GenericAllocationCallback<const Memory*> s_allocator;

		static NOU::NOU_DAT_ALG::Vector<const Memory*> s_poolAllocator;

		static sizeType *memoryBlock;

	public:

		~PoolAllocator();
		sizeType getPoolAllocatorSize();


	};
}

#endif