#ifndef NOU_DAT_ALG_VECTOR_HPP
#define	NOU_DAT_ALG_VECTOR_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/mem_mngt/AllocationCallback.hpp"
#include "nostrautils/core/Utils.hpp"
#include "nostrautils/core/ErrorHandler.hpp"
#include "nostrautils/dat_alg/Utils.hpp"

#include <new>

/** \file Vector.hpp
\author  Dennis Franz
\author  Lukas Reichmann
\since   1.0.0
\version 1.0.0
\brief   This file provides a Vector implementation.
*/

namespace NOU::NOU_DAT_ALG
{
	///\cond
	template<typename T>
	class VectorIterator;

	template<typename T>
	class VectorReverseIterator;
	///\endcond

	template<typename T>
	using VectorConstIterator = const VectorIterator<T>;

	template<typename T>
	using VectorReverseConstIterator = const VectorReverseIterator<T>;

	/**
	\tparam The type of the elements that will be stored in this Vector.

	\brief A dynamically growing container that can store multiple elements of a single type.

	\details The most basic of our containers. It can act like a dynamic array a FIFO-Queue, LIFO-Queue or a normal Queue.
	*/
	template<typename T>
	class NOU_CLASS Vector final
	{

	private:
		/**
		\brief The allocation callback that will allocate and deallocate the memory for the vector.
		*/
		NOU::NOU_MEM_MNGT::AllocationCallback<T>	&m_allocator;

		/**
		\brief A Constant for the minimal size of the Vector.
		*/
		static constexpr sizeType	                MIN_CAPACITY = 1;

		/**
		\brief The actual capacity of the Vector (memory allocation).

		\details 
		The amount of memory 
		*/
		sizeType								    m_capacity;

		/**
		\brief The actual size of the Vector (elements stored).
		*/
		sizeType								    m_size;

		/**
		\brief A pointer to the array that stores data.
		*/
		T										   *m_data;

		/**
		\brief Allocates an memory amount for the vector.

		\see nostra::utils::mem_mngt::AllocationCallback
		*/
		T* alloc(sizeType amount);

		/**
		\brief Frees the amount of the Vector.

		\see nostra::utils::mem_mngt::AllocationCallback
		*/
		void free(T *data);

		/**
		\brief Reallocate memory for the vector.

		\details 
		If a new element gets inserted to the vector it has to reallocate the memory for it.
		*/
		void reallocateData(sizeType capacity);

		/**
		\tparam ARGS The types of the arguments that will be passed to the constructor of T.

		\param index The index at which the instance will be inserted at.
		\param args  The arguments that will be passed to the constructor of T.

		\brief Constructs a new instance of T and inserts it at the passed index. 
		*/
		template<typename... ARGS>
		void construct(sizeType index, ARGS&&... args);

	public:
		/**
		\param size Initial size of the constructor.
		\param allocator Allocator for the vector.

		\brief Standard constructor with the size.
		\details 
		The size is initialized by default with 1 (if no size is given or size < 1). The allocator is initialized by default 
		with a GenericAllocation (nostra::utils::mem_mngt::GenericAllocationCallback).
		If there is need for a custom allocator you can create one from the interface nostra::utils::mem_mngt::AllocationCallback.

		\see   nostra::utils::mem_mngt::AllocationCallback
		\see   nostra::utils::mem_mngt::GenericAllocationCallback
		*/
		Vector<T>(sizeType size = MIN_CAPACITY, NOU::NOU_MEM_MNGT::AllocationCallback<T> &allocator = 
			NOU_MEM_MNGT::GenericAllocationCallback<T>::getInstance());

		/**
		\param other Takes an other vector for moving.

		\brief For Moving the \p other Vector.
		*/
		Vector<T>(Vector<T> &&other);

		/**
		\param other Takes an other vector for copying.

		\brief For Copying the \p other Vector.
		*/
		Vector<T>(const Vector<T> &other);

		/**
		\brief Standard destructor.

		\details 
		Note that the Vectors memory is not allocated with the new keyword therefore the memory gets not dealocated with the delete keyword. 
		For more deatils look at the implication.
		*/
		~Vector<T>();

		/**
		\tparam ARGS The types of the arguments that will be passed to the constructor of the type T.
		\param args The parameters that will be passed to the constructor of T.

		\brief Like pushBack, this function inserts an element in the vector at the end. However, instead of 
		       copying the element, it will construct a new element from the arguments that were passed to the
			   function.
		*/
		template<typename... ARGS>
		void emplaceBack(ARGS&&... args);

