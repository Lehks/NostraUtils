#ifndef NOU_MEM_MNGT_POOL_ALLOCATOR_HPP
#define NOU_MEM_MNGT_POOL_ALLOCATOR_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\Vector.hpp"

#include <new>
#include <memory>

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
		static const sizeType POOL_ALLOCATOR_DEFAULT_SIZE = 1024;

		sizeType m_size = 0;

		PoolBlock<T>* m_data = nullptr;
		PoolBlock<T>* m_head = nullptr;

	public:
		explicit PoolAllocator(sizeType size = POOL_ALLOCATOR_DEFAULT_SIZE) :
			m_size(size)
		{
			m_data = new PoolBlock<T>[size];
			m_head = m_data;

			for (sizeType i = 0; i < m_size - 1; i++)
			{
				m_data[i].nextPoolBlock = std::addressof(m_data[i + 1]);
			}
			m_data[m_size - 1].nextPoolBlock = nullptr;
		}

		PoolAllocator(const PoolAllocator& other)				= delete; //Copy Constructor
		PoolAllocator(const PoolAllocator&& other)				= delete; //Move Constructor
		PoolAllocator& operator=(const PoolAllocator& other)	= delete; //Copy Assignment
		PoolAllocator& operator=(const PoolAllocator&& other)	= delete; //Move Assignment

		~PoolAllocator()
		{
			delete[] m_data;
			m_data = nullptr;
			m_head = nullptr;
		}

		template <typename... arguments>
		T* allocate(arguments&&... args)
		{
			if (m_head == nullptr)
			{
				return nullptr;
			}

			PoolBlock<T>* poolBlock = m_head;
			m_head = m_head->nextPoolBlock;
			T* retVal = new (std::addressof(poolBlock->value)) T(std::forward<arguments>(args)...);
			return retVal;
		}

		void deallocate(T* data)
		{
			///\TODO what if data is not part of m_data?
			data->~T();
			PoolBlock<T>* poolBlock = reinterpret_cast<PoolBlock<T>*>(data);
			poolBlock->nextPoolBlock = m_head;
			m_head = poolBlock;
		}
	};
}

#endif