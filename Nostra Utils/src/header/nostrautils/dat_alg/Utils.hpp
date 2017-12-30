#ifndef NOU_DAT_ALG_UTILS_HPP
#define NOU_DAT_ALG_UTILS_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"

namespace NOU::NOU_DAT_ALG
{
	template<typename T>
	NOU_FUNC void swap(T *dataone, T *datatwo);

	template<typename T>
	swap(T *dataone, T *datatwo) 
	{
		//TODO move implementation in core utils.
		T tempdata = NOU_CORE::move(*dataone);
		*dataone = NOU_CORE::move(*datatwo);
		*datatwo = NOU_CORE::move(tempdata);
	}
}

#endif
