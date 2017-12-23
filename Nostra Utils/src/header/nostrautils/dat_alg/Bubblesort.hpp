#ifndef NOU_DAT_ALG_BUBBLESORT_HPP
#define NOU_DAT_ALG_BUBBLESORT_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\Utils.hpp"

namespace NOU::NOU_DAT_ALG
{

	template<typename T>
	void NOU_FUNC bubbleSort(T container, sizeType size);


	template<typename T>
	void bubbleSort(T container, sizeType size)
	{
		T tempdata;
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
}

#endif 

