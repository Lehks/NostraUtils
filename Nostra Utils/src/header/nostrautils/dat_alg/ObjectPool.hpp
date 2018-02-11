#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\core\Assertions.hpp"

#include <cstddef>

/** \file Vector.hpp
\author  Lukas Reichmann
\since   0.0.1
\version 0.0.1
\brief   This file provides the nostra::utils::dat_alg::ObjectPool container.

\see nostra::utils::dat_alg::ObjectPool
*/

namespace NOU::NOU_DAT_ALG
{
	/**
	\tparam T The type of objects to store.

	\brief A container that stores a pool of pre-allocated objects. The container has a maximum size and can
	       not grow larger that size.

	\details
	This class is somewhat similar to nostra::utils::mem_mngt::PoolAllocator, but instead of constructing a 
	new object each time, the objects in this container stay constructed for the entire lifetime. This is
	useful if a class does a lot of dynamic allocations during its construction. 
	After the construction of this object, 

	\note
	The order in which the objects in the pool will be distributed is not defined - a user can not make any 
	assumptions on which concrete object will be returned. It is a good practice to have the objects in the 
	container share the same state.
	*/
	template<typename T>
	class ObjectPool
	{
	public:
		/**
		\brief The type of object that will be stored in the pool.
		*/
		using Type = T;

	public:
		/**
		\brief A struct that will be used to store the data and pointer to build a double linked list. This is
		       only public to allow a custom nostra::utils::mem_mngt::AllocationCallback.
		*/
		struct Chunk
		{
			/**
			\brief The stored data.
			*/
			Type m_data;

			/**
			\brief A pointer to the left neighbor in the linked list.
			*/
			Chunk* m_left;

			/**
			\brief A pointer to the right neighbor in the linked list.
			*/
			Chunk* m_right;

			/**
			\param data The data to store.

			\brief Constructs a new instance that stores the passed data.
			*/
			Chunk(Type &&data);
		};

	private:
		/**
		\brief The vector in which the different chunks are being stored.
		*/
		Vector<Chunk> m_data;

		/**
		\brief The start of the linked list that links the single chunk to build the actual pool.
		*/
		Chunk* m_head;

		/**
		\brief The amount of objects left in the pool for distribution.
		*/
		sizeType m_objectsLeft;

		/**
		\param object The object to determine the chunk of.

		\return The chunk in which the passed object is stored in.

		\brief Returns a pointer to the chunk that the passed object is stored in.
		*/
		Chunk* getChunkFromObject(const Type &object);

		/**
		\param chunk The chunk to remove.

		\brief Removes the passed chunk from the linked list.
		*/
		void removeFromList(Chunk *chunk);

		/**
		\param chunk The chunk to set as head.

		\brief Sets the passed chunk as the head of the list.
		*/
		void setAsHead(Chunk *chunk);

	public:
		/**
		\param capacity           The capacity of the pool. It is not possible to push more objects that this 
		                          capacity.
		\param allocationCallback The callback to allocate the chunk of data to store the objects in.

		\brief Constructs a new instance.
		*/
		ObjectPool(sizeType capacity, NOU_MEM_MNGT::AllocationCallback<Chunk> &allocationCallback 
			= NOU_MEM_MNGT::GenericAllocationCallback<Chunk>::getInstance());

		ObjectPool(const ObjectPool&) = delete;
		ObjectPool(ObjectPool&&) = delete;

		/**
		\param object The object to push.

		\brief Pushes a new object into the pool. At most, this can be called capacity() times.
		*/
		void pushObject(const Type &object);

		/**
		\param object The object to push.

		\brief Pushes a new object into the pool. At most, this can be called capacity() times.
		*/
		void pushObject(Type &&object);

		/**
		\tparam ARGS The types of the parameters that will be used to construct the new object.

		\param args The parameters that will be used to construct the new object.

		\brief Pushes a new object into the pool. This object will be constructed from the parameters that 
		       were passed to this method. At most, this can be called capacity() times.
		*/
		template<typename... ARGS>
		void emplaceObject(ARGS&&... args);

		/**
		\return An object from the pool.

		\brief Returns an object from the pool.
		*/
		Type& get();

		/**
		\param object The object to return to the pool.

		\brief Gives an object back to the pool. It is only valid to give back objects that were previously 
		       obtained from get() from that very same pool.
		*/
		void giveBack(const Type& object);

		/**
		\return The size of the pool.

		\brief Returns the amount of objects that are currently in the pool. This includes objects that are 
		       distributed by the pool and those that are ready for being distributed.
		*/
		sizeType size() const;

		/**
		\return size() == 0

		\brief Returns size() == 0.
		*/
		boolean empty() const;

