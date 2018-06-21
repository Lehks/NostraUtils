#ifndef NOU_DAT_ALG_HASHMAP_HPP
#define	NOU_DAT_ALG_HASHMAP_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/mem_mngt/AllocationCallback.hpp"
#include "nostrautils/core/ErrorHandler.hpp"
#include "nostrautils/dat_alg/Hashing.hpp"
#include "nostrautils/dat_alg/Vector.hpp"

#include <type_traits>

/** 
\file	 dat_alg/HashMap.hpp
\author  Leslie Marxen
\author  Dennis Franz
\author  Lukas Reichmann
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
		constexpr static NOU::sizeType LOAD_SIZE = 20;

	private:

		/**
		\tparam The type of the object to store. This will either be \p K or \p V.

		\brief A container that wraps around a single value. This is required for the implementation of map().

		\details
		A container that wraps around a single value. This is required for the implementation of map().

		This wrapper is required because:

		map() has several overloads, one for each combination of L- and R-Values of all key and value objects 
		possible (the combinations are: \f$\{(K\&, V\&), (K\&\&, V\&) (K\&, V\&\&), (K\&\&, V\&\&)\})\f$

		To avoid the necessity of having to implement the method for each overload, a method called mapImpl()
		was implemented, which is called by all of the overloads.

		This method mapImpl() takes all of its parameters as R-Value which cause errors with some types 
		(e.g. pointers did not seem to work). By using type deduction, the constructor of this class avoids 
		this problem by sometimes copying the value instead of moving it (which is not a performance problem 
		with pointers).

		The data that is then stored in this wrapper can later be accessed using rval(), which will move the 
		data out of the wrapper class.

		\note
		As soon as rval() was called once, the data will be moved out of the wrapper and the stored object may
		be in an invalid state.
		*/
		template<typename T>
		class Wrapper
		{
		private:
			/**
			\brief The stored object.
			*/
			T m_data;

		public:
			/**
			\tparam ARGS The types of the arguments that the wrapped object will be constructed from.

			\param args The arguments that the wrapped object will be constructed from.

			\brief Constructs a new instance and constructs the wrapped object from the passed parameter(s).

			\details
			Constructs a new instance and constructs the wrapped object from the passed parameter(s). The 
			construction of the wrapped object will behave like this:

			\code{cpp}
			T(NOU::NOU_CORE::forward<ARGS>(args)...)
			\endcode
			*/
			template<typename... ARGS>
			Wrapper(ARGS&&... args);

			/**
			\return The wrapped object as an L-Value reference.

			\brief Returns the wrapped object as an L-Value reference.
			*/
			T& lval();

			/**
			\return The wrapped object.

			\brief The wrapped object.

			\attention
			This method can only be called once since it does not copy the wrapped object but instead moves 
			it.
			*/
			T rval();
		};

		/**
		\brief The amount of objects that are currently stored in the map.
		*/
		sizeType											m_size;

		/**
		\brief The buckets.
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

		/**
		\param key   The key to map the value to.
		\param value The value that will be mapped to the key.

		\return True, if the key-value-pair could be put into the map, false if not. As of now, the method 
		        will always return true.

		\brief The implementation of the algorithm that adds a key-value-pair to the map. This method will 
		       use the operator == for comparisons of keys.
		*/
		boolean mapImp(Wrapper<K> &&key, Wrapper<V> &&value);

		/**
		\param key   The key to map the value to.
		\param value The value that will be mapped to the key.
		\param comp The comparator that will used to compare keys.

		\return True, if the key-value-pair could be put into the map, false if not. As of now, the method
		will always return true.

		\brief The implementation of the algorithm that adds a key-value-pair to the map. This method will 
		       use the passed comparator for comparisons of keys.
		*/
		boolean mapImp(Wrapper<K> &&key, Wrapper<V> &&value, Comparator<K> comp);

	public:

		/**
		\param size      The amount of buckets that are available to the map. The more buckets there are, the
		                 more often access times can be in \f$O(1)\f$ (but the amount of memory used will 
						 also rise).
		\param allocator The allocator that will be used to allocate the buckets.

		\brief Creates a new instance from the passes parameters.
		*/
		explicit HashMap(sizeType size = LOAD_SIZE, NOU::NOU_MEM_MNGT::AllocationCallback<Vector<
			NOU::NOU_DAT_ALG::Pair<K, V>>> &allocator = NOU_MEM_MNGT::GenericAllocationCallback<Vector<
			NOU::NOU_DAT_ALG::Pair<K, V>>>::get());

		/**
		\param key     The key that the passed value will be mapped to.
		\param value   The value that will be mapped to the passed key.

		\return	True, if the key-value-pair was successfully added to the map, false if not. As of now, the 
		        adding of new pairs will never fail, hence only true will be returned.

		\brief Adds a new value and a new key that the values is mapped to.

		\details
		Adds a new value and a new key that the values is mapped to.

		This method will use the operator == for comparisons of keys.

		\attention
		If a key already exists in the map, the value that is mapped to that key will be overridden.

		\note
		In reality, there are many more overloads for this method that are not documented here for the sake of
		clarity. Those overloads take different combinations of L- and R-Values.
		*/
		boolean map(const K &key, const V &value);

		///\cond

		boolean map(K &&key, V &&value);

		boolean map(const K &key, V &&value);

		boolean map(K &&key, const V &value);

		///\endcond

		/**
		\param key   The key that the passed value will be mapped to.
		\param value The value that will be mapped to the passed key.
		\param comp  The comparator that will used to compare keys.

		\return	True, if the key-value-pair was successfully added to the map, false if not. As of now, the
		adding of new pairs will never fail, hence only true will be returned.

		\brief Adds a new value and a new key that the values is mapped to.

		\details
		Adds a new value and a new key that the values is mapped to.

		This method will use the passed comparator for comparisons of keys.

		\attention
		If a key already exists in the map, the value that is mapped to that key will be overridden.

		\note
		In reality, there are many more overloads for this method that are not documented here for the sake of
		clarity. Those overloads take different combinations of L- and R-Values.
		*/
		boolean map(const K &key, const V &value, Comparator<K> comp);

		///\cond

		boolean map(K &&key, V &&value, Comparator<K> comp);

		boolean map(const K &key, V &&value, Comparator<K> comp);

		boolean map(K &&key, const V &value, Comparator<K> comp);

		///\endcond

		/**
		\param key The key of the value that should be returned.

		\return The value that is mapped to \p key.

		\brief Returns the value that is mapped to \p key, or an invalid value if no value is mapped to the
		       key (see detailed section).

		\details
		Returns the value that is mapped to \p key, or an invalid value if no value is mapped to the.

		This method uses the operator == for key comparisons.

		In the case that the method fails, an error is pushed to the error handler. 

		\warning
		In the case of failure, the returned object is invalid and accessing it in any way might result in
		undefined behavior.
		*/
		V& get(const K &key);

		/**
		\param key The key of the value that should be returned.

		\return The value that is mapped to \p key.

		\brief Returns the value that is mapped to \p key, or an invalid value if no value is mapped to the
		key (see detailed section).

		\details
		Returns the value that is mapped to \p key, or an invalid value if no value is mapped to the.

		This method uses the operator == for key comparisons.

		In the case that the method fails, an error is pushed to the error handler.

		\warning
		In the case of failure, the returned object is invalid and accessing it in any way might result in
		undefined behavior.
		*/
		const V& get(const K &key) const;

		/**
		\param key  The key of the value that should be returned.
		\param comp The comparator that will used to compare keys.

		\return The value that is mapped to \p key.

		\brief Returns the value that is mapped to \p key, or an invalid value if no value is mapped to the	
		key (see detailed section).

		\details
		Returns the value that is mapped to \p key, or an invalid value if no value is mapped to the.

		This method uses the passed comparator for key comparisons.

		In the case that the method fails, an error is pushed to the error handler.

		\warning
		In the case of failure, the returned object is invalid and accessing it in any way might result in
		undefined behavior.
		*/
		const V& get(const K &key, Comparator<K> comp) const;

		/**
		\param key  The key of the value that should be returned.
		\param comp The comparator that will used to compare keys.

		\return The value that is mapped to \p key.

		\brief Returns the value that is mapped to \p key, or an invalid value if no value is mapped to the
		key (see detailed section).

		\details
		Returns the value that is mapped to \p key, or an invalid value if no value is mapped to the.

		This method uses the passed comparator for key comparisons.

		In the case that the method fails, an error is pushed to the error handler.

		\warning
		In the case of failure, the returned object is invalid and accessing it in any way might result in
		undefined behavior.
		*/
		V& get(const K &key, Comparator<K> comp);

		/**
		\return \p true if empty, \p false if not.

		\brief Returns whether the map is empty or not.
		*/
		boolean isEmpty() const;

		/**
		\return Returns the amount 
		of key-value-pairs that are currently in the map.

		\brief Returns the amount of key-value-pairs that are currently in the map.
		*/
		sizeType size() const;

		/**
		\param		key The key of the value that will be removed.
		\param		out An optional output parameter. If this is not \p nullptr, the object that was removed 
		                will be stored in it.

		\brief Removes an object which the specific key.
		*/
		boolean remove(const K &key, V *out = nullptr);

		/**
		\return A vector that contains all keys that currently have a value mapped to them.

		\brief Returns a vector that contains all keys that currently have a value mapped to them.
		*/
		Vector<const K*> keySet() const;

		/**
		\return A vector that contains all values that currently are mapped to a key.

		\brief Returns a vector that contains all values that currently are mapped to a key.
		*/
		Vector<const V*> entrySet() const;

		/**
		\param key The key that will be checked.

		\return \p true if the key is contained inside the map, \p false if not.

		\brief Returns whether the key is contained in the map. This method will use the operator == for 
		       comparisons of keys.
		*/
		boolean containsKey(const K &key) const;

		/**
		\param key The key that will be checked.
		\param comp The comparator that will used to compare keys.

		\return \p true if the key is contained inside the map, \p false if not.

		\brief Returns whether the key is contained in the map. This method will use the passed comparator for
		comparisons of keys.
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
		\param key The key of the value that should be returned.

		\return Same as get(const K&).

		\brief Same as get(const K&).

		\note
		There is no array subscript operator overload for get(const K&, Comparator<K>).
		*/
		V& operator [](const K& key);
	};

	///\cond

	template <typename K, typename V>
	template<typename T>
	template<typename... ARGS>
	HashMap<K, V>::Wrapper<T>::Wrapper(ARGS&&... args) :
		m_data(NOU_CORE::forward<ARGS>(args)...)
	{}

	template <typename K, typename V>
	template<typename T>
	T& HashMap<K, V>::Wrapper<T>::lval()
	{
		return m_data;
	}

	template <typename K, typename V>
	template<typename T>
	T HashMap<K, V>::Wrapper<T>::rval()
	{
		return NOU_CORE::move(m_data);
	}

	template <typename K, typename V>
	constexpr NOU::sizeType HashMap<K, V>::LOAD_SIZE;

	template <typename K, typename V>
	NOU::NOU_DAT_ALG::Pair<K, V>* HashMap<K, V>::getPair(const K &key)
	{
		NOU::sizeType hash = hashObj(&key, 1, m_data.size());

		NOU::sizeType size = m_data[hash].size();

		if (size == 0) 
			return nullptr;
		else
		{
			for (auto &pair : m_data[hash])
				if (pair.dataOne == key)
					return &pair;

			return nullptr;
		}
	}

	template <typename K, typename V>
	NOU::NOU_DAT_ALG::Pair<K, V>* HashMap<K, V>::getPair(const K &key, Comparator<K> comp)
	{
		NOU::sizeType hash = hashObj(&key, 1, m_data.size());

		NOU::sizeType size = m_data[hash].size();

		if (size == 0) 
			return nullptr;
		else 
		{
			for (auto &pair : m_data[hash]) 
				if (comp(pair.dataOne, key) == 0) 
					return &pair;

			return nullptr;
		}
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::mapImp(Wrapper<K> &&key, Wrapper<V> &&value) 
	{
		sizeType n;

		Pair<K, V> tmpPair(NOU_CORE::move(key.rval()), NOU_CORE::move(value.rval()));
		
		n = hashObj(&tmpPair.dataOne, 1, m_data.size());

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
			return true;
		}
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::mapImp(Wrapper<K> &&key, Wrapper<V> &&value, Comparator<K> comp)
	{
		sizeType n;

		Pair<K, V> tmpPair(NOU_CORE::move(key.rval()), NOU_CORE::move(value.rval()));

		n = hashObj(&tmpPair.dataOne, 1, m_data.size());

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
				if (comp(m_data[n][i].dataOne, tmpPair.dataOne) == 0)
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
			return true;
		}
	}

	template <typename K, typename V>
	HashMap<K, V>::HashMap(sizeType size, NOU_MEM_MNGT::AllocationCallback<Vector<NOU_DAT_ALG::Pair<K, V>>> &allocator) :
		m_data(size, allocator),
		m_size(0)
	{
		for (sizeType i = 0; i < size; i++)
		{
			m_data.emplaceBack(Vector<Pair<K, V>>());
		}
	}
	 
	template <typename K, typename V>
	boolean HashMap<K, V>::map(const K &key, const V &value) 
	{
		return mapImp(Wrapper<K>(key), Wrapper<V>(value));
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::map(K &&key, V &&value)
	{
		return mapImp(Wrapper<K>(NOU_CORE::move(key)), Wrapper<V>(NOU_CORE::move(value)));
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::map(const K &key, V &&value)
	{
		return mapImp(Wrapper<K>(key), Wrapper<V>(NOU_CORE::move(value)));
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::map(K &&key, const V &value)
	{
		return mapImp(Wrapper<K>(NOU_CORE::move(key)), Wrapper<V>(value));
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::map(const K &key, const V &value, Comparator<K> comp)
	{
		return mapImp(Wrapper<K>(key), Wrapper<V>(value), comp);
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::map(K &&key, V &&value, Comparator<K> comp)
	{
		return mapImp(Wrapper<K>(NOU_CORE::move(key)), Wrapper<V>(NOU_CORE::move(value)), comp);
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::map(const K &key, V &&value, Comparator<K> comp)
	{
		return mapImp(Wrapper<K>(key), Wrapper<V>(NOU_CORE::move(value)), comp);
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::map(K &&key, const V &value, Comparator<K> comp)
	{
		return mapImp(Wrapper<K>(NOU_CORE::move(key)), Wrapper<V>(value), comp);
	}

	template <typename K, typename V>
	V& HashMap<K, V>::get(const K &key)
	{
		sizeType n;
		n = hashObj(&key, 1, m_data.size());
		NOU::NOU_DAT_ALG::Pair<K, V> *pair = getPair(key);

		if (pair == nullptr)
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT,
				"No object was found.");

			return m_data.data()[0].data()[0].dataTwo;
		}
		else
		{
			return pair->dataTwo;
		}
	}

	template <typename K, typename V>
	const V& HashMap<K,V>::get(const K &key) const
	{
		sizeType n;
		n = hashObj(&key, 1, m_data.size());
		NOU::NOU_DAT_ALG::Pair<K, V> *pair = getPair(key);

		if(pair == nullptr) 
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, 
				"No object was found.");

			return m_data.data()[0].data()[0].dataTwo;
		}
		else 
		{
			return pair->dataTwo;
		}
	}

	template <typename K, typename V>
	V& HashMap<K, V>::get(const K &key, Comparator<K> comp)
	{
		NOU::NOU_DAT_ALG::Pair<K, V> *pair = getPair(key, comp);

		if (pair == nullptr) 
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, 
				"No object was found.");

			return m_data.data()[0].data()[0].dataTwo;
		}
		else 
		{
			return pair->dataTwo;
		}
	}

	template <typename K, typename V>
	const V& HashMap<K, V>::get(const K &key, Comparator<K> comp) const
	{
		NOU::NOU_DAT_ALG::Pair<K, V> *pair = getPair(key, comp);

		if (pair == nullptr)
		{
			NOU_PUSH_ERROR(NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT,
				"No object was found.");

			return m_data.data()[0].data()[0].dataTwo;
		}
		else
		{
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
	boolean HashMap<K, V>::remove(const K &key, V *out)
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
	Vector<const K*> HashMap<K, V>::keySet() const
	{
		Vector<const K*> keySetVec(m_size);

		for (sizeType i = 0; i < m_data.size(); i++)
		{
			for (sizeType j = 0; j < m_data[i].size(); j++)
			{
				keySetVec.emplaceBack(&m_data[i][j].dataOne);
			}
		}
		return keySetVec;
	}

	template<typename K, typename V>
	Vector<const V*> HashMap<K, V>::entrySet() const
	{
		Vector<const V*> entrySetVec(m_size);

		for (sizeType i = 0; i < m_data.size(); i++)
		{
			for (sizeType j = 0; j < m_data[i].size(); j++)
			{
				entrySetVec.emplaceBack(&m_data[i][j].dataTwo);
			}
		}
		return entrySetVec;
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::containsKey(const K &key) const 
	{
		return const_cast<HashMap<K, V>*>(this)->getPair(key) != nullptr;
	}

	template <typename K, typename V>
	boolean HashMap<K, V>::containsKey(const K &key, Comparator<K> comp) const 
	{
		return const_cast<HashMap<K, V>*>(this)->getPair(key, comp) != nullptr;
	}

	template<typename K, typename V>
	V& HashMap<K, V>::operator [](const K &key) 
	{
		return get(key);
	}

	template<typename K, typename V>
	NOU::sizeType HashMap<K, V>::bucketCount() const 
	{
		return m_data.size();
	}

	///\endcond
}
#endif