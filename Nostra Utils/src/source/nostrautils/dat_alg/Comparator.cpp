#include "nostrautils\dat_alg\Comparator.hpp"
#include "nostrautils\core\Meta.hpp"

namespace NOU::NOU_DAT_ALG
{
	CompareResult invert(CompareResult result)
	{
		//cast to underlying type, invert value, cast back to enum
		return static_cast<CompareResult>(-static_cast<NOU_CORE::UnderlyingType_t<CompareResult>>(result));
	}
}