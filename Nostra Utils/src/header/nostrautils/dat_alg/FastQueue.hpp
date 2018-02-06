#ifndef NOU_DAT_ALG_FAST_QUEUE_HPP
#define NOU_DAT_ALG_FAST_QUEUE_HPP

#include "nostrautils\core\Utils.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\mem_mngt\Pointer.hpp"
#include "nostrautils\core\ErrorHandler.hpp"

#include <new>

/**
\file core/FastQueue.hpp

\author  Lukas Groﬂ
\author  Lukas Reichmann
\version 0.0.1
\since   1.0.0

\brief A file that contains the nostra::utils::core::FastQueue class.
*/
namespace NOU::NOU_DAT_ALG
{
	/**
	\tparam T The type of the stored elements.
	\brief A simple implementation of a queue which can be used in O(1).
	*/
	template<typename T>
	class NOU_CLASS FastQueue final
	{
	public:
		/**
		\brief Local class alias.
		*/
		using Type = T;

		/**
		\brief The minium capacity of a FastQueue.
		*/
		static constexpr sizeType MIN_CAPACITY = 1;

	private:
		/**
		\brief The allocator that will be used to allocate and deallocate data.
		*/
		NOU_MEM_MNGT::AllocationCallback<Type> &m_allocator;

		/** 
		\Mahan is dumm!
		\brief The max size of the queue.
		*/
		sizeType m_capacity;

		/** 
		\brief The start index of the queue.
		*/
		sizeType m_startIndex;

		/**
		\brief The end index of the queue.
		*/
		sizeType m_endIndex;

		/**
		\brief A pointer to the queue.
		*/
		NOU_MEM_MNGT::UniquePtr<Type, NOU_MEM_MNGT::AllocationCallbackRefDeleter<Type>> m_queue;
		
		/**
		\param src    The source array.
		\param dst    The destination array.
		\param amount The amount of data to copy.

		\brief Copies the data from \p src to \p dst.
		*/
		void copyFromTo(Type *src, Type *dst, sizeType amount);

	public:
		/**
		\param initialCapacity The initial capacity.
		\param allocator       The allocator that will be used to allocate data.
		*/
		FastQueue(sizeType initialCapacity = MIN_CAPACITY, NOU_MEM_MNGT::AllocationCallback<Type> &allocator 
			= NOU_MEM_MNGT::GenericAllocationCallback<Type>::getInstance());

		/**
		\brief Destructs an instance of FastQueue.
		*/
		~FastQueue();

		/**
		\brief Checks if the queue is empty.
		*/
		boolean empty() const;

		/**
		\return The current size of the queue.
		\brief Returns the current size of the queue.
		*/
		sizeType size() const;

		/**
		\param data The element which will be stored in the queue.
		\brief Stores a element in the queue
		*/
		void pushBack(const Type &data);

		/**
		\param data The element which will be stored in the queue.
		\brief Stores a element in the queue
		*/
		void pushBack(Type &&data);

		/**
		\param data The element which will be stored in the queue.
		\brief Calls the pushBack().
		*/
		void push(const Type &data);

		/*
		/**
		\param data The element which will be stored in the queue.
		\brief Calls the pushBack().
		*/
		void push(Type &&data);

		/*
		\return The first element in the queue.
		\brief Returns the first element in the queue.
		*/
		Type popFront();

		/**
		\return The first element in the queue.
		\brief Calls the popFront().
		*/
		Type pop();

		/**
		\return A reference to the first (aka oldest) element in the queue.

		\brief Returns a reference to the first (aka oldest) element in the queue without removing it.
		*/
		const Type& peekFront() const;

		/**
		\return A reference to the first (aka oldest) element in the queue.

		\brief Returns a reference to the first (aka oldest) element in the queue without removing it.
		*/
		Type& peekFront();

		/**
		\return A reference to the first (aka oldest) element in the queue.

		\brief Returns a reference to the first (aka oldest) element in the queue without removing it.
		*/
		const Type& peek() const;

