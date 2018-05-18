#ifndef NOU_DAT_ALG_HASHMAP_HPP
#define	NOU_DAT_ALG_HASHMAP_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/mem_mngt/AllocationCallback.hpp"
#include "nostrautils/core/ErrorHandler.hpp"
#include "nostrautils/dat_alg/Hashing.hpp"
#include "nostrautils/dat_alg/Vector.hpp"

/** \file Vector.hpp
\author  Leslie Marxen
\author  Dennis Franz
\since   1.0.0
\version 1.0.0
\brief   This file provides a HashMap implementation.
*/

namespace NOU::NOU_DAT_ALG 
{
	/**
	\brief   This class provides a HashMap implementation using the bucket method.
	*/

	template<typename K, typename V>
	class HashMap 
	{
	public:
		/**
		\brief The default count of the internal used buckets.
		*/
		//can be changed to minimize collisions -> the bigger the more often O(1) occurs
		constexpr static NOU::sizeType						LOAD_SIZE = 20;

	private:
		/**
		\brief count of current objects stored inside the map.
		*/
		sizeType											m_size;

		/**
		\brief Buckets containing dynamically growing arrays inside.
		*/
		Vector<Vector<NOU::NOU_DAT_ALG::Pair<K, V>>>		m_data;

		/**
		\param key The key to search.

		\return A pointer to the pair if it is in the map. If not, \p nullptr.

		\brief Searches for the pair with the passed key. Compares keys using the operator ==.
		*/
		NOU::NOU_DAT_ALG::Pair<K, V>* getPair(const K &key);

		/**
		\param key  The key to search.
		\param comp The comparator to use.

		\return A pointer to the pair if it is in the map. If not, \p nullptr.

		\brief Searches for the pair with the passed key. Compares keys using the passed comparator.
		*/
		NOU::NOU_DAT_ALG::Pair<K, V>* getPair(const K &key, Comparator<K> comp);

	public:

		/**
		\brief "Standard" constructor.
		\param size the count of buckets used inside the map (the more the better but also more mem space is used)
		\param allocator the internally used mem allocator, defaults to NOU generic alloc
		*/
		HashMap(sizeType size = LOAD_SIZE, NOU::NOU_MEM_MNGT::AllocationCallback<Vector<NOU::NOU_DAT_ALG::Pair<K, V>>> &allocator = NOU_MEM_MNGT::GenericAllocationCallback<Vector<NOU::NOU_DAT_ALG::Pair<K, V>>>::getInstance());
		/**
		\param			key the key where the value will be mapped to
		\param		    value the value that will be mapped
		\return			true if successfully mapped, false if otherwise
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
		\param key		the key where a value will be returned
		\return value
		\brief Returns the corresponding value mapped to a specific key or nullptr if it does not exist
		*/
		V& get(const K &key, Comparator<K> comp);
		/**
		\brief Checks whether the map is empty or not.
		\return true if empty, false if otherwise
		*/
		boolean isEmpty() const;
		/**
		\return			the current count of values mapped
		\brief Returns the current size of the map.
		*/
		sizeType size() const;
		/**
		\return			A vector containing all currently used keys
		\brief Returns an Vector of the keys which are stored in the map.
		*/
		Vector<K> keySet() const;
		/**
		\param		key The key of the value that will be deleted
		\param		out An optional output parameter. If this is not \p nullptr, the object that was removed 
		                will be stored in it.
		\brief Removes an Object which the specific key.
		*/
		boolean remove(const K &key, V *out = nullptr);
		/**
		\return			a vector containing all currently used values
		\brief Returns an Vector of the Objects which are stored in the map.
		*/
		Vector<V> entrySet() const;
		/**
		\param			key The key that will be checked;
		\return			true if the key is contained inside the map;
		\brief Checks if the key is contained in the map.
		*/
		boolean containsKey(const K &key) const;
		/**
		\param			key  The key that will be checked.
		\param			comp The comparator that will be used to check two keys for equality.
		\return			true if the key is contained inside the map;
		\brief Checks if the key is contained in the map.
		*/
		boolean containsKey(const K &key, Comparator<K> comp) const;
		/**
		\return The amount of buckets in this hash map.

		\brief Returns the amount of buckets in this hash map.

		\details
		Returns the amount of buckets in this hash map. This is the exact value that was passed as the first 
		value to the constructor, or, in the case that there were now values passed, \p LOAD_SIZE.
		*/
		NOU::sizeType bucketCount() const;
		/**
		\brief Overloading [] operators. Works now exactly like get();
		*/
		V& operator [](const K& key);
	};

