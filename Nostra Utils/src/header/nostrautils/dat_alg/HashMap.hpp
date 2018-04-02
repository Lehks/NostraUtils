#ifndef NOU_DAT_ALG_HASHMAP_HPP
#define	NOU_DAT_ALG_HASHMAP_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\dat_alg\Hashing.hpp"
#include "nostrautils\dat_alg\Vector.hpp"

/** \file Vector.hpp
\author  Leslie Marxen
\author  Dennis Franz
\since   0.0.1
\version 0.0.1
\brief   This file provides a HashMap implementation.
*/

namespace NOU::NOU_DAT_ALG 
{
	/**
	\brief   This class provides a HashMap implementation using the bucket method.
	*/

	template<typename K, typename V>
	class NOU_CLASS HashMap 
	{
	private:
		/**
		\brief The default count of the internal used buckets.
		*/
		const static NOU::sizeType							LOAD_SIZE = 20;  //can be changed to minimize collisions -> the bigger the more ofthen O(1) occurs

		/**
		\brief count of current objects stored inside the map.
		*/
		sizeType											m_size;

		/**
		\brief Buckets containing dynamically growing arrays inside.
		*/
		Vector<Vector<NOU::NOU_DAT_ALG::Pair<K, V>>>		m_data;


	public:

		/**
		\brief "Standard" constructor.
		\param size the count of buckets used inside the map (the more the better but also more mem space is used)
		\param allocator the internally used mem allocator, defaults to NOU generic alloc
		*/
		HashMap(sizeType size = LOAD_SIZE, NOU::NOU_MEM_MNGT::AllocationCallback<Vector<NOU::NOU_DAT_ALG::Pair<K, V>>> &allocator = NOU_MEM_MNGT::GenericAllocationCallback<Vector<NOU::NOU_DAT_ALG::Pair<K, V>>>::getInstance());
		/**
		\brief Copy-constructor
		\param other the HasMap from where this one will copy
		*/
		HashMap(const HashMap &other);
		/**
		\brief Move-comstructor
		\param other the HashMap from where this one will move
		*/
		HashMap(HashMap &&other);

		/**
		\param			key the key where the value will be mapped to
		\param		    value the vaule that will be mapped
		\return			true if sucessfully mapped, false if otherwise
		\brief maps a value to a specific key
		*/
		NOU::boolean map(const K &key,const V &value);//WIP

		/**
		\param key		the key where a value will be returned
		\return value
		\brief Returns the corresponding value mapped to a specific key or nullptr if it does not exist
		*/
		V& get(const K &key);
		/**
		\brief Checks wether the map is empty or not.
		\return true if empty, false if otherwise
		*/
		boolean isEmpty();
		/**
		\return			the current count of values mapped
		\brief Returns the current size of the map.
		*/
		sizeType size();
		/**
		\return			a vector containing all currently used keys
		\brief Returns an Vector of the keys wich are stored in the map.
		*/
		Vector<K> keySet();
		/**
		\input		key the key of the valule that iwill be deleted;
		\brief Removes an Object wich the specific key.
		*/
		V& remove(K key);
		/**
		\return			a vector containing all currently used values
		\brief Returns an Vector of the Objects wich are stored in the map.
		*/
		Vector<V> entrySet();
		/**
		\input			K key that will be checked;
		\return			true if the key is contained inside the map;
		\brief Checks if the key is contained in the map.
		*/
		boolean containsKey(K key);
		/**
		\brief Overloading [] operators. Works now exactly like get();
		*/
		V& operator [](const K& key);

	};



	template <typename K, typename V>
	HashMap<K,V>::HashMap(sizeType size, NOU_MEM_MNGT::AllocationCallback<Vector<NOU_DAT_ALG::Pair<K, V>>> &allocator) :
		m_data(size, allocator),
		m_size(0)
	{
		for (sizeType i = 0; i < size; i++)
		{
			m_data.emplaceBack(Vector<Pair<K, V>>(0));
		}
	}
	 
