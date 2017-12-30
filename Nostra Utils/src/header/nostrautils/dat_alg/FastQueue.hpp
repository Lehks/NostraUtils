#ifndef NOU_DAT_ALG_FAST_QUEUE_HPP
#define NOU_DAT_ALG_FAST_QUEUE_HPP

#include "nostrautils\dat_alg\ContainerInterfaces.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\dat_alg\Utils.hpp"

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

	private:
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
		\brief
		*/
		Type *m_queue;
		
	public:
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
	};

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
		m_queue[m_endIndex] = data;
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
		//destruktor!
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
		swap(index0, index1);
	}

	template<typename T>
	sizeType FastQueue<T>::capacity()
	{
		return m_capacity;
	}
}
#endif