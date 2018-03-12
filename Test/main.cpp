#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\Random.hpp"   
#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <ctime>

NOU::uint64 values[11] = {0};

int main()
{
	NOU::NOU_DAT_ALG::Random r;

#if 1
	for (int i = 0; i < 10000; i++)
		values[r.rand(0, 10)]++;

	for (int i = 0; i < 11; i++)
		std::cout << (i) << " " << values[i] << std::endl;
#endif

#if 0
	for (int i = 0; i < 1000; i++)
		if (NOU::uint64 ra = r.rand(1, 10); ra % 2 == 1)
			std::cout << "Ungerade: " << ra << std::endl;
#endif


	

	
	system("Pause"); 
}