		/**
		\return The maximum amount of objects that can be stored in this pool.

		\brief Returns the maximum amount of objects that can be stored in this pool.
		*/
		sizeType capacity() const;

		/**
		\return The amount of objects left for distribution.

		\brief Returns the amount of objects left for distribution.
		*/
		sizeType objectsLeft() const;
	};

	template<typename T>
	ObjectPool<T>::Chunk::Chunk(Type &&data) :
		m_data(NOU_CORE::forward<Type>(data)),
		m_objectsLeft(0)
	{}

	template<typename T>
	typename ObjectPool<T>::Chunk* ObjectPool<T>::getChunkFromObject(const Type &object)
	{
		//calculate address of the chunk
		return reinterpret_cast<Chunk*>(reinterpret_cast<byte*>(const_cast<Type*>(&object)) 
			- offsetof(Chunk, m_data));
	}

	template<typename T>
	void ObjectPool<T>::removeFromList(Chunk *chunk)
	{
		if(chunk->m_left != nullptr)
			chunk->m_left->m_right = chunk->m_right;

		if (chunk->m_right != nullptr)
			chunk->m_right->m_left = chunk->m_left;
	}

	template<typename T>
	void ObjectPool<T>::setAsHead(Chunk *chunk)
	{
		chunk->m_left = nullptr;
		chunk->m_right = m_head;

		m_head = chunk;
	}

	template<typename T>
	ObjectPool<T>::ObjectPool(sizeType capacity,
		NOU_MEM_MNGT::AllocationCallback<Chunk> &allocationCallback):
		m_data(capacity, allocationCallback),
		m_head(nullptr)
	{}

	template<typename T>
	void ObjectPool<T>::pushObject(const Type &object)
	{
		emplaceObject(object);
	}

	template<typename T>
	void ObjectPool<T>::pushObject(Type &&object)
	{
		emplaceObject(NOU_CORE::move(object));
	}

	template<typename T>
	template<typename... ARGS>
	void ObjectPool<T>::emplaceObject(ARGS&&... args)
	{
#ifdef NOU_DEBUG
		sizeType oldCapacity = m_data.capacity()
		NOU_ASSERT(m_data.size() != m_data.capacity()); //check that the capacity has not changed
#endif


		if (m_data.size() >= m_data.capacity()) //if full \todo set error & prevent vector from reallocating
		{
			NOU_PUSH_DBG_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_STATE, 
				"The pool is full. No more objects can be pushed to it.");
			return;
		}

		m_data.pushBack(Chunk(NOU_CORE::forward<ARGS>(args)...));

		m_objectsLeft++; //there is now one more object left

#ifdef NOU_DEBUG
		NOU_ASSERT(oldCapacity == m_data.capacity()); //check that the capacity has not changed
#endif

		setAsHead(m_data.data() + m_data.size() - 1); //set the just inserted chunk as head
	}
	
	template<typename T>
	typename ObjectPool<T>::Type& ObjectPool<T>::get()
	{
		NOU_COND_PUSH_DBG_ERROR(!(m_head == nullptr), NOU_CORE::getErrorHandler(), 
			NOU_CORE::ErrorCodes::INVALID_STATE, "The pool is empty. Use pushObject() to push a new object.");

		Chunk *head = m_head;

		if (m_head != nullptr)
		{
			//remove head & replace with the one following the head
			m_head = head->m_right;
			head->m_left = nullptr;
		}

		m_objectsLeft--;

		return head->m_data;
	}

	template<typename T>
	void ObjectPool<T>::giveBack(const Type& object)
	{
		//error if the pointer to the object is not within bounds of the internal vector
		NOU_COND_PUSH_DBG_ERROR(&object >= m_dataPtr && &object < m_dataPtr + m_data.size(),
			NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, 
			"The passed object is not part of the object pool.");

#ifdef NOU_DEBUG
		if (!(&object >= m_dataPtr && &object < m_dataPtr + m_data.size()))
			return; //abort in debug
#endif
		Chunk *chunk = getChunkFromObject(object);

		removeFromList(chunk);

		setAsHead(chunk);

		m_objectsLeft++;
	}

	template<typename T>
	sizeType ObjectPool<T>::size() const
	{
		return m_data.size();
	}

	template<typename T>
	boolean ObjectPool<T>::empty() const
	{
		return size() == 0;
	}

	template<typename T>
	sizeType ObjectPool<T>::capacity() const
	{
		return m_data.capacity();
	}

	template<typename T>
	sizeType ObjectPool<T>::objectsLeft() const
	{
		return m_objectsLeft;
	}
}