#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include <iostream>


int main()
{
	NOU::NOU_DAT_ALG::Vector<NOU::int32> vec1(1);
	NOU::NOU_DAT_ALG::Vector<NOU::int32> vec2(1);

	int b = 10;
	for (int i = 0; i < 10; i++)
	{
		vec1.pushBack(b);
		b--;
		std::cout << vec1[i] << std::endl;
	}

	vec1.sortComp();

	for (int i = 0; i < 10; i++)
	{
		std::cout << vec1[i] << std::endl;
	}


	int a;
	NOU::NOU_MEM_MNGT::DebugAllocationCallback<NOU::int32> dbgAlloc;
	std::cin >> a;

	{
		NOU::NOU_DAT_ALG::Vector<NOU::int32> vec4(1, dbgAlloc);

		for (int i = 0; i <= 1000000; i++)
		{
			vec4.pushBack(i);
		}

		std::cout << dbgAlloc.getCounter() << std::endl;

		std::cin >> a;
	}

	std::cin >> a;

	//Do testing here
}