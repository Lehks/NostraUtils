#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\HashMap.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include <iostream>


int main()
{
	NOU::NOU_DAT_ALG::HashMap<NOU::NOU_DAT_ALG::StringView<NOU::char8>, NOU::uint32> hm(100);

	NOU::NOU_DAT_ALG::StringView<NOU::char8>str("Hallo");

	hm.add(str, 15);

	std::cout << hm.get(str) << std::endl;

	system("pause");
}