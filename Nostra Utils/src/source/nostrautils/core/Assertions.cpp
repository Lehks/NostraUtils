#include "nostrautils\core\Assertions.hpp"

#include <iostream>

namespace NOU::NOU_CORE
{
	void assert(boolean b, decltype(__LINE__) lineNr, const char *fName, const char *expr)
	{
		///\todo implement this

		if (!b)
		{
			std::cerr << "(" << expr << "): Assertion failed in File \""
				<< fName << "\" at line " << lineNr << "." << std::endl;
		}
	}
}