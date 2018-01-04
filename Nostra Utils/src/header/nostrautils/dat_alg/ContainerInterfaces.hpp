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
		virtual T peekFront() = 0;
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
		virtual T peekFront() = 0;
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
		virtual T peek() = 0;
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
	class NOU_CLASS RandomAccess
	{
	public:
		/**
		\brief Returns the size of the queue.
		*/
		virtual sizeType size() const = 0;

		/**
		\brief Swaps the elements at the corresponding index.
		*/
		virtual void swap(sizeType index0, sizeType index1) = 0;
		/**
		\param index The index of the element to remove.
		\return      The element that was removed.

		\brief Returns a reference of the object at the given index.
		*/
		virtual T& at(sizeType index) = 0;
		/**
		\param index The index of the element to remove.
		\return      The element that was removed.

		\brief Returns a const reference of the object at the given index.
		*/
		virtual const T& at(sizeType index) const = 0;
		/**
		\param additionalCapactiy Additional capacity amount.

		\brief Expends the capacity of the vector.
		*/
		/**
		\param index The index of the element in the vector.
		\return      The element at the passed index.

		\brief Returns the element at the specified index. Same as at().

		\details
		Returns the element at the specified index. Same as at(), seet the doc of that method for further
		information.

		\see at()
		*/
		virtual T& operator [] (sizeType index);
		/**
		\param index The index of the element in the vector.
		\return      The element at the passed index.

		\brief Returns the element at the specified index. Same as at().

		\details
		Returns the element at the specified index. Same as at(), seet the doc of that method for further
		information.

		\see at()
		*/
		virtual const T& operator [] (sizeType index) const;
	};

	template<typename T>
	T& RandomAccess<T>::operator[](sizeType index)
	{
		return at(index);
	}
	template<typename T>
	const T& RandomAccess<T>::operator[](sizeType index) const
	{
		return at(index);
	}
}

#endif
 