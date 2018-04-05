#include "nostrautils/NostraUtils.hpp"
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