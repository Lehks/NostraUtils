#include "nostrautils/NostraUtils.hpp"
#include <iostream>
#include <ctime>

using namespace std;
using namespace NOU;
using namespace NOU_CORE;
//using namespace NOU_CORE;
using namespace NOU_DAT_ALG;

int main()
{
	std::cout << SystemInformation::currentlyUsedMemory() << std::endl;
	std::cout << SystemInformation::totalPhysicalMemory() << std::endl;

	std::cin.get();
}							