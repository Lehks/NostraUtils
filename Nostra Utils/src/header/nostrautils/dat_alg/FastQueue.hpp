#ifndef NOU_DAT_ALG_FAST_QUEUE_HPP
#define NOU_DAT_ALG_FAST_QUEUE_HPP

#include "nostrautils\dat_alg\ContainerInterfaces.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\\mem_mngt\Pointer.hpp"

/**
\file core/FastQueue.hpp

\author  Lukas Groﬂ
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
		
	public:
		FastQueue(sizeType initialCapacity = MIN_SIZE, NOU_MEM_MNGT::AllocationCallback<Type> &allocator 
			= NOU_MEM_MNGT::GenericAllocationCallback<Type>);

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

		void resize(sizeType capacity);
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
		for (Type* i = m_queue.rawPtr() + startIndex; i != m_queue.rawPtr() + endIndex; i++)
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
	
		new (m_queue + m_endIndex) Type(data);
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
		T ret = move(m_queue[m_startIndex]);

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
		::swap(index0, index1);
	}

	template<typename T>
	sizeType FastQueue<T>::capacity()
	{
		return m_capacity;
	}

	template<typename T>
	void FastQueue<T>::resize(sizeType capacity)
	{
		if (m_capacity - m_endIndex >= (m_capacity - capacity >= m_capacity ? 0 : m_capacity - capacity))
		{
			return;
		}
	}
}
#endif