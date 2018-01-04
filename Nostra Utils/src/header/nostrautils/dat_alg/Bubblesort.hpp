#ifndef NOU_DAT_ALG_BUBBLESORT_HPP
#define NOU_DAT_ALG_BUBBLESORT_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\dat_alg\Comparator.hpp"

/** \file Bubblesort.hpp
\author  Dennis Franz
\since   0.0.1
\version 0.0.1
\brief   This file provides a simple "placeholder" bubblesort.
*/

namespace NOU::NOU_DAT_ALG
{
	/**
	\tparam		The type of the container to sort.
	\param size The size of the container.

	\brief Sorts the Conatiner .
	*/
	template<typename T>
	void NOU_FUNC bubbleSort(T container, sizeType size);
	/**
	\tparam		The type of the container to sort.
	\param size The size of the container.

	\brief Sorts the Conatiner using comperators.
	*/
	template<typename T>
	void NOU_FUNC bubbleSortComp(T container, sizeType size);

	template<typename T>
	void bubbleSort(T container, sizeType size)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = i+1; j < size; j++)
			{
				if (container[i] > container[j])
				{
					swap(&container[i], &container[j]);
				}
			}
		}
	}

	template<typename T>
	void bubbleSortComp(T container, sizeType size)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (NOU::NOU_DAT_ALG::genericComparator(container[i], container[j]) == NOU::NOU_DAT_ALG::CompareResult::BIGGER)
				{
					swap(&container[i], &container[j]);
				}
			}
		}
	}

}

#endif 

