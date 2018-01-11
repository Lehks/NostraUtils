#include "nostrautils\core\Logging.hpp"
#include <iostream>

int main()
{
	NOU::NOU_CORE::Logger log;

	NOU::NOU_CORE::ConsoleLogger clog;
	log.pushLogger(clog);

	log.write(NOU::NOU_CORE::EventLevelCodes::ERROR, "Invalid value in fn()");
	log.write(NOU::NOU_CORE::EventLevelCodes::FATAL, "Access violation in 0xDCDCDCDCDC");

	std::cin.get();
}