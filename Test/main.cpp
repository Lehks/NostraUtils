#include "nostrautils\core\Logging.hpp"
#include "nostrautils/mem_mngt/Utils.hpp"
#include <iostream>
#include <stdio.h>
#include <ctime>

void testTask()
{

}

int main()
{
	using namespace NOU;
	using namespace NOU::NOU_CORE;
	using namespace NOU::NOU_DAT_ALG;
	using namespace NOU::NOU_THREAD;
	NOU::NOU_CORE::Logger log;
	
	NOU::NOU_CORE::ConsoleLogger clog;
	NOU::NOU_CORE::FileLogger flog;

	log.pushLogger(clog);
	log.pushLogger(flog);

	std::cout << "Main thread " << std::this_thread::get_id() << std::endl;
	
	using namespace std::chrono_literals;
	for (int i = 0; i < 60; i++)
	{
		log.write(NOU::NOU_CORE::EventLevelCodes::ERROR, "log.txt error");
		log.write(NOU::NOU_CORE::EventLevelCodes::ERROR, "log2.txt error", "log2.txt");
		log.write(NOU::NOU_CORE::EventLevelCodes::ERROR, "log3.txt error", "log3.txt");
		NOU_WRITE_LOG(log, NOU::NOU_CORE::EventLevelCodes::ERROR, "log4.txt error", "log4.txt");
		std::this_thread::sleep_for(4s);
	}

	std::cin.get();
}							