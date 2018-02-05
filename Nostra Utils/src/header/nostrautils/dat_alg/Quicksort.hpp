#ifndef NOU_DAT_ALG_QUICKSORT_HPP
#define NOU_DAT_ALG_QUICKSORT_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\dat_alg\Comparator.hpp"


/** \file Quicksort.hpp
\author  Mahan Karimi
\since   0.0.1
\version 0.0.1
\brief   This file provides a quicksort.
*/
namespace NOU::NOU_DAT_ALG
{
	/**
	\swap two values in an Array a[i] and a[j].
	\tparam a Array.
	\tparam i first index.
	\tparam j second index .
	*/
	template <typename T>
	void NOU_FUNC swap(T *array, sizeType fristindex, sizeType secondindex);

	/**
	\ a function that Partitioning an Array with a given pivots.
	\tparam a Array .
	\tparam l for the left range limit.
	\tparam r for the right range limit.
	\tparam p the Index of the pivots. 
	\return the pivots
	*/
	template <typename T>
	T NOU_FUNC partition(T *array, sizeType leftrangelimit, sizeType rightrangelimit, sizeType pivot);

	/**
	\Quickort 
	\tparam a that Array will sorted.
	\tparam l for the left range limit.
	\tparam r for the right range limit.
	\return sorted array. 
	*/
	template<typename T >
	T* NOU_FUNC qsort(T *a, sizeType leftrangelimit, sizeType rightrangelimit);

	/**
    \Quicksort 
	\tparam a that array what will be sort
	\return sorted array
	*/
	template<typename T>
	T* NOU_FUNC quicksort(T*a); 

	template <typename T >
	void NOU_FUNC swap(T *array, sizeType firstindex, sizeType secondindex) 
	{
		T n = NOU_CORE::move(array[firstindex]);
		array[firstindex] = array[secondindex]; 
		array[secondindex] = n; 

	}


	template<typename T>
	T NOU_FUNC partition(T *array, sizeType leftrangelimit, sizeType rightrangelimit, sizeType pivot)
	{
		sizeType pn = leftrangelimit; 
		sizeType pv = array[pivot]; 


		// pivot goes to end 
		swap(array, pivot, rightrangelimit);

		// all values smaller as pivot goes to the right side 
		for (sizeType i = leftrangelimit; i < rightrangelimit; i++) 
		{
			if (array[i] <= pv)
			{
				swap(array, pn, i); 
				pn++
			}
		}

		// pivot goes to his right position 
		swap(array, r, pn); 
		 
		return pn; 

	}


	template<typename T >
	T* NOU_FUNC qsort(T *a, sizeType leftrangelimit, sizeType rightrangelimit)
	{
		if (rightrangelimit > leftrangelimit) {
			sizeType p = r; 
			sizeType pn = partition(a, leftrangelimit, p, rightrangelimit); 
			NOU_FUNC qsort(a, leftrangelimit, pn - 1); 
			NOU_FUNC qsort(a, pn + 1, rightrangelimit); 

		}
		return a; 
	}


	template<typename T>
	T* NOU_FUNC quicksort(T*a)
	{
		return qsort(a, 0, sizeof(a) - 1); 
	}







}
#endif