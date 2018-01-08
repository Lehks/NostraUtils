#ifndef NOU_CORE_ASSERTIONS_HPP
#define	NOU_CORE_ASSERTIONS_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\ErrorHandler.hpp"

#ifndef NOU_ASSERT
#    ifdef NOU_DEBUG
#        define NOU_ASSERT(b) NOU::NOU_CORE::assert(b, "Assertion failed: " NOU_STRINGIFY(b) "; Function: "\
				 NOU_FUNC_NAME "; Line: " NOU_LINE_STRING "; File: " __FILE__, NOU_FUNC_NAME, __LINE__, \
				__FILE__)
#    else
#        define NOU_ASSERT
#    endif
#endif

namespace NOU::NOU_CORE
{
	NOU_FUNC void assert(boolean b, const char *msg, const char *fnName, sizeType line, const char *file);
}

#endif