		/**
		\return      Returns a boolean.

		\brief Checks whether the Vector is empty or not.
		*/
		boolean empty() const ;

		/**
		\return      Returns the size of the Vector.

		\brief Returns the size of the Vector.
		*/
		sizeType size() const ;

		/**
		\return      Returns the capacity of the Vector.

		\brief Returns the capacity of the Vector.
		*/
		sizeType capacity() const;

		/**
		\param index The index of the element to show.
		\return      The element that should be shown.

		\brief Returns a reference of the object at the given index.
		*/
		T& at(sizeType index);

		/**
		\param index The index of the element to show.
		\return      The element that should be shown.

		\brief Returns a const reference of the object at the given index.
		*/
		const T& at(sizeType index) const;

		/**
		\param additionalCapacity Additional capacity amount.

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
		void pushBack(const T &data);

		/**
		\param data The data to insert.

		\brief Inserts an element at the last position.
		*/
		void pushBack(T &&data);

		/**
		\param data The data to insert.

		\brief Inserts an element at the first position.
		*/
		void pushFront(T &&data);

		/**
		\param data The data to insert.

		\brief Inserts an element at the first position.
		*/
		void pushFront(const T &data);

		/**
		\param data The data to insert.

		\brief Inserts an element at the last position.
		\details 
		This method calls pushBack() .
		*/
		void push(T &&data);

		/**
		\param data The data to insert.

		\brief Inserts an element at the last position.
		\details
		This method calls pushBack() .
		*/
		void push(const T &data);

		/**
		\return      The element at the first position.

		\brief Returns the element at the first position and deletes it.
		*/
		T popFront();

		/**
		\return      The element at the first position.

		\brief Returns the element at the first position and deletes it.
		\details 
		This method calls popFront() .
		*/
		T pop();

		/**
		\return      The element at the first position.

		\brief Returns the element at the first position.
		*/
		T& peekFront();

		/**
		\return      The element at the first position.

		\brief Returns the element at the first position.
		*/
		const T& peekFront() const;

		/**
		\return      The element at the first position.

		\brief Returns the element at the first position.
		\details
		This method calls peakFront() .
		*/
		T& peek();

		/**
		\return      The element at the first position.

		\brief Returns the element at the first position.
		\details
		This method calls peakFront() .
		*/
		const T& peek() const;

		/**
		\param index0 The first index.
		\param index1 The second index.

		\brief Swaps the elements at the corresponding index.
		\details 
		This method calls the swap function in nostra::utils::dat_alg::utils.

		\see nostra::utils::dat_alg::utils
		*/
		void swap(sizeType index0, sizeType index1);

		/**
		\param index Removes the element at the given index.

		\brief removes an element at a given index.
		*/
		void remove(sizeType index);

		/**
		\tparam ARGS The types of the arguments that will be passed to the constructor of the type T.
		\param index The index at which the new instance will be inserted.
		\param args  The parameters that will be passed to the constructor of T.

		\brief Like insert, this function inserts an element in the vector at a given index. However, instead 
		of copying the element, it will construct a new element from the arguments that were passed to the
		function.
		*/
		template<typename... ARGS>
		void emplace(sizeType index, ARGS&&... args);

		/**
		\param data The data to insert.
		\param index The index at which the data gets inserted.

		\brief Inserts an element at a given index while keeping the order of the other elements in tact.
		*/
		void insert(sizeType index, T &&data);

		/**
		\param data The data to insert.
		\param index The index at which the data gets inserted.

		\brief Inserts an element at a given index while keeping the order of the other elements in tact.
		*/
		void insert(sizeType index, const T &data);

		/**
		\brief Sorts the Vector.
		*/
		void sort();

		/**
		\brief Sorts the Vector using comparators.
		*/
		void sortComp(NOU::NOU_DAT_ALG::Comparator<T> comp);

		/**
		\brief returns a pointer reference to the current data.
		*/
		T* const & data();

		/**
		\brief returns a const pointer reference to the current data.
		*/
		const T* data() const;

		/**
		\brief Clears the Vector.
		*/
		void clear();

		/**
		\brief Sets the size of the Vector.
		*/
		void setSize(sizeType size);

		/**
		\param replacement The data to insert.
		\param index The index at which the data gets replaced.

		\brief replaces the data at the index with the passed data.
		*/
		Vector& replace(sizeType index, T &&replacement);

