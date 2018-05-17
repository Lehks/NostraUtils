#ifndef NOU_DAT_ALG_HASHMAPTEST_HPP
#define	NOU_DAT_ALG_HASHMAPTEST_HPP

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
\details If an object that is not immutable will be stored it will result in some false states.
		 To fix this: Create an overloaded function of hashObj(T obj, objSize, sizeType max) 
		 that internally passes only the immutable data to the original function.
		 All stored objects need to overload the '==' operator.
*/

namespace NOU::NOU_DAT_ALG 
{

	/**
	\brief   This class provides a HashMap implementation using the bucket method.
	*/

	template<typename K, typename V>
	class NOU_CLASS HashMapT 
	{
	private:

		template<typename T>
		class NOU_CLASS Wrapper
		{
		private:
			T m_data;

		public:
			template<typename... ARGS>
			Wrapper(ARGS&&... args) : 
				m_data(NOU_CORE::forward<ARGS>(args)...)
			{}

			T& lval()
			{
				return m_data;
			}

			T rval()
			{
				return NOU_CORE::move(m_data); 
			}
		};

		/**
		\brief The default count of the internal used buckets.
		*/
		const static NOU::sizeType							LOAD_SIZE = 20;  //can be changed to minimize collisions -> the bigger the more often O(1) occurs

		/**
		\brief count of current objects stored inside the map.
		*/
		sizeType											m_size;

		/**
		\brief Buckets containing dynamically growing arrays inside.
		*/
		Vector<Vector<NOU::NOU_DAT_ALG::Pair<K, V>>>		m_data;


		boolean mapImp(Wrapper<K> &&key, Wrapper<V> &&value);
	public:

		/**
		\brief "Standard" constructor.
		\param size the count of buckets used inside the map (the more the better but also more mem space is used)
		\param allocator the internally used mem allocator, defaults to NOU generic alloc
		*/
		explicit HashMapT(sizeType size = 200, NOU::NOU_MEM_MNGT::AllocationCallback<Vector<NOU::NOU_DAT_ALG::Pair<K, V>>> &allocator = NOU_MEM_MNGT::GenericAllocationCallback<Vector<NOU::NOU_DAT_ALG::Pair<K, V>>>::getInstance());

		HashMapT(const HashMapT &other);

		HashMapT(HashMapT &&other);

		/**
		\param			key the key where the value will be mapped to
		\param		    value the value that will be mapped
		\param			keySize the size of the actual Data of the key
		\return			true if successfully mapped, false if otherwise
		\brief maps a value to a specific key
		*/
		boolean map(const K &key, const V &value);

		/**
		\param			key the key where the value will be mapped to
		\param		    value the value that will be mapped
		\param			keySize the size of the actual Data of the key
		\return			true if successfully mapped, false if otherwise
		\brief maps a value to a	 specific key
		*/
		boolean map(K &&key, V &&value);

		/**
		\param			key the key where the value will be mapped to
		\param		    value the value that will be mapped
		\param			keySize the size of the actual Data of the key
		\return			true if successfully mapped, false if otherwise
		\brief maps a value to a specific key
		*/
		boolean map(const K &key, V &&value);

		/**
		\param			key the key where the value will be mapped to
		\param		    value the value that will be mapped
		\param			keySize the size of the actual Data of the key
		\return			true if successfully mapped, false if otherwise
		\brief maps a value to a specific key
		*/
		boolean map(K &&key, const V &value);

		/**
		\param key		the key where a value will be returned
		\param			keySize the size of the actual Data of the key
		\return value
		\brief Returns the corresponding value mapped to a specific key or nullptr if it does not exist
		*/
		const V& get(const K &key) const;

		/**
		\param key		the key where a value will be returned
		\param			keySize the size of the actual Data of the key
		\return value
		\brief Returns the corresponding value mapped to a specific key or nullptr if it does not exist
		*/
		V& get(const K &key);

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
		Vector<K*> keySet();

