#ifndef NOU_CORE_SYSTEM_INFORMATION_HPP
#define NOU_CORE_SYSTEM_INFORMATION_HPP

#include "nostrautils/core/StdIncludes.hpp"

namespace NOU::NOU_CORE
{
	namespace SystemInformation
	{
		/**
		\return The total amount of (physical) RAM that is available on the current system.

		\brief Returns the total amount of (physical) RAM that is available on the current system.
		*/
		uint64 NOU_FUNC totalPhysicalMemory();

		/**
		\return The amount of (physical) RAM that is used by the current process.

		\brief Returns the amount of (physical) RAM that is used by the current process.
		*/
		uint64 NOU_FUNC currentlyUsedMemory();
	}
}

#endif