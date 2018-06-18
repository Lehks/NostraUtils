#include "nostrautils/core/SystemInformation.hpp"

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
#include <Windows.h>
#include <Psapi.h>
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#        include <sys/sysctl.h>
#        include <sys/types.h>
#		 include <sys/resource.h>
#endif

namespace NOU::NOU_CORE
{
	namespace SystemInformation
	{
		uint64 NOU_FUNC totalPhysicalMemory()
		{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
			MEMORYSTATUSEX memStatus;
			memStatus.dwLength = sizeof(MEMORYSTATUSEX);
			GlobalMemoryStatusEx(&memStatus);

			return memStatus.ullTotalPhys;
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
			int mib [] = { CTL_HW, HW_MEMSIZE };
			int64_t value = 0;
			size_t length = sizeof(value);

			sysctl(mib, 2, &value, &length, NULL, 0);

			return value;

#else
			return 0; ///\todo Support other systems.
#endif
		}

		uint64 NOU_FUNC currentlyUsedMemory()
		{
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
			PROCESS_MEMORY_COUNTERS pmc;
			GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(PROCESS_MEMORY_COUNTERS));

			return pmc.WorkingSetSize;
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
			struct rusage usage;
			if(0 == getrusage(RUSAGE_SELF, &usage))
				return usage.ru_maxrss; // bytes
			else
				return 0;
#endif
		}
	}
}