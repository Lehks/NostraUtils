#ifndef NOU_DAT_ALG_QUICKSORT_HPP
#define NOU_DAT_ALG_QUICKSORT_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/dat_alg/Utils.hpp"
#include "nostrautils/dat_alg/Comparator.hpp"

/** \file Quicksort.hpp
\author  Mahan Karimi
\since   1.0.0
\version 1.0.0
\brief   This file provides a quicksort.
*/
namespace NOU::NOU_DAT_ALG
{
	

	/**
	\brief A function that Partitioning an Array with a given pivots.
	\tparam T The type.
	\param array Array .
	\param leftrangelimit for the left range limit.
	\param rightrangelimit for the right range limit.
	\param pivot the Index of the pivots.
	\return the pivots
	*/
	template <typename T>
	NOU_FUNC T partition(T *array, int64 leftrangelimit, int64 rightrangelimit, int64 pivot);

	/**
	\brief An implementation of the quicksort algorithm.
	\tparam T The type.
	\param a The array to sort.
	\param leftrangelimit for the left range limit.
	\param rightrangelimit for the right range limit.
	\return The sorted array.
	*/
	template<typename T >
	NOU_FUNC T* qsort(T *a, NOU::int64 leftrangelimit, NOU::int64 rightrangelimit);

	template<typename T>
	NOU_FUNC T partition(T *array, int64 leftrangelimit, int64 rightrangelimit, int64 pivot)
	{
		int64 pn = leftrangelimit;
		int64 pv = array[pivot];


		// pivot goes to end 
		swap(array + pivot, array + rightrangelimit);

		// all values smaller as pivot goes to the right side 
		for (int64 i = leftrangelimit; i < rightrangelimit; i++)
		{
			if (array[i] <= pv)
			{
				swap(array + pn, array + i);
				pn++;
			}
		}

		// pivot goes to his right position 
		swap(array + rightrangelimit, array + pn);

		return pn;
	}


	template<typename T >
	NOU_FUNC T* qsort(T *a, int64 leftrangelimit, int64 rightrangelimit)
	{
		
		if (rightrangelimit > leftrangelimit) {
			int64 p = rightrangelimit;
			int64 pn = partition(a, leftrangelimit, p, rightrangelimit);
			qsort(a, leftrangelimit, pn - 1);
			qsort(a, pn + 1, rightrangelimit);

		}
		return a;
	}


	
}
#endif