#ifndef NOU_DAT_ALG_CONTAINER_INTERFACES_HPP
#define NOU_DAT_ALG_CONTAINER_INTERFACES_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\Utils.hpp"

/** \file ContainerInterfaces.hpp
\author  Dennis Franz
\since   0.0.1
\version 0.0.1
\brief   This file provides the container interfaces.
*/


namespace NOU::NOU_DAT_ALG
{	

	/**
	\tparam The type of the elements that will be stored in this queue.

	\brief Implementation of the a FIFO Queue interface.
	*/
	template<typename T>
	class NOU_CLASS FifoQueue
	{
	public:
		/**
		\brief Checks wether the queue is empty or not.
		*/
		virtual boolean empty() const = 0;
		/**
		\brief Returns the size of the queue.
		*/
		virtual sizeType size() const = 0;
		/**
		\brief Inserts the element at the last position.
		*/
		virtual void pushBack(const T &data) = 0;
		/**
		\brief Returns the first element of the queue and delets it.
		*/
		virtual T popFront() = 0;
		/**
		\brief Returns the first element of the queue.
		*/
		virtual T peakFront() = 0;
		/**
		\brief Swaps the elements at the corresponding index.
		*/
		virtual void swap(sizeType index0, sizeType index1) = 0;
	};


	/**
	\tparam The type of the elements that will be stored in this queue.

	\brief Implementation of the a LIFO Queue interface.
	*/
	template<typename T>
	class NOU_CLASS LifoQueue
	{
	public:
		/**
		\brief Checks wether the queue is empty or not.
		*/
		virtual boolean empty() const = 0;
		/**
		\brief Returns the size of the queue.
		*/
		virtual sizeType size() const = 0;
		/**
		\brief Inserts the element at the first position.
		*/
		virtual void pushFront(const T &data) = 0;
		/**
		\brief Returns the first element of the queue and delets it.
		*/
		virtual T popFront() = 0;
		/**
		\brief Returns the first element of the queue.
		*/
		virtual T peakFront() = 0;
		/**
		\brief Swaps the elements at the corresponding index.
		*/
		virtual void swap(sizeType index0, sizeType index1) = 0;
	};


	/**
	\tparam The type of the elements that will be stored in this queue.

	\brief Implementation of the a Queue interface.

	\details
	If an element dont need a specific queue interface like FIFO or LIFO, this interface could be applied.
	*/
	template<typename T>
	class NOU_CLASS Queue
	{
	public:
		/**
		\brief Checks wether the queue is empty or not.
		*/
		virtual boolean empty() const = 0;
		/**
		\brief Returns the size of the queue.
		*/
		virtual sizeType size() const = 0;
		/**
		\brief Inserts an element.
		*/
		virtual void push(const T &data) = 0;
		/**
		\brief Returns the first element of the queue and delets it.
		*/
		virtual T pop() = 0;
		/**
		\brief Returns the first element of the queue.
		*/
		virtual T peak() = 0;
		/**
		\brief Swaps the elements at the corresponding index.
		*/
		virtual void swap(sizeType index0, sizeType index1) = 0;
	};
}

#endif
 