		/**
		\return A reference to the first (aka oldest) element in the queue.

		\brief Returns a reference to the first (aka oldest) element in the queue without removing it.
		*/
		Type& peek();

		/**
		\param index0 The first element.
		\param index1 The second element.
		\brief Swaps two elements of the queue.
		*/
		void swap(sizeType index0, sizeType index1);

		/**
		\return The element at the index \p index in the queue. 

		\brief Returns the element at the index \p index in the queue.
		*/
		Type& at(sizeType index);

		/**
		\return The element at the index \p index in the queue.

		\brief Returns the element at the index \p index in the queue.
		*/
		const Type& at(sizeType index) const;

		/**
		\brief Removes all elements from the queue.
		*/
		void clear();

		/**
		\return The max capacity of the queue.
		\brief Returns the max capacity of the queue.
		*/
		sizeType capacity();

		/**
		\param additionalCapacity The capacity that will be added to the currently existing capacity.

		\brief Ensures that after a call to this method, the capacity will be <u>at least</u> the current 
		       capacity plus \p additionalCapacity.
		*/
		void resize(sizeType additionalCapacity);

		/**
		\return m_allocator.

		\brief Returns m_allocator.
		*/
		const NOU_MEM_MNGT::AllocationCallback<Type>& getAllocationCallback() const;

		/**
		\param index The index of the element that will be returned.
		\return A const reference to the element at the specified index.

		\brief Returns a const reference to the element at the specified index.
		*/
		const Type& operator [] (sizeType index) const;

		/**
		\param index The index of the element that will be returned.
		\return A const reference to the element at the specified index.

		\brief Returns a const reference to the element at the specified index.
		*/
		Type& operator [] (sizeType index);
	};

	template<typename T>
	void FastQueue<T>::copyFromTo(Type *src, Type *dst, sizeType amount)
	{
		for (sizeType i = 0; i < amount; i++)
		{
			new (dst + i) Type(NOU_CORE::move(src[i]));
			src->~Type();
		}
	}

