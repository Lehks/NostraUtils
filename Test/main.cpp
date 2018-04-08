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
	NOU::NOU_DAT_ALG::String8 str = "ThisIsAString";
	NOU::NOU_DAT_ALG::String8 str2;

	str2 = str.replace("Is", "Integer", 0, 13);

	std::cout << str2.rawStr() << std::endl;

	system("pause");
}