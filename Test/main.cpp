#define NOU_DEBUG

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\mem_mngt\PoolAllocator.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\mem_mngt\GeneralPurposeAllocator.hpp"
#include "nostrautils\dat_alg\String.hpp"

#include <iostream>
#include <string>
#include <type_traits>


int main()
{
	NOU::NOU_DAT_ALG::String8 str = "HalloDennis";
	NOU::NOU_DAT_ALG::String8 str2 = "Dennis";

	str = str2;

	std::cout << str.rawStr() << std::endl;
	std::cout << str.size() << std::endl;

	system("pause");
}