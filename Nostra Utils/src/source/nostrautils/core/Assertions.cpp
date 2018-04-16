#include "nostrautils/core/Assertions.hpp"
#include "nostrautils/core/ErrorHandler.hpp"

#include <iostream>

namespace NOU::NOU_CORE
{
	void assertImpl(boolean b, const char *msg, const char *fnName, sizeType line, const char *file)
	{
		if (!b)
		{
			getErrorHandler().pushError(fnName, line, file, ErrorCodes::ASSERT_ERROR, msg);
		}
	}
}
