#include "nostrautils/core/Time.hpp"
#include <chrono>

namespace NOU::NOU_CORE
{
	uint32 currentTimeMillis()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	uint64 currentTimeNanos()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock.now().time_since_epoch()).count();
	}
}