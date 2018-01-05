#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include <iostream>


int main()
{
	NOU::NOU_DAT_ALG::String<NOU::char8> str("hallo");

	std::cout << str.size() << std::endl;

	system("pause");
	//Do testing here
}