	template<typename T>
	FastQueue<T>::FastQueue(sizeType initialCapacity, NOU_MEM_MNGT::AllocationCallback<Type> &allocator) :
		m_allocator(allocator),
		m_capacity(initialCapacity < MIN_CAPACITY ? MIN_CAPACITY : initialCapacity), ///\todo replace w/ max()
		m_startIndex(0),
		m_endIndex(0),
		m_queue(m_allocator.allocate(m_capacity), m_allocator)
	{
		if(m_queue == nullptr)
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::BAD_ALLOCATION, "The allocation failed.");
	}

	template<typename T>
	FastQueue<T>::~FastQueue()
	{
		for (Type* i = m_queue.rawPtr() + m_startIndex; i != m_queue.rawPtr() + m_endIndex; i++)
		{
			i->~Type();
		}
	}

	template<typename T>
	boolean FastQueue<T>::empty() const
	{
		return m_startIndex == m_endIndex;
	}

	template<typename T>
	sizeType FastQueue<T>::size() const
	{
		return m_endIndex - m_startIndex;
	}

	template<typename T>
	void FastQueue<T>::pushBack(const Type &data)
	{
		resize(1);
		new (m_queue.rawPtr() + m_endIndex) Type(data);
		m_endIndex++;
	}

	template<typename T>
	void FastQueue<T>::pushBack(Type &&data)
	{
		resize(1);
		new (m_queue.rawPtr() + m_endIndex) Type(std::forward<Type>(data));
		m_endIndex++;
	}

	template<typename T>
	void FastQueue<T>::push(const Type &data)
	{
		pushBack(data);
	}

	template<typename T>
	void FastQueue<T>::push(Type &&data)
	{
		pushBack(std::forward<Type>(data));
	}

	template<typename T>
	typename FastQueue<T>::Type FastQueue<T>::popFront()
	{
		if (size() == 0)
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, 
				"No elements in the queue");

		T ret = NOU_CORE::move(m_queue[m_startIndex]);

		m_queue[m_startIndex].~Type();

		m_startIndex++;

		if (m_startIndex != 0 && m_startIndex == m_endIndex)
		{
			m_startIndex = 0;
			m_endIndex = 0;
		}

		return ret;
	}

	template<typename T>
	typename FastQueue<T>::Type FastQueue<T>::pop() //trailing? 
	{
		return popFront();
	}

	template<typename T>
	const typename FastQueue<T>::Type& FastQueue<T>::peekFront() const
	{
		if (size() == 0)
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS,
				"No elements in the queue");

		return m_queue[m_startIndex];
	}

	template<typename T>
	typename FastQueue<T>::Type& FastQueue<T>::peekFront()
	{
		if (size() == 0)
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS,
				"No elements in the queue");

		return m_queue[m_startIndex];
	}

	template<typename T>
	const typename FastQueue<T>::Type& FastQueue<T>::peek() const
	{
		return peekFront();
	}

	template<typename T>
	typename FastQueue<T>::Type& FastQueue<T>::peek()
	{
		return peekFront();
	}

	template<typename T>
	void FastQueue<T>::swap(sizeType index0, sizeType index1)
	{
		if (index0 >= size())
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS,
				"index0 is out of bounds.");

		if (index1 >= size())
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS,
				"index1 is out of bounds.");

		Type *queueStart = m_queue.rawPtr() + m_startIndex;
		NOU_DAT_ALG::swap<Type>(queueStart + index0, queueStart + index1);
	}

	template<typename T>
	typename FastQueue<T>::Type& FastQueue<T>::at(sizeType index)
	{
		if (index >= size())
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS,
				"index is out of bounds.");

		return *(m_queue.rawPtr() + m_startIndex + index);
	}

	template<typename T>
	typename const FastQueue<T>::Type& FastQueue<T>::at(sizeType index) const
	{
		if (index >= size())
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS,
				"index is out of bounds.");

		return *(m_queue.rawPtr() + m_startIndex + index);
	}

	template<typename T>
	void FastQueue<T>::clear()
	{
		for (Type* i = m_queue.rawPtr() + m_startIndex; i != m_queue.rawPtr() + m_endIndex; i++)
		{
			i->~Type();
		}

		m_startIndex = 0;
		m_endIndex = 0;
	}

	template<typename T>
	sizeType FastQueue<T>::capacity()
	{
		return m_capacity;
	}

	template<typename T>
	void FastQueue<T>::resize(sizeType additionalCapacity)
	{
		//The remaining size that is available after the end index, aka w/o moving or reallocation
		sizeType remainingSize = m_capacity - m_endIndex;

		if (remainingSize >= additionalCapacity)
		{
			return;
		}

		Type *newBuf = m_queue.rawPtr();
		sizeType newCapacity = m_capacity;

		//If reallocation is needed
		if ((size() + additionalCapacity) > m_capacity)
		{
			newCapacity = m_capacity + (((m_capacity + additionalCapacity) / m_capacity) * m_capacity);
			newBuf = m_allocator.allocate(newCapacity);
			
			if (newBuf == nullptr)
				NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::BAD_ALLOCATION, "The allocation failed.");
		}

		copyFromTo(m_queue.rawPtr() + m_startIndex, newBuf, size());

		m_endIndex = size();
		m_startIndex = 0;

		if (newBuf != m_queue.rawPtr())
		{
			m_queue = newBuf;
			m_capacity = newCapacity;
		}
	}

	template<typename T>
	const NOU_MEM_MNGT::AllocationCallback<typename FastQueue<T>::Type>& 
		FastQueue<T>::getAllocationCallback() const
	{
		return m_allocator;
	}

	template<typename T>
	const typename FastQueue<T>::Type& FastQueue<T>::operator [] (sizeType index) const
	{
		return at(index);
	}

	template<typename T>
	typename FastQueue<T>::Type& FastQueue<T>::operator [] (sizeType index)
	{
		return at(index);
	}
}
#endif