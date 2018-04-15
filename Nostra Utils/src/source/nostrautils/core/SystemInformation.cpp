#include "nostrautils/core/SystemInformation.hpp"

#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
#include <Windows.h>
#include <Psapi.h>
#elif NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
#include <stdio.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <stdlib.h>
#include <unistd.h>
#endif

namespace NOU { namespace NOU_CORE
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
#   if NOU_OS == NOU_OS_LINUX
		//	long currentUsage = 0;
		//	FILE* fp = nullptr;
		//
		//	if ((fp = fopen("/proc/self/statm", "r")) == nullptr)
		//		return uint64(0); //Can not open /proc/self/statm
		//
		//	if (fscanf(fp, "%*s%ld", &currentUsage) != 1)
		//	{
		//		fclose(fp);
		//		return uint64(0);
		//	}
		//
		//	fclose(fp);
		//
		//	//return (uint64)rss * (uint64)sysconf(_SC_PAGESIZE); ///TODO find rss include file
			return 0;
#   elif NOU_OS == NOU_OS_MAC
			///\todo Verify.
			struct mach_task_basic_info info;
			mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;

			if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO,
				(task_info_t)&info, &infoCount) != KERN_SUCCESS)
			{
				return uint64(0); //Error reading
			}

			return uint64(info.resident_size);
#	else  //No generic implementation for Unix.
			return uint64(0);
#   endif
#endif
		}
	}
} //Namespace NOU_DAT_ALG
} //Namespace NOU