#ifndef NOU_DAT_ALG_HASHMAP_HPP
#define	NOU_DAT_ALG_HASHMAP_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\Hashing.hpp"
#include "nostrautils\dat_alg\Vector.hpp"

/** \file Vector.hpp
\author  Leslie Marxen	
\since   0.0.1
\version 0.0.1
\brief   This file provides a HashMap implementation.
*/

namespace NOU::NOU_DAT_ALG {

	template<typename K, typename V>
	class NOU_CLASS HashMap {
	private:

		const static sizeType LOAD_SIZE = 20;  //can be changed to minimize collisions -> the bigger the more ofthen O(1) occurs

		struct Pair {
		public:
			K &key;
			V &value;
		};	//helper struct to help identify Values
		Vector<Pair> pairs[LOAD_SIZE]; //actual storage
	public:

		/**
		\brief "Standard" constructor.
		*/
		HashMap();//WIP

		/**
		\param key the key where the value will be mapped to
		\param value
		\return true if sucessfully mapped
		\brief maps a value to a specific key;
		*/
		boolean add(K &key, V &value);//WIP

		/**
		\param key the key on where a value will be returned
		\brief returns the corresponding value mapped to a specific key
		*/
		V& get(K &key);//WIP

		//TODO:
		/*
		~HashMap();
		V remove(K key)
		at(sizeType index);
		boolean containsKey(K key);
		sizeType size();
		boolean isEmpty();
		Vector keySet();
		Vector entrySet();
		*/

		V& operator [](K& key);


	};
	template <typename K, typename V>
	HashMap<K,V>::HashMap() {
		//initialize all Vectors;
		for (int i = 0; i < LOAD_SIZE; i++) {
			pairs[i]();
		}
	}


	template <typename K, typename V>
	boolean HashMap<K, V>::add(K &key, V &value) {
		sizeType n;
		Vector tmpVector;
		Pair tmpPair;

		n = hashObj(key, LOAD_SIZE);
		tmpPair.key = key;
		tmpPair.value = value;

		if (pairs[n].size() == 0) {	//if Vector at this position is empty, fill it -> O(1)
			tmp.emplaceBack(tmpPair);
			pairs[n] = tmpVector;
			return true;
		}
		else {	//if a Vector in this position has elements, search if the given Key is already existing. If yes return false;
			for (int i = 0; i < pairs[n].size(); i++) {
				if (pairs[n][i].key == tmpPair.key) {
					return false;
				}
			}

			//add tmp Pair at the end of the Vector -> O(n)
			pairs[n].emplaceBack(tmpPair)
			return true;
		}
		
	}

	template <typename K, typename V>
	V& HashMap<K,V>::get(K &key) {
		sizeType n;
		
		n = hashObj(key, LOAD_SIZE);
		Pair *tmpPair;

		if (pairs[n] == NULL) {	//if nothing is mapped to HashPos n, return null
			return NULL;
		}

		for (int i = 0; i < pairs[n].size(); i++) {	//search for key in HashPos n
			tmpPair = pairs[n][i];
			if (tmpPair->key == tmpPair->key) {
				return tmpPair->value;
			}
		}

		return NULL;
	}


	template<typename K, typename V>
	V& HashMap<K,V>::operator [](K &key) {
		return this->get(key);
	}
}
#endif