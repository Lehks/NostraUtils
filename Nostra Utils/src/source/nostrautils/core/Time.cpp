#include <chrono>

#include "nostrautils/core/Time.hpp"


namespace NOU::NOU_CORE
{
	uint32 currentTimeMillis()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	uint64 currentTimeNanos()
	{
		std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::nanoseconds>(t.time_since_epoch()).count();
	}
}