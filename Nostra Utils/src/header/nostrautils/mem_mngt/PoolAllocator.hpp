#ifndef NOU_MEM_MNGT_POOL_ALLOCATOR_HPP
#define NOU_MEM_MNGT_POOL_ALLOCATOR_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/ErrorHandler.hpp"
#include "nostrautils/dat_alg/Vector.hpp"
#include "nostrautils/mem_mngt/Utils.hpp"

/**
\file mem_mngt/PoolAllocator.hpp

\author	 Lukas Gross
\version 0.0.1
\since	 1.0.0

\brief A file that contains the nostra::utils::mem_mngt::PoolAllocator class.
*/
namespace NOU::NOU_MEM_MNGT
{

	/**
	\tparam T	The type of the elements that are stored in the PoolBlock.

	\brief		An union that defines the PoolBlock.
	*/
	template <typename T>
	union PoolBlock
	{
		/**
		brief The value of the PoolBlock.
		*/
		T value;

		/**
		\brief A pointer to the next PoolBlock.
		*/
		PoolBlock<T>* nextPoolBlock;

		PoolBlock() {};
		~PoolBlock() {};
	};

	/**
	\tparam T	The type of the stored elements.

	\brief		A class that defines the PoolAllocator.
	*/
	template <typename T>
	class NOU_CLASS PoolAllocator
	{
	private:
		/**
		\brief Defines the default size of one PoolAllocator.
		*/
		static constexpr sizeType POOL_ALLOCATOR_DEFAULT_SIZE = 1024;

		/**
		\brief Defines the default size of m_blocks.
		*/
		static constexpr sizeType BLOCK_BUFFER_DEFAULT_SIZE = 5;

		/**
		\brief Counts the amount of used PoolAllocator blocks.
		*/
		sizeType m_usedSize = 0;

		/**
		\brief A vector that stores the PoolAllocators.
		*/
		NOU_DAT_ALG::Vector<PoolBlock<T>*> m_blocks;

		/**
		\brief The size of the PoolAllocator. 
		*/
		sizeType m_size = 0;

		/**
		\brief A null pointer which points to the head of the PoolBlocks. 
		*/
		PoolBlock<T>* m_head = nullptr;

	public:

		/**
		\param size			The size of the PoolAllocator. Can be set manually or can use the default size.

		\param allocator	Reference to an AllocationCallback that is used for initializing the m_blocks
							vector.

		\brief				Constructs a new PoolAllocator. Calls the newPool(sizeType size), which creates 
							the PoolAllocator.
		*/
		explicit PoolAllocator(sizeType size = POOL_ALLOCATOR_DEFAULT_SIZE, 
			AllocationCallback<PoolBlock<T>*> &allocator = 
			GenericAllocationCallback<PoolBlock<T>*>::getInstance());

		/**
		\brief Deleted copy constructor.
		*/
		PoolAllocator(const PoolAllocator& other)				= delete;

		/**
		\brief Deleted move constructor.
		*/
		PoolAllocator(const PoolAllocator&& other)				= delete;

		/**
		\brief Deleted copy assignment.
		*/
		PoolAllocator& operator=(const PoolAllocator& other)	= delete;

		/**
		\brief Deleted move assignment.
		*/
		PoolAllocator& operator=(const PoolAllocator&& other)	= delete;

		/**
		\param size	The size of the new PoolAllocator. Can be set manually or can use the default size.

		\brief		Creates new PoolBlocks which are stored in the m_blocks vector. When a new PoolBlock is
					created, the last element of the old one points to the new one.
		*/
		void newPool(sizeType size = POOL_ALLOCATOR_DEFAULT_SIZE);

		/**
		\brief Destructor of the PoolAllocator. Deletes the PoolBlocks and sets m_head to null pointer.
		*/
		~PoolAllocator();

		/**
		\tparam arguments	The type of passed arguments to the method.
		\param args			The passed arguments.

		\return				Returns a pointer to an object of type T.

		\brief				Allocates the PoolBlocks for the objects.
		*/
		template <typename... arguments>
		T* allocate(arguments&&... args);

		/**
		\param data	A pointer of type T to the object that will be deallocated.

		\brief		Deallocates the PoolBlock that stores the passed element.
		*/
		void deallocate(T* data);
	};

	template <typename T>
	PoolAllocator<T>::PoolAllocator(sizeType size, AllocationCallback<PoolBlock<T>*> &allocator) :
		m_size(size),
		m_blocks(BLOCK_BUFFER_DEFAULT_SIZE, allocator)
	{
		newPool(size);
	}

	template <typename T>
	PoolAllocator<T>::~PoolAllocator()
	{
		for (PoolBlock<T>* block : m_blocks)
		{
			delete[] block;
		}
		
		m_head = nullptr;
	}

	template <typename T>
	void PoolAllocator<T>::newPool(sizeType size)
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
	template <typename... arguments>
	T* PoolAllocator<T>::allocate(arguments&&... args)
	{	
		if (PoolAllocator<T>::m_usedSize == m_blocks.size() * m_size)
		{
			newPool();
			m_head = m_blocks.at(m_blocks.size() - 1);
		}

		if (m_head == nullptr)
		{
			return nullptr;
		}

		m_usedSize++;
		PoolBlock<T>* poolBlock = m_head;
		m_head = m_head->nextPoolBlock;
		T* retVal = new (NOU::NOU_MEM_MNGT::addressof(poolBlock->value))
			T(NOU::NOU_CORE::forward<arguments>(args)...);

		return retVal;
	}

	template <typename T>
	void PoolAllocator<T>::deallocate(T* data)
	{
		if (data == nullptr)
			return;

#ifdef NOU_DEBUG
		boolean found = false;

		for (sizeType i = 0; i < m_blocks.size() && !found; i++)
		{
			if (static_cast<void*>(data) >= static_cast<void*>(m_blocks[i]) && 
				static_cast<void*>(data) <= static_cast<void*>(m_blocks[i] + POOL_ALLOCATOR_DEFAULT_SIZE))
				found = true;
		}

		if (!found)
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::BAD_DEALLOCATION, 
				"A chunk of data passed to a PoolAllocator was not allocated using that allocator.");
		
			return;
		}
#endif
		data->~T();
		PoolBlock<T>* poolBlock = reinterpret_cast<PoolBlock<T>*>(data);
		poolBlock->nextPoolBlock = m_head;
		m_head = poolBlock;
		m_usedSize--;
	}
}

#endif