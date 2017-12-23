#ifndef NOU_DAT_ALG_VECTOR_HPP
#define	NOU_DAT_ALG_VECTOR_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\ContainerInterfaces.hpp"
#include "nostrautils\dat_alg\Bubblesort.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"

/** \file Vector.hpp
\author  Dennis Franz
\since   0.0.1
\version 0.0.1
\brief   This file provides a Vector implementation.
*/

namespace NOU::NOU_DAT_ALG
{

	/**
	\tparam The type of the elements that will be stored in this Vector.

	\brief A dynamically growing container that can store multiple elements of a single type.

	\details The most basic of our containers. It can act like a dynamic array a FIFO-Queue, LIFO-Queue or a normal Queue.
	*/
	template<typename T>
	class NOU_CLASS Vector : public FifoQueue<T> , public LifoQueue<T>, public Queue<T>
	{
	private:
		NOU::NOU_MEM_MNGT::AllocationCallback<T>	&m_allocator;

		/**
		\brief A Constant for the minimal size of the Vector.
		*/
		static constexpr sizeType	                MIN_CAPACITY = 1;
		/**
		\brief The actuall capacity of the Vector (memory allocation).
		*/
		sizeType								    m_capacity;
		/**
		\brief The actuall size of the Vector (elements stored).
		*/
		sizeType								    m_size;
		/**
		\brief A pointer to the array that stores data.
		*/
		T										   *m_data;
		/**
		\brief Allocates an memory amount for the vector.
		*/
		T* alloc(sizeType amount);
		/**
		\brief Frees the amount of the Vector.
		*/
		void free(T *data);
		/**
		\brief Reallocate memory for the vector.
		*/
		void reallocateData(sizeType capacity);

	public:
		/**
		\param size Default set to 1.

		\brief Standard constructor with the size.
		*/
		Vector<T>(sizeType size, NOU::NOU_MEM_MNGT::AllocationCallback<T> &allocator = NOU_MEM_MNGT::GenericAllocationCallback<T>::getInstance()); ///\todo add allocator to the stadard constructor
		/**
		\param other Takes an other vector for moving.

		\brief Move constructor with the size.
		*/
		Vector<T>(Vector<T> &&other);
		/**
		\param other Takes an other vector for copying.

		\brief Copy constructor with the size.
		*/
		Vector<T>(const Vector<T> &other);
		/**
		\brief Standard destructor.
		*/
		~Vector<T>();

		/**
		\return      Returns a boolean.

		\brief Checks wehter the Vector is empty or not.
		*/
		boolean empty() const override;
		/**
		\return      Returns the size of the Vector.

		\brief Returns the size of the Vector.
		*/
		sizeType size() const override;
		/**
		\param index The index of the element to remove.
		\return      The element that was removed.

		\brief Returns the object at the given index.
		*/
		T& at(sizeType index);
		/**
		\param index The index of the element to remove.
		\return      The element that was removed.

		\brief Returns the object at the given index.
		*/
		const T& at(sizeType index) const;
		/**
		\param additionalCapactiy Additional capacity amount.

		\brief Expends the capacity of the vector.
		*/
		void expandCapacity(sizeType additionalCapacity);
		/**
		\param additionalCapactiy Additional capacity amount.

		\brief Checks if the capacity of the vector needs to be extended.
		*/
		void expandIfNeeded(sizeType additionalCapactiy);
		/**
		\param data The data to insert.

		\brief Inserts an element at the last position.
		*/
		void pushBack(const T &data) override;
		/**
		\param data The data to insert.

		\brief Inserts an element at the first position.
		*/
		void pushFront(const T &data) override;

		void push(const T &data);
		/**
		\return      The elemnt at the first position.

		\brief Inserts an element at the first position.
		*/
		T popFront() override;

		T pop() override;
		/**
		\param index0 The first index.
		\param index1 The second index.

		\brief Swaps the elements at the corresponding index.
		*/
		void swap(sizeType index0, sizeType index1) override;
		/**
		\param index Removes the data at the given index.

		\brief Inserts an element at a given index.
		*/
		void remove(sizeType index);

		/**
		\param data The data to insert.
		\param index The index at wich the data gets inserted.

		\brief Inserts an element at a given index.
		*/
		void insert(const T &data, sizeType index);
		/**
		\brief Sorts the Vector.
		*/
		void sort();

		Vector& operator = (const Vector &other);
		Vector& operator = (Vector &&other);
		T& operator [] (sizeType index);
		const T& operator [] (sizeType index) const;

	};


	template<typename T>
	T* Vector<T>::alloc(sizeType amount)
	{
		return m_allocator.allocate(amount); 
	}

	template<typename T>
	void Vector<T>::free(T *data)
	{
		return m_allocator.deallocate(data); 
	}

	template<typename T>
	void Vector<T>::reallocateData(sizeType capacity)
	{
		T *newData = alloc(capacity);

		m_capacity = capacity;

		for (sizeType i = 0; i < m_size; i++)
		{
			new (newData + i) T(NOU::NOU_CORE::move(at(i))); //move data to new buffer
			at(i).~T(); //delete old objects
		}

		free(m_data);

		m_data = newData;
	}

	template<typename T>
	Vector<T>::Vector(sizeType size, NOU::NOU_MEM_MNGT::AllocationCallback<T> &allocator) :
		m_capacity(NOU::NOU_CORE::max(MIN_CAPACITY, size)),
		m_data(alloc(m_capacity)),
		m_size(m_capacity),
		m_allocator(allocator)
	{}