		/**
		\return			A vector containing all currently used keys
		\brief Returns an Vector of the keys which are stored in the map.
		*/
		const Vector<K*> keySet() const;

		/**
		\param		key The key of the value that will be deleted
		\param		out An optional output parameter. If this is not \p nullptr, the object that was removed 
		                will be stored in it.
		\param		keyCount
		\brief Removes an Object which the specific key.
		*/
		boolean remove(const K &key, V *out = nullptr);

		/**
		\return			a vector containing all currently used values
		\brief Returns an Vector of the Objects which are stored in the map.
		*/
		Vector<V*> entrySet();

		/**
		\return			a vector containing all currently used values
		\brief Returns an Vector of the Objects which are stored in the map.
		*/
		const Vector<V*> entrySet() const;

		/**
		\param			key The key that will be checked;
		\return			true if the key is contained inside the map;
		\brief Checks if the key is contained in the map.
		*/
		boolean containsKey(const K &key) const;
	};


	template<typename K, typename V>
	HashMapT<K, V>::HashMapT(const HashMapT &other)
	{
		this-> m_size = other.size();
		this-> m_data = other.m_data;
	}

	template <typename K, typename V>
	HashMapT<K, V>::HashMapT(HashMapT &&other)
	{
		
	}

	template <typename K, typename V>
	boolean HashMapT<K, V>::mapImp(Wrapper<K> &&key, Wrapper<V> &&value) 
	{
		sizeType n;

		Pair<K, V> tmpPair(NOU_CORE::move(key.rval()), NOU_CORE::move(value.rval()));

		n = hashObj(&key, 1, m_data.size());

		if (m_data[n].size() == 0) 
		{	//if Vector at this position is empty, fill it -> O(1)
			m_data[n].emplaceBack(NOU_CORE::move(tmpPair));
			m_size++;
			return true;
		}
		else 
		{	//if a Vector in this position has elements, search if the given Key is already existing. If yes overwrite it;
			for (sizeType i = 0; i < m_data[n].size(); i++) 
			{
				if (m_data[n][i].dataOne == tmpPair.dataOne) 
				{
					if constexpr (std::is_move_assignable_v<V>)
					{
						m_data[n][i].dataTwo = NOU_CORE::move(tmpPair.dataTwo);
					}
					else
					{
						m_data[n][i].dataTwo.~V();
						new (&(m_data[n][i].dataTwo)) V(NOU_CORE::move(tmpPair.dataTwo));
					}

					return true;
				}
			}
		
			//add tmp Pair at the end of the Vector -> O(n)
			m_data[n].emplaceBack(NOU_CORE::move(tmpPair));
			m_size++;
		 }
	}

	template <typename K, typename V>
	HashMapT<K, V>::HashMapT(sizeType size, NOU_MEM_MNGT::AllocationCallback<Vector<NOU_DAT_ALG::Pair<K, V>>> &allocator) :
		m_data(size, allocator),
		m_size(0)
	{
		for (sizeType i = 0; i < size; i++)
		{
			m_data.emplaceBack(Vector<Pair<K, V>>());
		}
	} 
	 

	template <typename K, typename V>
	boolean HashMapT<K, V>::map(const K &key, const V &value) 
	{
		return mapImp(Wrapper<K>(key), Wrapper<V>(value));
	}

	template <typename K, typename V>
	const V& HashMapT<K,V>::get(const K &key) const
	{
		sizeType n;
		n = hashObj(&key, 1, m_data.size());

		if (m_data[n].size() == 0) 
		{	//if nothing is mapped to HashPos n, return null
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "No object was found.");
			return m_data.data()[0].data()[0].dataTwo;
		}

		for (sizeType i = 0; i < m_data[n].size(); i++)
		{	//search for key in HashPos n
			if (m_data[n][i].dataOne == key)
			{
				return m_data[n][i].dataTwo;
			}
		}

		NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "No object was found.");
		return m_data.data()[0].data()[0].dataTwo;
	}

	template <typename K, typename V>
	V& HashMapT<K,V>::get(const K &key)
	{
		sizeType n;
		n = hashObj(&key, 1, m_data.size());

		if (m_data[n].size() == 0) 
		{	//if nothing is mapped to HashPos n, return null
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "No object was found.");
			return m_data.data()[0].data()[0].dataTwo;
		}

		for (sizeType i = 0; i < m_data[n].size(); i++)
		{	//search for key in HashPos n
			if (m_data[n][i].dataOne == key)
			{
				return m_data[n][i].dataTwo;
			}
		}

		NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "No object was found.");
		return m_data.data()[0].data()[0].dataTwo;
	}

	template<typename K, typename V>
	boolean HashMapT<K, V>::isEmpty() const
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
	sizeType HashMapT<K, V>::size() const
	{
		return m_size;
	}

	template <typename K, typename V>
	boolean HashMapT<K, V>::remove(const K &key, V *out)
	{
		sizeType h;

		h = hashObj(&key, 1,m_data.size());

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
	Vector<K*> HashMapT<K, V>::keySet()
	{
		Vector<K> keySetVec(m_size);

		for (sizeType i = 0; i < m_data.size(); i++)
		{
			if (m_data[i].size() != 0)
			{
				for (sizeType j = 0; j < m_data[i].size(); j++)
				{
					keySetVec.emplaceBack(&(m_data[i][j].dataOne));
				}
			}
		}
		return keySetVec;
	}

	template<typename K, typename V>
	const Vector<K*> HashMapT<K, V>::keySet() const
	{
		Vector<K> keySetVec(m_size);

		for (sizeType i = 0; i < m_data.size(); i++)
		{
			if (m_data[i].size() != 0)
			{
				for (sizeType j = 0; j < m_data[i].size(); j++)
				{
					keySetVec.emplaceBack(&(m_data[i][j].dataOne));
				}
			}
		}
		return keySetVec;
	}

	template<typename K, typename V>
	const Vector<V*> HashMapT<K, V>::entrySet() const
	{
		Vector<V*> entrySetVec(m_size);

		for (sizeType i = 0; i < m_data.size(); i++)
		{
			if (m_data[i].size() != 0)
			{
				for (sizeType j = 0; j < m_data[i].size(); j++)
				{
					entrySetVec.emplaceBack(&(m_data[i][j].dataTwo));
				}
			}
		}
		return entrySetVec;
	}

	template<typename K, typename V>
	Vector<V*> HashMapT<K, V>::entrySet()
	{
		Vector<V*> entrySetVec(m_size);

		for (sizeType i = 0; i < m_data.size(); i++)
		{
			if (m_data[i].size() != 0)
			{
				for (sizeType j = 0; j < m_data[i].size(); j++)
				{
					entrySetVec.emplaceBack(&(m_data[i][j].dataTwo));
				}
			}
		}
		return entrySetVec;
	}

	template <typename K, typename V>
	boolean HashMapT<K, V>::containsKey(const K &key) const
	{
		Vector<K*> tmp = keySet();

		for (sizeType i = 0; i < tmp.size(); i++)
		{
			if (*(tmp.at(i)) == key) {
				return true;
			}
		}
		return false;
	}

	template <typename K, typename V>
	boolean HashMapT<K, V>::map(K &&key, V &&value)
	{
		return mapImp(Wrapper<K>(NOU_CORE::move(key)), Wrapper<V>(NOU_CORE::move(value)));
	}

	template <typename K, typename V>
	boolean HashMapT<K, V>::map(const K &key, V &&value)
	{
		return mapImp(Wrapper<K>(key), Wrapper<V>(NOU_CORE::move(value)));
	}

	template <typename K, typename V>
	boolean HashMapT<K, V>::map(K &&key, const V &value)
	{
		return mapImp(Wrapper<K>(NOU_CORE::move(key)), Wrapper<V>(value));
	}
	///\endcond
}
#endif