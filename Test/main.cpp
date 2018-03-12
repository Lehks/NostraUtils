#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\Hashing.hpp"

#include <iostream>
#include <ctime>


int main()
{
	const char *msg = "Text";

	NOU::NOU_DAT_ALG::md5(reinterpret_cast<const NOU::byte*>(msg));

	system("pause");
}