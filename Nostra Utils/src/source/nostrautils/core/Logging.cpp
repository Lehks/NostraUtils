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
}
