#include "nostrautils\math\Utils.hpp"

namespace NOU::NOU_MATH
{
	template<typename IT>
	IT abs(const IT &intone)
	{
		if (intone < 0) {
			return intone * (-1);
		}
		return intone;
	}
}