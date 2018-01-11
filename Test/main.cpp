#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\math\Utils.hpp"
#include <iostream>


int main()
{
	NOU::int32 a = -(-51231);

	std::cout << NOU::NOU_MATH::abs(a) << std::endl;

	system("pause");
}