	template<typename T>
	Vector<T>::Vector(Vector<T>&& other) :
		m_capacity(other.m_capacity),
		m_data(other.m_data),
		m_size(other.m_size),
		m_allocator(other.m_allocator)
	{
		other.m_capacity = 0; //set capacity to 0, to allow for cpy-reassingment to the other-vector.
		other.m_data = nullptr;
		other.m_size = 0; //set size to 0, to avoid any destructors for stored objects from being called.
	}

	template<typename T>
	Vector<T>::Vector(const Vector<T> &other) :
		m_capacity(other.m_capacity),
		m_data(alloc(m_capacity)),
		m_size(other.m_size),
		m_allocator(other.m_allocator)
	{
		for (sizeType i = 0; i < other.m_size; i++)
			new (m_data + i) T(other.at(i));
	}

	template<typename T>
	Vector<T>::~Vector() 
	{
		for (sizeType i = 0; i < m_size; i++)
		{
			at(i).~T();
		}

		m_allocator.deallocate(m_data);
	}

	template<typename T>
	boolean Vector<T>::empty() const
	{
		return m_size > 0 ? false : true;
	}

	template<typename T>
	sizeType Vector<T>::size() const
	{
		return m_size;
	}
	template<typename T>
	T& Vector<T>::at(sizeType index)
	{
		return m_data[index];
	}

	template<typename T>
	const T& Vector<T>::at(sizeType index) const
	{
		return m_data[index];
	}

	template<typename T>
	void Vector<T>::expandCapacity(sizeType additionalCapacity)
	{
		//sizeType newCapacity = m_capacity + (m_capacity * ((m_capacity + additionalCapacity) / additionalCapacity));
		sizeType newCapacity = m_capacity + (((m_capacity + additionalCapacity) / m_capacity) * m_capacity); //dividing by m_capacity is safe b/c m_capacity is always > 0

		reallocateData(newCapacity);
	}

	template<typename T>
	void Vector<T>::expandIfNeeded(sizeType additionalCapactiy)
	{
		if ((m_size + additionalCapactiy) > m_capacity)
			expandCapacity(additionalCapactiy);
	}

	template<typename T>
	void Vector<T>::pushBack(const T &data)
	{
		expandIfNeeded(1);

		new (m_data + m_size) T(data); //initialize next object

		m_size++;
	}

	template<typename T>
	void Vector<T>::pushFront(const T &data)
	{
		insert(0, data);
	}

	template<typename T>
	T Vector<T>::popFront()
	{
		T element = NOU_CORE::move(*m_data);
		remove(0);
		return element;
	}

	template<typename T>
	void Vector<T>::push(const T &data)
	{
		pushBack(data);
	}

	template<typename T>
	T Vector<T>::pop()
	{
		return popFront();
	}

	template<typename T>
	void Vector<T>::swap(sizeType index0, sizeType index1)
	{
		swap(*m_data + index0, *m_data + index1);
	}

	template<typename T>
	void Vector<T>::remove(sizeType index)
	{
		for (sizeType i = index; i < m_size - 1; i++) //shift all element to the left, until the index
		{
			at(i).~T(); //delete old element
			new (m_data + i) T(NOU::NOU_CORE::move(at(i + 1))); //override old element using move constr
		}

		//destroy last element in the vector (it was moved and will not be overridden at this point)
		at(m_size - 1).~T();

		m_size--;
	}

	template<typename T>
	void Vector<T>::insert(const T &data, sizeType index)
	{
		expandIfNeeded(1);

		for (sizeType i = m_size; i > index; i--)
		{
			if (i != m_size)
				at(i).~T(); //delete old element (if not outside array bounds)

			new (m_data + i) T(m_data[i - 1]); //shift element to the right using move constructor
		}

		m_data[index].~T();
		new (m_data + index) T(data); //copy new element into the vector

		m_size++;
	}

	template<typename T>
	void Vector<T>::sort()
	{
		bubbleSort(m_data, m_size);
	}

	template<typename T>
	Vector<T>& Vector<T>::operator = (const Vector<T> &other)
	{
		//If capacity of this vector is smaller than the capacity of the other one, reallocate memory
		//This also ensures, that a copy has at least a capacity as big as the other one's
		if (m_capacity < other.m_capacity)
		{
			free(m_data);
			m_capacity = other.m_capacity;
			m_data = alloc(m_capacity);
		}

		//Delete all objects that are in the current vector, but will not overridden by elements in the other one
		//If there are fewer elements in this vector than in the other one, nothing will happen
		for (sizeType i = other.m_size; i < m_size; i++)
			at(i).~T();

		sizeType i;

		/*
		First:  Override existing elements with the values from the other vector using cpy-assign
		Second: Set uninitialized elements with the values from the other vector using cpy-constr
		*/
		//####
		for (i = 0; i < min(m_size, other.m_size); i++) //cpy-assign part
			at(i) = other.at(i);

		for (; i < other.m_size; i++) //cpy-constr part
			new (m_data + i) T(other.at(i));
		//####

		m_size = other.m_size;

		return *this;
	}

	template<typename T>
	Vector<T>& Vector<T>::operator = (Vector<T> &&other)
	{
		this->~Vector(); //destruct elements in this vector + frees buffer

		m_capacity = other.m_capacity; //copy values here
		m_data = other.m_data;
		m_size = other.m_size;

		other.m_capacity = 0; //Invalidate other vector
		other.m_data = nullptr;
		other.m_size = 0;

		return *this;
	}

	template<typename T>
	T& Vector<T>::operator [] (sizeType index)
	{
		return at(index);
	}

	template<typename T>
	const T& Vector<T>::operator [] (sizeType index) const
	{
		return at(index);
	}
}


#endif