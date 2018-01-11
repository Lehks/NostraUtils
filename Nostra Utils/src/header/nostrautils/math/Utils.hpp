#ifndef NOU_MATH_UTILS_HPP
#define NOU_MATH_UTILS_HPP

#include "nostrautils\core\StdIncludes.hpp"

namespace NOU::NOU_MATH
{
	/**
	\param intone		The Integer passed to the function.

	\return				The passed positiv interger.

	\brief Converts the passed integer to a positiv integer and returns it.
	*/
	template<typename IT>
	NOU_FUNC IT abs(const IT &intone);


	template<typename IT>
	IT abs(const IT &intone)
	{
		return intone < 0 ? -intone : intone;
	}
}

#endif 