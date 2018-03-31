#include "nostrautils\core\Logging.hpp"
#include <iostream>
#include <string>
#include <type_traits>

class Person
{
	NOU::NOU_CORE::Logger log;

	NOU::NOU_CORE::ConsoleLogger clog;
	log.pushLogger(clog);

	log.write(NOU::NOU_CORE::EventLevelCodes::ERROR, "Invalid value in fn()");
	log.write(NOU::NOU_CORE::EventLevelCodes::FATAL, "Access violation in 0xDCDCDCDCDC");

	std::cin.get();
}