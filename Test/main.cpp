#include "nostrautils/core/Logging.hpp"

int main()
{
	using namespace NOU;
	using namespace NOU::NOU_CORE;
	using namespace NOU::NOU_DAT_ALG;
	using namespace NOU::NOU_THREAD;
	
	Logger* log = Logger::instance();
	Logger* log2 = Logger::instance();

	log->pushLogger<ConsoleLogger>();
	log2->pushLogger<FileLogger>();

	std::cout << "Main thread " << std::this_thread::get_id() << std::endl;
	
	using namespace std::chrono_literals;

	for (int i = 0; i < 200; i++)
	{
		log->write(NOU::NOU_CORE::EventLevelCodes::ERROR, "log.txt error");
		log->write(NOU::NOU_CORE::EventLevelCodes::ERROR, "log2.txt error", "log2.txt");
		log->write(NOU::NOU_CORE::EventLevelCodes::ERROR, "log3.txt error", "log3.txt");
		NOU_WRITE_LOG(log, NOU::NOU_CORE::EventLevelCodes::ERROR, "log4.txt error", "log4.txt");
		log->write(NOU::NOU_CORE::EventLevelCodes::UNKNWON, "Singleton successful");
		//std::this_thread::sleep_for(1s);
	}

	begin = currentTimeMillis();
	for (int i = 0; i < 1000000000; i++);
	end = currentTimeMillis();
	cout << "Time in ms: " << end - begin << endl;
	system("pause");
}