#ifndef NOU_MEM_MNGT_POOL_ALLOCATOR_HPP
#define NOU_MEM_MNGT_POOL_ALLOCATOR_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\mem_mngt\Utils.hpp"

namespace NOU::NOU_MEM_MNGT
{
	template <typename T>
	union PoolBlock
	{
		T value;
		PoolBlock<T>* nextPoolBlock;

		PoolBlock() {};
		~PoolBlock() {};
	};

	template <typename T>
	class NOU_CLASS PoolAllocator
	{
	private:

		static constexpr sizeType POOL_ALLOCATOR_DEFAULT_SIZE = 1024;
		static constexpr sizeType BLOCK_BUFFER_DEFAULT_SIZE = 5;

		NOU_DAT_ALG::Vector<PoolBlock<T>*> m_blocks;

		sizeType m_size = 0;

		PoolBlock<T>* m_head = nullptr;

	public:
		explicit PoolAllocator(sizeType size = POOL_ALLOCATOR_DEFAULT_SIZE, 
			AllocationCallback<PoolBlock<T>*> &allocator = GenericAllocationCallback<PoolBlock<T>*>::getInstance());

		PoolAllocator(const PoolAllocator& other)				= delete; //Copy Constructor
		PoolAllocator(const PoolAllocator&& other)				= delete; //Move Constructor
		PoolAllocator& operator=(const PoolAllocator& other)	= delete; //Copy Assignment
		PoolAllocator& operator=(const PoolAllocator&& other)	= delete; //Move Assignment

		~PoolAllocator();

		template <typename... arguments>
		T* allocate(arguments&&... args);

		void deallocate(T* data);
	};

	template <typename T>
	PoolAllocator<T>::PoolAllocator(sizeType size, AllocationCallback<PoolBlock<T>*> &allocator) :
		m_size(size),
		m_blocks(BLOCK_BUFFER_DEFAULT_SIZE, allocator)
	{
		PoolBlock<T>* m_data = new PoolBlock<T>[size];
		m_head = m_data;

		for (sizeType i = 0; i < m_size - 1; i++)
		{
			m_data[i].nextPoolBlock = NOU::NOU_MEM_MNGT::addressof(m_data[i + 1]);
		}
		m_data[m_size - 1].nextPoolBlock = nullptr;

		m_blocks.pushBack(m_data);
	}

	template <typename T>
	PoolAllocator<T>::~PoolAllocator()
	{
		for (PoolBlock<T>* block : m_blocks)
		{
			delete[] block;
			std::cout << "block deleted" << std::endl; ///\Todo delete this line
		}

		m_head = nullptr;
	}

	template <typename T>
	template <typename... arguments>
	T* PoolAllocator<T>::allocate(arguments&&... args)
	{	
		if (m_head == nullptr)
		{
			return nullptr;
		}

		PoolBlock<T>* poolBlock = m_head;
		m_head = m_head->nextPoolBlock;
		T* retVal = new (NOU::NOU_MEM_MNGT::addressof(poolBlock->value))
			T(NOU::NOU_CORE::forward<arguments>(args)...);

		return retVal;	
	}

	template <typename T>
	void PoolAllocator<T>::deallocate(T* data)
	{
		///\TODO what if data is not part of m_data?
		data->~T();
		PoolBlock<T>* poolBlock = reinterpret_cast<PoolBlock<T>*>(data);
		poolBlock->nextPoolBlock = m_head;
		m_head = poolBlock;
	}
}

#endif