#include "nostrautils\core\Logging.hpp"
#include <iostream>
#include <string>
#include <type_traits>

int main()
{
	using namespace NOU::NOU_CORE;

	NOU::NOU_CORE::Logger log;
	
	NOU::NOU_CORE::ConsoleLogger clog;
	log.pushLogger(clog);
	
	log.write(NOU::NOU_CORE::EventLevelCodes::ERROR, "Invalid value in fn()");

	using namespace std::chrono_literals;
	std::this_thread::sleep_for(1s);
	log.write(NOU::NOU_CORE::EventLevelCodes::FATAL, "Access violation in 0xDCDCDCDCDC");


	std::cin.get();
}