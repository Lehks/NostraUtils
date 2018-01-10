#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\core\Logging.hpp"
#include <iostream>

int main()
{
	NOU::NOU_CORE::Logger log;

	NOU::NOU_CORE::ConsoleLogger clog;
	NOU::NOU_CORE::EventLevelCodes evc;

	std::cout << evc.getLevel(0).rawStr() << std::endl;
	std::cout << evc.getLevel(1).rawStr() << std::endl;
	std::cout << evc.getLevel(2).rawStr() << std::endl;
	log.pushLogger(clog);

	log.logAll("Error", "Critical error in 0x000000");

	clog.writeLog("Error", "Critical error in 0x000000", clog);
	clog.writeLog("Error", "Critical error in 0x000000", clog);



	std::cin.get();
}