#include "nostrautils\core\Logging.hpp"

namespace NOU::NOU_CORE
{

	ILogger::StringType ILogger::getTime()
	{
		time_t now = time(0);

		StringType localTime = ctime(&now);

		return localTime;
	}

	void ILogger::writeLog(StringType eventLevel, StringType eventMsg, ILogger &log)
	{
		log.write(eventLevel, eventMsg);
	}

	void Logger::pushLogger(ILogger &log)
	{
		s_logger.pushBack(&log);
	}

	NOU::NOU_MEM_MNGT::GenericAllocationCallback<ILogger*> Logger::s_allocator;
	NOU::NOU_DAT_ALG::Vector<ILogger*> Logger::s_logger(1, s_allocator);

	void Logger::logAll(StringType eventLevel, StringType eventMsg)
	{
		for (sizeType i = 0; i < s_logger.capacity(); i++)
		{
			s_logger[i]->writeLog(eventLevel, eventMsg, *s_logger[i]);
		}
	}
}