		/**
		\param replacement The data to insert.
		\param index The index at which the data gets replaced.

		\brief replaces the data at the index with the passed data.
		*/
		Vector& replace(sizeType index, const T &replacement);

		/**
		\return A nostra::utils::dat_alg::VectorIterator that points to the first element in the vector.

		\brief Returns a nostra::utils::dat_alg::VectorIterator that points to the first element in the
		vector.
		*/
		VectorIterator<T> begin();

		/**
		\return A nostra::utils::dat_alg::VectorIterator that points to the element after the last element
		in the vector.

		\brief Returns a nostra::utils::dat_alg::VectorIterator that points to the element after the last element
		in the vector.

		\warning Using the operator * on this iterator is invalid and it will return an invalid element.
		*/
		VectorIterator<T> end();

		/**
		\return A nostra::utils::dat_alg::VectorIterator that points to the element at the specified index.

		\brief Returns a nostra::utils::dat_alg::VectorIterator that points to the element at the specified index.
		*/
		VectorIterator<T> indexIterator(sizeType index);

		/**
		\return A nostra::utils::dat_alg::VectorIterator that points to the first element in the vector.

		\brief Returns a nostra::utils::dat_alg::VectorIterator that points to the first element in the
		vector.
		*/
		VectorConstIterator<T> begin() const;

		/**
		\return A nostra::utils::dat_alg::VectorIterator that points to the element after the last element
		in the vector.

		\brief Returns a nostra::utils::dat_alg::VectorIterator that points to the element after the last element
		in the vector.

		\warning Using the operator * on this iterator is invalid and it will return an invalid element.
		*/
		VectorConstIterator<T> end() const;

		/**
		\return A nostra::utils::dat_alg::VectorIterator that points to the element at the specified index.

		\brief Returns a nostra::utils::dat_alg::VectorIterator that points to the element at the specified index.
		*/
		VectorConstIterator<T> indexIterator(sizeType index) const;

		/**
		\return A nostra::utils::dat_alg::VectorReverseIterator that points to the last element in the vector.

		\brief Returns a nostra::utils::dat_alg::VectorReverseIterator that points to the last element in the
		vector.
		*/
		VectorReverseIterator<T> rbegin();

		/**
		\return A nostra::utils::dat_alg::VectorReverseIterator that points to the element before the first
		element in the vector.

		\brief Returns a nostra::utils::dat_alg::VectorReverseIterator that points to the element before the first
		element in the vector.

		\warning Using the operator * on this iterator is invalid and it will return an invalid element.
		*/
		VectorReverseIterator<T> rend();

		/**
		\return A nostra::utils::dat_alg::VectorReverseIterator that points to the element at the specified index.

		\brief Returns nostra::utils::dat_alg::VectorReverseIterator that points to the element at the specified
		index.
		*/
		VectorReverseIterator<T> rindexIterator(sizeType index);

		/**
		\return A nostra::utils::dat_alg::VectorReverseIterator that points to the last element in the vector.

		\brief Returns a nostra::utils::dat_alg::VectorReverseIterator that points to the last element in the
		vector.
		*/
		VectorReverseConstIterator<T> rbegin() const;

		/**
		\return A nostra::utils::dat_alg::VectorReverseIterator that points to the element before the first
		element in the vector.

		\brief Returns a nostra::utils::dat_alg::VectorReverseIterator that points to the element before the first
		element in the vector.

		\warning Using the operator * on this iterator is invalid and it will return an invalid element.
		*/
		VectorReverseConstIterator<T> rend() const;

		/**
		\return A nostra::utils::dat_alg::VectorReverseIterator that points to the element at the specified index.

		\brief Returns a nostra::utils::dat_alg::VectorReverseIterator that points to the element at the specified
		index.
		*/
		VectorReverseConstIterator<T> rindexIterator(sizeType index) const;

		/**
		\param other The vector to copy the data from.
		\return The vector that the data was copied to.

		\brief Copies the data from the passed vector to this one. This uses both the copy assignment
		operator and copy constructor.
		*/
		Vector& operator = (const Vector &other);
		/**
		\param other The vector to move the data from.

		\brief Moves the data from the passed vector to this one.

		\details 
		Moves the data from the passed vector to this one. The vector that the data was
		moved from will afterwards have a size and capacity of 0. This allows it to reassigning another
		vector to the one that the data was moved from using the copy or move assignment operators.
		*/
		Vector& operator = (Vector &&other);
		/**
		\param index The index of the element in the vector.
		\return      The element at the passed index.

		\brief Returns the element at the specified index. Same as at().

		\details
		Returns the element at the specified index. Same as at(), see the doc of that method for further
		information.

		\see at()
		*/
		T& operator [] (sizeType index);
		/**
		\param index The index of the element in the vector.
		\return      The element at the passed index.

		\brief Returns the element at the specified index. Same as at().

		\details
		Returns the element at the specified index. Same as at(), see the doc of that method for further
		information.

		\see at()
		*/
		const T& operator [] (sizeType index) const;

	};

