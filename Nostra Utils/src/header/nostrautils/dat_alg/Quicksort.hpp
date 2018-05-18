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
	NOU_FUNC T partition(T *array, CompareResult leftrangelimit, CompareResult rightrangelimit, CompareResult pivot);

	/**
	\brief An implementation of the quicksort algorithm.
	\tparam T The type.
	\param a The array to sort.
	\param leftrangelimit for the left range limit.
	\param rightrangelimit for the right range limit.
	\return The sorted array.
	*/
	template<typename T >
	NOU_FUNC T* qsort(T *a, CompareResult leftrangelimit, CompareResult rightrangelimit, Comparator<T> comp);

	template<typename T>
	NOU_FUNC T partition(T *array, CompareResult leftrangelimit, CompareResult rightrangelimit, CompareResult pivot, Comparator<T> comp)
	{
		CompareResult pn = leftrangelimit;
		T &pv = array[pivot];


		// pivot goes to end 
		swap(array + pivot, array + rightrangelimit);

		// all values smaller as pivot goes to the right side 
		for (CompareResult i = leftrangelimit; comp (i,rightrangelimit) < 0; i++)
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
	NOU_FUNC T* qsort(T *a, CompareResult leftrangelimit, CompareResult rightrangelimit, Comparator<T> comp)
	{
		
		if (genericComparator(rightrangelimit , leftrangelimit) < 0) {
			CompareResult p = rightrangelimit;
			CompareResult pn = partition(a, leftrangelimit, p, rightrangelimit, comp);
			qsort(a, leftrangelimit, pn - 1, comp);
			qsort(a, pn + 1, rightrangelimit, comp);

		}
		return a;
	}


	
}
#endif