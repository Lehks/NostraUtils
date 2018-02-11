#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"

#include <cstddef>
#include <iostream>

namespace NOU::NOU_DAT_ALG
{
	template<typename T>
	class ObjectPool
	{
	public:
		using Type = T;

	public:
		struct Chunk //public for use in AllocationCallback
		{
			Type m_data;

			sizeType m_leftIndex;
			sizeType m_rightIndex;

			Chunk(Type &&data);
		};

	private:
		constexpr static sizeType INVALID_INDEX = -1;

		Vector<Chunk> m_data;

		sizeType m_head;

		Chunk* getChunkFromObject(const Type &object);

		void removeFromList(Chunk *chunk);
		void setAsHead(Chunk *chunk);

		Chunk* asPtr(sizeType index);
		const Chunk* asPtr(sizeType index) const;

		sizeType indexOf(Chunk *chunk) const;

	public:
		ObjectPool(sizeType initialCapacity = 0, NOU_MEM_MNGT::AllocationCallback<Chunk> &allocationCallback 
			= NOU_MEM_MNGT::GenericAllocationCallback<Chunk>::getInstance());

		void pushObject(const Type &object);
		void pushObject(Type &&object);

		template<typename... ARGS>
		void emplaceObject(ARGS&&... args);

		Type& get();

		void giveBack(const Type& object);

		sizeType size() const;
		boolean empty() const;
	};

	template<typename T>
	ObjectPool<T>::Chunk::Chunk(Type &&data) :
		m_data(NOU_CORE::forward<Type>(data))
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
		if(chunk->m_leftIndex != INVALID_INDEX)
			asPtr(chunk->m_leftIndex)->m_rightIndex = chunk->m_rightIndex;

		if (chunk->m_rightIndex != INVALID_INDEX)
			asPtr(chunk->m_rightIndex)->m_leftIndex = chunk->m_leftIndex;
	}

	template<typename T>
	void ObjectPool<T>::setAsHead(Chunk *chunk)
	{
		chunk->m_leftIndex = INVALID_INDEX;
		chunk->m_rightIndex = m_head;

		m_head = indexOf(chunk);
	}

	template<typename T>
	typename ObjectPool<T>::Chunk* ObjectPool<T>::asPtr(sizeType index)
	{
		//INVALID_INDEX will be translated to nullptr
		return index != INVALID_INDEX ? m_data.data() + index : nullptr;
	}

	template<typename T>
	const typename ObjectPool<T>::Chunk* ObjectPool<T>::asPtr(sizeType index) const
	{
		//INVALID_INDEX will be translated to nullptr
		return index != INVALID_INDEX ? m_data.data() + index : nullptr; 
	}

	template<typename T>
	sizeType ObjectPool<T>::indexOf(Chunk *chunk) const
	{
		//nullptr will be translated to INVALID_INDEX
		return chunk != nullptr ? m_data.data() - chunk : INVALID_INDEX;
	}

	template<typename T>
	ObjectPool<T>::ObjectPool(sizeType initialCapacity, 
		NOU_MEM_MNGT::AllocationCallback<Chunk> &allocationCallback):
		m_data(initialCapacity, allocationCallback),
		m_head(INVALID_INDEX)
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
		m_data.pushBack(Chunk(NOU_CORE::forward<ARGS>(args)...));

		setAsHead(m_data.data() + m_data.size() - 1); //set the just inserted chunk as head
	}

	template<typename T>
	typename ObjectPool<T>::Type& ObjectPool<T>::get()
	{
		NOU_COND_PUSH_DBG_ERROR(!(m_head == nullptr), NOU_CORE::getErrorHandler(), 
			NOU_CORE::ErrorCodes::INVALID_STATE, "The pool is empty. Use pushObject() to push a new object.");

		Chunk *head = asPtr(m_head);

		if (m_head != INVALID_INDEX)
		{
			//remove head & replace with the one following the head
			m_head = head->m_rightIndex;
			head->m_leftIndex = INVALID_INDEX;
		}

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
}