	/**
	\brief An iterator that is used to iterate over a nostra::utils::dat_alg::Vector (this iterator supports
	both const and non-const iterating). This iterator is a forward iterator.
	*/
	template<typename T>
	class NOU_CLASS VectorIterator
	{
		friend class Vector<T>;

	private:
		/*
		\brief A pointer to the array that this iterator iterates over.
		*/
		T                **m_dataPtr;

		/**
		\brief The index of the element that will be returned the next time the operator * is called.
		*/
		mutable sizeType   m_index; //mutable to allow operator ++ to be const

	public:
		/**
		\param index   The index to start at.
		\param dataPtr A pointer to a pointer to the array that this iterator iterates over.

		\brief Constructs a new instance that starts at the passed index and iterates over the passed array.
		*/
		constexpr VectorIterator(sizeType index, const T **dataPtr);

		/**
		\return The element that this iterator is currently pointing to.

		\brief Returns the element that this iterator is currently pointing to.
		*/
		constexpr T& operator * ();

		/**
		\return The element that this iterator is currently pointing to.

		\brief Returns the element that this iterator is currently pointing to.
		*/
		constexpr const T& operator * () const;

		/**
		\return The element that this iterator is currently pointing to.

		\brief Returns the element that this iterator is currently pointing to.
		*/
		constexpr T* operator -> ();

		/**
		\return The element that this iterator is currently pointing to.

		\brief Returns the element that this iterator is currently pointing to.
		*/
		constexpr const T* operator -> () const;

		/**
		\brief Increments the iterator to point to the next element in the vector.
		*/
		constexpr VectorIterator& operator ++ ();

		/**
		\brief Increments the iterator to point to the next element in the vector.
		*/
		constexpr const VectorIterator& operator ++ () const;

		/**
		\brief Increments the iterator to point to the next element in the vector.
		*/
		constexpr VectorIterator operator ++ (int) const;

		/**
		\param other The iterator to compare this iterator to.
		\return      True, if the iterators are equal, false if not.

		\brief Returns whether two iterators are equal. Two iterators qualify as equal if their internal
		index and the vector that they point to are the same.
		*/
		constexpr boolean operator == (const VectorIterator &other) const;

		/**
		\param other The iterator to compare this iterator to.
		\return      False, if the iterators are equal, true if not.

		\brief Returns whether two iterators are unequal. This returns the opposite of what the operator
		= would return.
		*/
		constexpr boolean operator != (const VectorIterator &other) const;

		/**
		\param value The value to add.

		\return A new iterator with the value of this operator plus the added value.

		\brief Adds two iterators. E.g. if this iterator points to the first object and \p value is two, the
		       resulting operator would point to the third object. Note that the order in which these 
			   iterators are named (first, second, etc.) is relative to Vector::begin(). 
		*/
		constexpr VectorIterator operator + (sizeType value) const;

		/**
		\param value The value to subtract.

		\return A new iterator with the value of this operator minus the subtracted value.

		\brief Subtracts two iterators. E.g. if this iterator points to the second object and \p value is one, 
		       the resulting operator would point to the first object. Note that the order in which these 
			   iterators are named (first, second, etc.) is relative to Vector::begin(). 
		*/
		constexpr VectorIterator operator - (sizeType value) const;

		/**
		\param value The value to add.

		\return A reference to this instance.

		\brief Adds the passed iterator to this one. E.g. if this iterator points to the first object and 
		       \p value is two, this iterator would point to the third object afterwards. Note that the 
			   order in which these iterators are named (first, second, etc.) is relative to Vector::begin(). 
		*/
		constexpr VectorIterator& operator += (sizeType value);

		/**
		\param value The value to subtract.

		\return A reference to this instance.

		\brief Subtracts the passed iterator to this one. E.g. if this iterator points to the second object 
	           and \p value is one, this iterator would point to the first object afterwards. Note that the 
			   order in which these iterators are named (first, second, etc.) is relative to Vector::begin(). 
		*/
		constexpr VectorIterator& operator -= (sizeType value);
	};