	template <typename K, typename V>
	constexpr NOU::sizeType HashMap<K, V>::LOAD_SIZE;

	template <typename K, typename V>
	NOU::NOU_DAT_ALG::Pair<K, V>* getPair(const K &key) {
		NOU::sizeType hash = hashObj(&key, 1, m_data.size());

		NOU::sizeType size = m_data[hash].size();

		if (size == 0) {
			return false;
		}
		else {
			for (auto &pair : m_data[hash]) {
				if (pair.dataone == key) {
					return &pair;
				}
			}
		}
	}

	template <typename K, typename V>
	NOU::NOU_DAT_ALG::Pair<K, V>* getPair(const K &key, Comparator<K> comp) {
		NOU::sizeType hash = hashObj(&key, 1, m_data.size());

		NOU::sizeType size = m_data[hash].size();

		if (size == 0) {
			return nullptr;
		}
		else {
			for (auto &pair : m_data[hash]) {
				if (comp(pair.dataone, key) == 0) {
					return &pair;
				}
			}

			return nullptr;
		}
	}

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
	 

	template <typename K, typename V>
	boolean HashMap<K, V>::map(const K &key,const V &value) 
	{
		sizeType n;

		Pair<K, V> tmpPair(key, value);

		n = hashObj(&key, 1, m_data.size());

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
		NOU::NOU_DAT_ALG::Pair<K, V> *pair = getPair(key);

		if(pair == nullptr) {
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, 
				"No object was found.");

			return m_data.data()[0].data()[0].dataTwo;
		}
		else {
			return pair->dataTwo;
		}
	}

	template <typename K, typename V>
	V& HashMap<K, V>::get(const K &key, Comparator<K> comp)
	{
		NOU::NOU_DAT_ALG::Pair<K, V> *pair = getPair(key, comp);

		if (pair == nullptr) {
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, 
				"No object was found.");

			return m_data.data()[0].data()[0].dataTwo;
		}
		else {
			return pair->dataTwo;
		}
	}

	template<typename K, typename V>
	boolean HashMap<K, V>::isEmpty() const
	{
		return m_size == 0;
	}

	template<typename K, typename V>
	sizeType HashMap<K, V>::size() const
	{
		return m_size;
	}


	template <typename K, typename V>
	boolean HashMap<K,V>::remove(const K &key, V *out)
	{
		sizeType h;

		h = hashObj(&key, 1, m_data.size());

		for (sizeType i = 0; i < m_data[h].size(); i++)
		{
			if (m_data[h][i].dataOne == key)
			{
				if (out != nullptr)
				{
					*out = NOU_CORE::move(m_data[h][i].dataTwo);
				}
				m_data[h].remove(i);
				return true;
			}
		}

		return false;
	}

	template<typename K, typename V>
	Vector<K> HashMap<K, V>::keySet() const
	{
		Vector<K> keySetVec(size());

		for (sizeType i = 0; i < m_data.size(); i++)
		{
			for (sizeType j = 0; j < m_data[i].size(); j++)
			{
				keySetVec.emplaceBack(m_data[i][j].dataOne);
			}
		}
		return keySetVec;
	}

	template<typename K, typename V>
	Vector<V> HashMap<K, V>::entrySet() const
	{
		Vector<V> entrySetVec(size());

		for (sizeType i = 0; i < m_data.size(); i++)
		{
			for (sizeType j = 0; j < m_data[i].size(); j++)
			{
				entrySetVec.emplaceBack(m_data[i][j].dataTwo);
			}
		}
		return entrySetVec;
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::containsKey(const K &key) const {
		return getPair(key) != nullptr;
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::containsKey(const K &key, Comparator<K> comp) const {
		return getPair(key, comp) != nullptr;
	}

	template<typename K, typename V>
	V& HashMap<K, V>::operator [](const K &key) {
		return get(key);
	}

	template<typename K, typename V>
	NOU::sizeType HashMap<K, V>::bucketCount() const {
		return m_data.size();
	}

	template<typename K, typename V>
	V& HashMap<K,V>::operator [](const K &key) {
		return get(key);
	}


	///\endcond
}
#endif
