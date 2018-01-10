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

	log.pushLogger(clog);

	log.logAll(0, "Critical error in 0x000000");
	clog.writeLog(1, "Critical error in 0x000000", clog);
	clog.writeLog(2, "Critical error in 0x000000", clog);



	std::cin.get();
}