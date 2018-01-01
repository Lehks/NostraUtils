#ifndef NOU_DAT_ALG_FAST_QUEUE_HPP
#define NOU_DAT_ALG_FAST_QUEUE_HPP

#include "nostrautils\dat_alg\ContainerInterfaces.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\\mem_mngt\Pointer.hpp"

#include <new>

/**
\file core/FastQueue.hpp

\author  Lukas Gro�
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
	class NOU_CLASS FastQueue : public Queue<T>, public FifoQueue<T>
	{
	public:
		/**
		\brief Local class alias.
		*/
		using Type = T;

		static constexpr sizeType MIN_SIZE = 1;

	public:
		class Deleter
		{
		private:
			NOU::NOU_MEM_MNGT::AllocationCallback<Type> &m_allocator;

		public:
			Deleter(NOU::NOU_MEM_MNGT::AllocationCallback<Type> &allocator);

			void operator () (Type* t);
		};

		NOU_MEM_MNGT::AllocationCallback<Type> &m_allocator;

		/** 
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
		NOU_MEM_MNGT::UniquePtr<Type, Deleter> m_queue;
		
		void copyFromTo(Type *src, Type *dst, sizeType amount);

	public:
		FastQueue(sizeType initialCapacity = MIN_SIZE, NOU_MEM_MNGT::AllocationCallback<Type> &allocator 
			= NOU_MEM_MNGT::GenericAllocationCallback<Type>::getInstance());

		~FastQueue();

		/**
		\brief Checks if the queue is empty.
		*/
		boolean empty() const override;

		/**
		\return The current size of the queue.
		\brief Returns the current size of the queue.
		*/
		sizeType size() const override;

		/**
		\param data The element which will be stored in the queue.
		\brief Stores a element in the queue
		*/
		void pushBack(const Type &data) override;

		/**
		\param data The element which will be stored in the queue.
		\brief Calls the pushBack().
		*/
		void push(const Type &data) override;

		/**
		\return The first element in the queue.
		\brief Returns the first element in the queue.
		*/
		Type popFront() override;

		/**
		\return The first element in the queue.
		\brief Calls the popFront().
		*/
		Type pop() override;

		/**
		\param index0 The first element.
		\param index1 The second element.
		\brief Swaps two elements of the queue.
		*/
		void swap(sizeType index0, sizeType index1) override;

		/**
		\return The max capacity of the queue.
		\brief Returns the max capacity of the queue.
		*/
		sizeType capacity();

		void resize(sizeType additionalCapacity);
	};

	template<typename T>
	FastQueue<T>::Deleter::Deleter(NOU::NOU_MEM_MNGT::AllocationCallback<Type> &allocator) :
		m_allocator(allocator)
	{}

	template<typename T>
	void FastQueue<T>::Deleter::operator () (Type* t)
	{
		m_allocator.deallocate(t);
	}

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
		m_capacity(initialCapacity < MIN_SIZE ? MIN_SIZE : initialCapacity), ///\todo replace w/ max()
		m_startIndex(0),
		m_endIndex(0),
		m_queue(m_allocator.allocate(m_capacity), Deleter(m_allocator))
	{}

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
	void FastQueue<T>::push(const Type &data)
	{
		pushBack(data);
	}

	template<typename T>
	typename FastQueue<T>::Type FastQueue<T>::popFront()
	{
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
	void FastQueue<T>::swap(sizeType index0, sizeType index1)
	{
		Type *queueStart = m_queue.rawPtr() + m_startIndex;
		NOU_DAT_ALG::swap<Type>(queueStart + index0, queueStart + index1);
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
}
#endif