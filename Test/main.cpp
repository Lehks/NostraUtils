#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\file_mngt\File.hpp"
#include "nostrautils\file_mngt\Path.hpp"
#include "nostrautils/core/SystemInformation.hpp"
#include <iostream>

using namespace std;
using namespace NOU;
using namespace NOU_CORE;
//using namespace NOU_CORE;
using namespace NOU_DAT_ALG;
using namespace NOU_FILE_MNGT;

int main()
{
	std::cout << SystemInformation::currentlyUsedMemory() << std::endl;
	std::cout << SystemInformation::totalPhysicalMemory() << std::endl;

	std::cin.get();
}							