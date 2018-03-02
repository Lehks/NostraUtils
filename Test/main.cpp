#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include <iostream>
#include "nostrautils\dat_alg\Quicksort.hpp"
#include "nostrautils\dat_alg\Vector.hpp"

int arr[5] = { 2,1,3,4,5 };

int main()
{

	NOU::NOU_DAT_ALG::qsort(arr, 0, 5);

	for (int i = 0; i < 5; i++)
	{

		std::cout << arr[i] << std::endl;

	}




	system("pause"); 
 
	
}
