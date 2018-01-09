#include "nostrautils\core\Logging.hpp"

namespace NOU::NOU_CORE
{

	Logger::StringType Logger::getTime()
	{
		time_t now = time(0);

		StringType dt = ctime(&now);

		return dt;
	}
}
