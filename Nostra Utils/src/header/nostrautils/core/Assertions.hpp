#ifndef NOU_CORE_ASSERTIONS_HPP
#define	NOU_CORE_ASSERTIONS_HPP

#include "nostrautils\core\StdIncludes.hpp"

#ifndef NOU_ASSERT
#    ifdef NOU_DEBUG
#        define NOU_ASSERT(b) NOU::NOU_CORE::assert(b, __LINE__, \
				__FILE__, NOU_STRINGIFY(b));
#    else
#        define NOU_ASSERT
#    endif
#endif

namespace NOU::NOU_CORE
{
	//use char since __FILE__ is defined as such (and expr uses NOU_STRINGIFY)
	NOU_FUNC void assert(boolean b, decltype(__LINE__) lineNr, const char *fName, const char *expr);
}

#endif