	template<typename K, typename V>
	HashMap<K, V>::HashMap(const HashMap<K,V> & other) :
		m_data(other.m_data),
		m_size(other.m_size)
	{
		other.m_data.clear();
		other.m_data = NULL;
	}

	template<typename K, typename V>
	HashMap<K, V>::HashMap(HashMap<K,V> && other) :
		m_data(other.m_data),
		m_size(other.m_size)
	{
		other.m_data.clear();
		other.m_data = NULL;
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::map(const K &key,const V &value) 
	{
		sizeType n;

		Pair<K, V> tmpPair(key, value);

		n = hashObj(&key, m_data.capacity());

		if (m_data[n].size() == 0) 
		{	//if Vector at this position is empty, fill it -> O(1)
			m_data[n].emplaceBack(tmpPair);
			m_size++;
			return true;
		}
		else 
		{	//if a Vector in this position has elements, search if the given Key is already existing. If yes overwrite it;
			for (sizeType i = 0; i < m_data[n].size(); i++) 
			{
				if (m_data[n][i].dataOne == tmpPair.dataOne) 
				{
					m_data[n][i].dataTwo = tmpPair.dataTwo;
				}
			}
		
			//add tmp Pair at the end of the Vector -> O(n)
			m_data[n].emplaceBack(tmpPair);
			m_size++;
			return true;
		}
	}

	template <typename K, typename V>
	V& HashMap<K,V>::get(const K &key) 
	{
		sizeType n;
		n = hashObj(&key, m_data.capacity());

		if (m_data[n].size() == 0) 
		{	//if nothing is mapped to HashPos n, return null
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "No object was found.");
		}

		for (sizeType i = 0; i < m_data[n].size(); i++)
		{	//search for key in HashPos n
			if (m_data[n][i].dataOne == key)
			{
				return m_data[n][i].dataTwo;
			}
		}

		NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "No object was found.");
	}

	template<typename K, typename V>
	boolean HashMap<K, V>::isEmpty()
	{
		if (m_size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename K, typename V>
	sizeType HashMap<K, V>::size()
	{
		return m_size;
	}


	template <typename K, typename V>
	V& HashMap<K,V>::remove(K key)
	{
		sizeType h;
		Pair<K, V> tmpPair(key, this->get(key));

		h = hashObj(&key, m_size);

		for (sizeType i = 0; i < m_data[h].size(); i++)
		{
			if (m_data[h][i].dataOne == key)
			{
				m_data[h].remove(i);
			}
		}

		return tmpPair.dataTwo;
	}

	template<typename K, typename V>
	Vector<K> HashMap<K, V>::keySet()
	{
		Vector<K> keySetVec(1);

		for (sizeType i = 0; i < m_data.size(); i++)
		{
			if (m_data[i].size() != 0)
			{
				for (sizeType j = 0; j < m_data[i].size(); j++)
				{
					keySetVec.emplaceBack(m_data[i][j].dataOne);
				}
			}
		}
		return keySetVec;
	}

	template<typename K, typename V>
	Vector<V> HashMap<K, V>::entrySet()
	{
		Vector<V> entrySetVec(1);

		for (sizeType i = 0; i < m_data.size(); i++)
		{
			if (m_data[i].size() != 0)
			{
				for (sizeType j = 0; j < m_data[i].size(); j++)
				{
					entrySetVec.emplaceBack(m_data[i][j].dataTwo);
				}
			}
		}
		return entrySetVec;
	}
	template <typename K, typename V>
	boolean HashMap<K, V>::containsKey(K key) 
	{
		Vector<K> tmp = keySet();

		for (sizeType i = 0; i < tmp.size(); i++)
		{
			if (tmp.at(i) == key) {
				return true;
			}
		}
		return false;
	}

	template<typename K, typename V>
	V& HashMap<K,V>::operator [](const K &key) {
		return get(key);
	}
}
#endif