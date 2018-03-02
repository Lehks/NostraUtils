#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\HashMap.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include <iostream>


int main()
{
	NOU::int64 i1 = 243536768574;
	NOU::int64 i2 = 243536768574;

	NOU::sizeType h = NOU::NOU_DAT_ALG::hashObj(&i1, 20);
	std::cout << h << std::endl << NOU::NOU_DAT_ALG::hashObj(&i2, 20) << std::endl;

	NOU::NOU_DAT_ALG::String<NOU::char8> str1 = "The quick onyx goblin jumps over the lazy dwarf";
	NOU::NOU_DAT_ALG::String<NOU::char8> str2 = "The quick onyx goblin jumps over the lazy dwarf";

	h = NOU::NOU_DAT_ALG::hashObj(&str1, 20);

	std::cout << h << std::endl << NOU::NOU_DAT_ALG::hashObj(&str2, 20) << std::endl;

	system("pause");
}