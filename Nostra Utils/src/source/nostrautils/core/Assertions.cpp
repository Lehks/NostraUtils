#include "nostrautils/core/Assertions.hpp"
#include "nostrautils/core/ErrorHandler.hpp"

#include <iostream>

#if NOU_OS_LIBRAR == NOU_OS_LIBRARY_POSIX
#include <signal.h>
#endif

namespace NOU::NOU_CORE
{
	AssertionSettings& getAssertionSettings()
	{
		static AssertionSettings settings = 
		{
			true,   //pushErrorOnFail
			false, 	//breakOnFail
			false, 	//printOnFail
			false,	//exitOnFail
			-1,		//exitCode
			nullptr //callbackOnFail
		};

		return settings;
	}

	void debugbreak()
	{
#if NOU_COMPILER == NOU_COMPILER_VISUAL_CPP
		__debugbreak();
#elif NOU_OS_LIBRAR == NOU_OS_LIBRARY_POSIX
		raise(SIGTRAP);
#endif
	}

	void assertImpl(boolean b, const char *msg, const char *fnName, sizeType line, const char *file)
	{
		if (!b)
		{
			if (getAssertionSettings().printOnFail)
				std::cout << msg << std::endl;

			if(getAssertionSettings().pushErrorOnFail)
				getErrorHandler().pushError(fnName, line, file, ErrorCodes::ASSERT_ERROR, msg);

			if (getAssertionSettings().callbackOnFail != nullptr)
				getAssertionSettings().callbackOnFail(msg, fnName, line, file);

			if (getAssertionSettings().breakOnFail)
				debugbreak();

			if (getAssertionSettings().exitOnFail)
				exit(getAssertionSettings().exitCode);
		}
	}
}
