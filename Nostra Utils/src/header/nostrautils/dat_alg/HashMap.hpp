#ifndef NOU_DAT_ALG_HASHMAP_HPP
#define	NOU_DAT_ALG_HASHMAP_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\dat_alg\Hashing.hpp"
#include "nostrautils\dat_alg\Vector.hpp"

/** \file Vector.hpp
\author  Leslie Marxen	
\since   0.0.1
\version 0.0.1
\brief   This file provides a HashMap implementation.
*/

namespace NOU::NOU_DAT_ALG 
{

	template<typename K, typename V>
	class NOU_CLASS HashMap 
	{
	private:

		const static sizeType							 LOAD_SIZE = 20;  //can be changed to minimize collisions -> the bigger the more ofthen O(1) occurs

		Vector<Vector<NOU::NOU_DAT_ALG::Pair<K, V>>>	 m_data;


	public:

		/**
		\brief "Standard" constructor.
		*/
		HashMap(sizeType size = LOAD_SIZE, NOU::NOU_MEM_MNGT::AllocationCallback<Vector<NOU::NOU_DAT_ALG::Pair<K, V>>> &allocator = NOU_MEM_MNGT::GenericAllocationCallback<Vector<NOU::NOU_DAT_ALG::Pair<K, V>>>::getInstance());//WIP
		HashMap(const HashMap &other);
		HashMap(HashMap &&other);

		/**
		\param key the key where the value will be mapped to
		\param value
		\return true if sucessfully mapped
		\brief maps a value to a specific key;
		*/
		boolean add(const K &key,const V &value);//WIP

		/**
		\param key the key on where a value will be returned
		\brief returns the corresponding value mapped to a specific key
		*/
		V& get(const K &key);//WIP

		boolean isEmpty();

		sizeType size();


		//TODO:
		/*
		V remove(K key)
		boolean containsKey(K key);
		Vector keySet();
		Vector entrySet();
		*/

		V& operator [](const K& key);


	};



	template <typename K, typename V>
	HashMap<K,V>::HashMap(sizeType size, NOU::NOU_MEM_MNGT::AllocationCallback<Vector<NOU::NOU_DAT_ALG::Pair<K, V>>> &allocator) :
		m_data(size, allocator)
	{
		for (sizeType i = 0; i < size; i++)
		{
			m_data.emplaceBack(Vector<NOU::NOU_DAT_ALG::Pair<K, V>>(0));
		}
	}
	 
	template<typename K, typename V>
	HashMap<K, V>::HashMap(const HashMap<K,V> & other) :
		m_data(other.m_data)
	{
		other.m_data.clear();
		other.m_data = NULL;
	}

	template<typename K, typename V>
	HashMap<K, V>::HashMap(HashMap<K,V> && other) :
		m_data(other.m_data)
	{
		other.m_data.clear();
		other.m_data = NULL;
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::add(const K &key,const V &value) 
	{
		sizeType n;

		Pair<K, V> tmpPair(key, value);

		n = hashObj(&key, m_data.capacity());

		if (m_data[n].size() == 0) 
		{	//if Vector at this position is empty, fill it -> O(1)
			m_data[n].emplaceBack(tmpPair);
			return true;
		}
		else 
		{	//if a Vector in this position has elements, search if the given Key is already existing. If yes return false;
			for (sizeType i = 0; i < m_data[n].size(); i++) 
			{
				if (m_data[n][i].dataOne == tmpPair.dataOne) 
				{
					return false;
				}
			}
		
			//add tmp Pair at the end of the Vector -> O(n)
			m_data[n].emplaceBack(tmpPair);
			return true;
		}

	}

	template <typename K, typename V>
	V& HashMap<K,V>::get(const K &key) 
	{
		sizeType n;
		n = hashObj(&key, LOAD_SIZE);

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
		return m_data.empty();
	}

	template<typename K, typename V>
	sizeType HashMap<K, V>::size()
	{
		return m_data.size();
	}

	template<typename K, typename V>
	V& HashMap<K,V>::operator [](const K &key) {
		return get(key);
	}
}
#endif