	/**
	\brief An iterator that is used to iterate over a nostra::utils::dat_alg::Vector (this iterator supports
	both const and non-const iterating). This iterator is a reverse iterator.
	*/
	template<typename T>
	class NOU_CLASS VectorReverseIterator
	{
		friend class Vector<T>;

	private:
		/*
		\brief A pointer to the array that this iterator iterates over.
		*/
		T                **m_dataPtr;

		/**
		\brief The index of the element that will be returned the next time the operator * is called.
		*/
		mutable sizeType   m_index; //mutable to allow operator ++ to be const

	public:
		/**
		\param index   The index to start at.
		\param dataPtr A pointer to a pointer to the array that this iterator iterates over.

		\brief Constructs a new instance that starts at the passed index and iterates over the passed array.
		*/
		constexpr VectorReverseIterator(sizeType index, const T **dataPtr);

		/**
		\return The element that this iterator is currently pointing to.

		\brief Returns the element that this iterator is currently pointing to.
		*/
		constexpr T& operator * ();

		/**
		\return The element that this iterator is currently pointing to.

		\brief Returns the element that this iterator is currently pointing to.
		*/
		constexpr const T& operator * () const;

		/**
		\return The element that this iterator is currently pointing to.

		\brief Returns the element that this iterator is currently pointing to.
		*/
		constexpr T* operator -> ();

		/**
		\return The element that this iterator is currently pointing to.

		\brief Returns the element that this iterator is currently pointing to.
		*/
		constexpr const T* operator -> () const;

		/**
		\brief Increments the iterator to point to the next element in the vector.
		*/
		constexpr VectorReverseIterator& operator ++ ();

		/**
		\brief Increments the iterator to point to the next element in the vector.
		*/
		constexpr const VectorReverseIterator& operator ++ () const;

		/**
		\brief Increments the iterator to point to the next element in the vector.
		*/
		constexpr VectorReverseIterator operator ++ (int) const;

		/**
		\param other The iterator to compare this iterator to.
		\return      True, if the iterators are equal, false if not.

		\brief Returns weather two iterators are equal. Two iterators qualify as equal if their internal
		index and the vector that they point to are the same.
		*/
		constexpr boolean operator == (const VectorReverseIterator &other) const;

		/**
		\param other The iterator to compare this iterator to.
		\return      False, if the iterators are equal, true if not.

		\brief Returns weather two iterators are unequal. This returns the opposite of what the operator
		= would return.
		*/
		constexpr boolean operator != (const VectorReverseIterator &other) const;

		/**
		\param value The value to add.

		\return A new iterator with the value of this operator plus the added value.

		\brief Adds two iterators. E.g. if this iterator points to the first object and \p value is two, the
		resulting operator would point to the third object. Note that the order in which these iterators are 
		named (first, second, etc.) is relative to Vector::rbegin().
		*/
		constexpr VectorReverseIterator operator + (sizeType value) const;

		/**
		\param value The value to subtract.

		\return A new iterator with the value of this operator minus the subtracted value.

		\brief Subtracts two iterators. E.g. if this iterator points to the second object and \p value is one,
		the resulting operator would point to the first object. Note that the order in which these iterators 
		are named (first, second, etc.) is relative to Vector::rbegin().
		*/
		constexpr VectorReverseIterator operator - (sizeType value) const;

		/**
		\param value The value to add.

		\return A reference to this instance.

		\brief Adds the passed iterator to this one. E.g. if this iterator points to the first object and
		\p value is two, this iterator would point to the third object afterwards. Note that the order in 
		which these iterators are named (first, second, etc.) is relative to Vector::rbegin().
		*/
		constexpr VectorReverseIterator& operator += (sizeType value);

		/**
		\param value The value to subtract.

		\return A reference to this instance.

		\brief Subtracts the passed iterator to this one. E.g. if this iterator points to the second object
		and \p value is one, this iterator would point to the first object afterwards. Note that the order in 
		which these iterators are named (first, second, etc.) is relative to Vector::rbegin().
		*/
		constexpr VectorReverseIterator& operator -= (sizeType value);
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
	template<typename... ARGS>
	void Vector<T>::construct(sizeType index, ARGS&&... args)
	{
		new (m_data + index) T(NOU_CORE::forward<ARGS>(args)...);
	}

	template<typename T>
	Vector<T>::Vector(sizeType size, NOU::NOU_MEM_MNGT::AllocationCallback<T> &allocator) :
		m_capacity(NOU::NOU_CORE::max(MIN_CAPACITY, size)),
		m_data(alloc(m_capacity)),
		m_size(0),
		m_allocator(allocator)
	{}

