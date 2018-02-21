#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\HashMap.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include <iostream>


int main()
{
	NOU::NOU_DAT_ALG::HashMap<NOU::char8, NOU::int32> hm(100);
	NOU::NOU_DAT_ALG::String<NOU::char8> str = "The quick onyx goblin jumps over the lazy dwarf";
	NOU::boolean b;

	b = hm.isEmpty();
	std::cout << b;

	for (NOU::sizeType i = 0; i < str.size(); i++) {
		b = hm.map(str.at(i), 1);
	}

	b = hm.isEmpty();
	std::cout << b;

	for (int i = 0; i < str.size(); i++) {
	//	Assert::AreEqual(hm.get(str.at(i)), 1);
	}
}