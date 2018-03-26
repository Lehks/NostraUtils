#ifndef NOU_DAT_ALG_BINARY_SEARCH_HPP
#define NOU_DAT_ALG_BINARY_SEARCH_HPP

#include "nostrautils\dat_alg\Vector.hpp"

/** \file BinarySearch.hpp
\author	 Lukas Gross
\since   0.0.1
\version 0.0.1
\brief   This file provides a binary search algorithm.
*/
namespace NOU::NOU_DAT_ALG
{
	/**
	\tparam T The type of the array.

	\param vec A pointer to the array.

	\param key A reference to the value, you want to search for.

	\param start The start index of your search.

	\param end The end index of your search.

	\param insertionIndex A pointer to the index of the array where a new value would be inserted to stay 
	in a sorted order.

	\return -1 if the object was not found or the index of the object if it was found.

	\brief Makes a binary search for the key in a passed array.
	*/
	template<typename T>
	NOU_FUNC sizeType binarySearch
	(const T *vec, const T &key, int64 start, int64 end, sizeType *insertionIndex = nullptr);

	/**
	\tparam T The type of the array.

	\param vec A reference to a nostra::utils::dat_alg::Vector.

	\param key A reference to the value, you want to search for.

	\param start The start index of your search.

	\param end The end index of your search. If the parameter is -1 the binarySearch() will be called with
	end set to vec.size() - 1.

	\param insertionIndex A pointer to the index of the array where a new value would be inserted to stay in
	a sorted order.

	\return -1 if the object was not found or the index of the object if it was found.

	\brief Makes a binary search for the key in a passed array.

	\details Performs a binary search for the nostra::utils::dat_alg::Vector.
	*/
	template<typename T>
	NOU_FUNC sizeType binarySearch(const NOU::NOU_DAT_ALG::Vector<T> &vec, const T &key, 
		int64 start = 0, int64 end = -1, sizeType *insertionIndex = nullptr);

	template<typename T>
	NOU_FUNC sizeType binarySearch(const T *vec, const T &key,
		int64 start, int64 end, sizeType *insertionIndex)
	{
		if (start > end)
		{
			if (insertionIndex != nullptr)
				*insertionIndex = start;

			return -1;
		}
		const int64 middle = start + ((end - start) / 2);

		if (vec[middle] == key)
		{
			return middle;
		}
		else if (vec[middle] > key)
		{
			return binarySearch(vec, key, start, middle - 1, insertionIndex);
		}

		return binarySearch(vec, key, middle + 1, end, insertionIndex);
	}

	template<typename T>
	NOU_FUNC sizeType binarySearch(const NOU::NOU_DAT_ALG::Vector<T> &vec, const T &key,
		int64 start, int64 end, sizeType *insertionIndex)
	{
		return binarySearch(vec.data(), key, start, (end == -1) ? vec.size() - 1 : end, insertionIndex);
	}
}
#endif