	template<typename T>
	Vector<T>::Vector(Vector<T>&& other) :
		m_capacity(other.m_capacity),
		m_data(other.m_data),
		m_size(other.m_size),
		m_allocator(other.m_allocator)
	{
		other.m_capacity = 0; //set capacity to 0, to allow for copy-reassignment to the other-vector.
		other.m_data = nullptr;
		other.m_size = 0; //set size to 0, to avoid any destructor's for stored objects from being called.
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
	template<typename ...ARGS>
	void Vector<T>::emplaceBack(ARGS&& ...args)
	{
		expandIfNeeded(1);

		construct(m_size, NOU_CORE::forward<ARGS>(args)...);

		m_size++;
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
	sizeType Vector<T>::capacity() const
	{
		return m_capacity;
	}

	template<typename T>
	T& Vector<T>::at(sizeType index)
	{
		NOU_COND_PUSH_ERROR((index > m_size),
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, "An index was out of bounds.");

		return m_data[index];
	}

	template<typename T>
	const T& Vector<T>::at(sizeType index) const
	{
		NOU_COND_PUSH_ERROR((index > m_size),
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, "An index was out of bounds.");

		return m_data[index];
	}

	template<typename T>
	void Vector<T>::expandCapacity(sizeType additionalCapacity)
	{
		//dividing by m_capacity is safe b/c m_capacity is always > 0
		sizeType newCapacity = m_capacity + (((m_capacity + additionalCapacity) / m_capacity) * m_capacity); 

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
		emplaceBack(data);
	}

	template<typename T>
	void Vector<T>::pushBack(T &&data)
	{
		emplaceBack(NOU_CORE::move(data));
	}

	template<typename T>
	void Vector<T>::pushFront(T &&data)
	{
		insert(0, NOU_CORE::move(data));
	}

	template<typename T>
	void Vector<T>::pushFront(const T &data)
	{
		insert(0, data);
	}

	template<typename T>
	T Vector<T>::popFront()
	{
		NOU_COND_PUSH_ERROR((m_size == 0),
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "No object was found.");

		T element = NOU_CORE::move(*m_data);
		remove(0);
		return element;
	}

	template<typename T>
	void Vector<T>::push(T &&data)
	{
		pushBack(NOU_CORE::move(data));
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
	T& Vector<T>::peekFront()
	{
		return m_data[0];
	}

	template<typename T>
	const T& Vector<T>::peekFront() const
	{
		return m_data[0];
	}

	template<typename T>
	T& Vector<T>::peek()
	{
		return peekFront();
	}

	template<typename T>
	const T& Vector<T>::peek() const
	{
		return peekFront();
	}

	template<typename T>
	void Vector<T>::swap(sizeType index0, sizeType index1)
	{
		NOU_COND_PUSH_ERROR((index0 > m_size),
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "No object was found at this index.");

		NOU_COND_PUSH_ERROR((index1 > m_size),
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "No object was found at this index.");

		NOU::NOU_DAT_ALG::swap(m_data + index0, m_data + index1);
	}

	template<typename T>
	void Vector<T>::remove(sizeType index)
	{
		NOU_COND_PUSH_ERROR((index > m_size),
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "No object was found at this index.");

		for (sizeType i = index; i < m_size - 1; i++) //shift all element to the left, until the index
		{
			at(i).~T(); //delete old element
			new (m_data + i) T(NOU::NOU_CORE::move(at(i + 1))); // old element using move constr
		}

		//destroy last element in the vector (it was moved and will not be overridden at this point)
		at(m_size - 1).~T();

		m_size--;
	}
	
	template<typename T>
	template<typename... ARGS>
	void Vector<T>::emplace(sizeType index, ARGS&&... args)
	{
		expandIfNeeded(1);
		for (sizeType i = m_size; i > index; i--)
		{
			if (i != m_size)
				at(i).~T(); //delete old element (if not outside array bounds)
	
			new (m_data + i) T(NOU_CORE::move(m_data[i - 1])); //shift element to the right using move constructor
		}

		m_data[index].~T();

		construct(index, NOU_CORE::forward<ARGS>(args)...);

		m_size++;
	}

	template<typename T>
	void Vector<T>::insert(sizeType index, T &&data)
	{
		emplace(index, NOU_CORE::move(data));
	}

	template<typename T>
	void Vector<T>::insert(sizeType index, const T &data)
	{
		emplace(index, data);
	}

	template<typename T>
	void Vector<T>::sort()
	{
		///\todo implementing a "real" sorting alg.
		qsort(m_data, m_size);
	}

	template<typename T>
	void Vector<T>::sortComp(NOU::NOU_DAT_ALG::Comparator<T> comp)
	{
		///\todo implementing a "real" sorting alg.
		qsort(m_data, m_size, comp);
	}

	template<typename T>
	T* const & Vector<T>::data()
	{
		return m_data;
	}

	template<typename T>
	const T* Vector<T>::data() const
	{
		return m_data;
	}

	template<typename T>
	void Vector<T>::clear()
	{
		for (sizeType i = 0; i < m_size; i++)
		{
			at(i).~T();
		}
		m_size = 0;
		reallocateData(1);
	}

	template<typename T>
	void Vector<T>::setSize(sizeType size)
	{
		m_size = size;
	}

	template<typename T>
	Vector<T>& Vector<T>::replace(sizeType index, T&& replacement)
	{
		at(index) = NOU_CORE::move(replacement);
		return *this;
	}

	template<typename T>
	Vector<T>& Vector<T>::replace(sizeType index, const T& replacement)
	{
		NOU_COND_PUSH_ERROR((index > m_size),
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS, "No object was found at this index.");

		at(index) = replacement;
		return *this;
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

		//Delete all objects that are in the current vector, but will not overridden by elements in the other
		//one
		//If there are fewer elements in this vector than in the other one, nothing will happen
		for (sizeType i = other.m_size; i < m_size; i++)
			at(i).~T();

		sizeType i;

		/*
		First:  existing elements with the values from the other vector using copy-assign
		Second: Set uninitialized elements with the values from the other vector using copy-constr
		*/
		//####
		for (i = 0; i < NOU::NOU_CORE::min(m_size, other.m_size); i++) //copy-assign part
			at(i) = other.at(i);

		for (; i < other.m_size; i++) //copy-constr part
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

	template<typename T>
	VectorIterator<T> Vector<T>::begin()
	{
		return indexIterator(0);
	}

	template<typename T>
	VectorIterator<T> Vector<T>::end()
	{
		return indexIterator(m_size);
	}

	template<typename T>
	VectorIterator<T> Vector<T>::indexIterator(sizeType index)
	{
		return VectorIterator<T>(index, const_cast<const T**>(&m_data));
	}

	template<typename T>
	VectorConstIterator<T> Vector<T>::begin()const
	{
		return indexIterator(0);
	}

	template<typename T>
	VectorConstIterator<T> Vector<T>::end()const
	{
		return indexIterator(m_size);
	}

	template<typename T>
	VectorConstIterator<T> Vector<T>::indexIterator(sizeType index)const
	{
		return VectorConstIterator<T>(index, const_cast<const T**>(&m_data));
	}

	template<typename T>
	VectorReverseIterator<T> Vector<T>::rbegin()
	{
		return rindexIterator(m_size - 1);
	}

	template<typename T>
	VectorReverseIterator<T> Vector<T>::rend()
	{
		return rindexIterator(-1);
	}

	template<typename T>
	VectorReverseIterator<T> Vector<T>::rindexIterator(sizeType index)
	{
		return VectorReverseIterator<T>(index, const_cast<const T**>(&m_data));
	}

	template<typename T>
	VectorReverseConstIterator<T> Vector<T>::rbegin() const
	{
		return rindexIterator(m_size - 1);
	}

	template<typename T>
	VectorReverseConstIterator<T> Vector<T>::rend() const
	{
		return rindexIterator(-1);
	}

	template<typename T>
	VectorReverseConstIterator<T> Vector<T>::rindexIterator(sizeType index) const
	{
		return VectorReverseConstIterator<T>(index, const_cast<const T**>(&m_data));
	}

	template<typename T>
	constexpr VectorIterator<T>::VectorIterator(sizeType index, const T **dataPtr) :
		m_dataPtr(const_cast<T**>(dataPtr)), //const cast is safe at this point
		m_index(index)
	{}

	template<typename T>
	constexpr T& VectorIterator<T>::operator * ()
	{
		return *((*m_dataPtr) + m_index);
	}

	template<typename T>
	constexpr const T& VectorIterator<T>::operator * () const
	{
		return *((*m_dataPtr) + m_index);
	}

	template<typename T>
	constexpr T* VectorIterator<T>::operator -> ()
	{
		return ((*m_dataPtr) + m_index);
	}

	template<typename T>
	constexpr const T* VectorIterator<T>::operator -> () const
	{
		return ((*m_dataPtr) + m_index);
	}

	template<typename T>
	constexpr VectorIterator<T>& VectorIterator<T>::operator ++ ()
	{
		m_index++;

		return *this;
	}

	template<typename T>
	constexpr const VectorIterator<T>& VectorIterator<T>::operator ++ () const
	{
		m_index++;

		return *this;
	}

	template<typename T>
	constexpr VectorIterator<T> VectorIterator<T>::operator ++ (int) const
	{
		VectorIterator<T> ret = *this;

		m_index++;

		return ret;
	}

	template<typename T>
	constexpr boolean VectorIterator<T>::operator == (const VectorIterator<T> &other) const
	{
		return m_dataPtr == other.m_dataPtr && m_index == other.m_index;
	}

	template<typename T>
	constexpr boolean VectorIterator<T>::operator != (const VectorIterator<T> &other) const
	{
		return !(*this == other);
	}

	template<typename T>
	constexpr VectorIterator<T> VectorIterator<T>::operator + (sizeType value) const
	{
		return VectorIterator<T>(m_index + value, const_cast<const T**>(m_dataPtr));
	}

	template<typename T>
	constexpr VectorIterator<T> VectorIterator<T>::operator - (sizeType value) const
	{
		return VectorIterator<T>(m_index - value, const_cast<const T**>(m_dataPtr));
	}

	template<typename T>
	constexpr VectorIterator<T>& VectorIterator<T>::operator += (sizeType value)
	{
		m_index += value;

		return *this;
	}

	template<typename T>
	constexpr VectorIterator<T>& VectorIterator<T>::operator -= (sizeType value)
	{
		m_index -= value;

		return *this;
	}



	template<typename T>
	constexpr VectorReverseIterator<T>::VectorReverseIterator(sizeType index, const T **dataPtr) :
		m_dataPtr(const_cast<T**>(dataPtr)), //const cast is safe at this point
		m_index(index)
	{}

	template<typename T>
	constexpr T& VectorReverseIterator<T>::operator * ()
	{
		return *((*m_dataPtr) + m_index);
	}

	template<typename T>
	constexpr const T& VectorReverseIterator<T>::operator * () const
	{
		return *((*m_dataPtr) + m_index);
	}

	template<typename T>
	constexpr T* VectorReverseIterator<T>::operator -> ()
	{
		return ((*m_dataPtr) + m_index);
	}

	template<typename T>
	constexpr const T* VectorReverseIterator<T>::operator -> () const
	{
		return ((*m_dataPtr) + m_index);
	}

	template<typename T>
	constexpr VectorReverseIterator<T>& VectorReverseIterator<T>::operator ++ ()
	{
		m_index--;

		return *this;
	}

	template<typename T>
	constexpr const VectorReverseIterator<T>& VectorReverseIterator<T>::operator ++ () const
	{
		m_index--;

		return *this;
	}

	template<typename T>
	constexpr VectorReverseIterator<T> VectorReverseIterator<T>::operator ++ (int) const
	{
		VectorReverseIterator<T> ret = *this;

		m_index--;

		return ret;
	}

	template<typename T>
	constexpr boolean VectorReverseIterator<T>::operator == (const VectorReverseIterator<T> &other) const
	{
		return m_dataPtr == other.m_dataPtr && m_index == other.m_index;
	}

	template<typename T>
	constexpr boolean VectorReverseIterator<T>::operator != (const VectorReverseIterator<T> &other) const
	{
		return !(*this == other);
	}

	template<typename T>
	constexpr VectorReverseIterator<T> VectorReverseIterator<T>::operator + (sizeType value) const
	{
		return VectorReverseIterator<T>(m_index - value, const_cast<const T**>(m_dataPtr));
	}

	template<typename T>
	constexpr VectorReverseIterator<T> VectorReverseIterator<T>::operator - (sizeType value) const
	{
		return VectorReverseIterator<T>(m_index + value, const_cast<const T**>(m_dataPtr));
	}

	template<typename T>
	constexpr VectorReverseIterator<T>& VectorReverseIterator<T>::operator += (sizeType value)
	{
		m_index -= value;

		return *this;
	}

	template<typename T>
	constexpr VectorReverseIterator<T>& VectorReverseIterator<T>::operator -= (sizeType value)
	{
		m_index += value;

		return *this;
	}
}


#endif