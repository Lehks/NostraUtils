#ifndef NOU_DAT_ALG_UTILS_HPP
#define NOU_DAT_ALG_UTILS_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"

/** \file Utils.hpp
\author  Dennis Franz
\since   0.0.1
\version 0.0.1
\brief   This file provides usefull utility funcitions for dat_alg.
*/

namespace NOU::NOU_DAT_ALG
{
	/**
	\param dataone First Type.
	\param datatwo Second Type.

	\brief A Function to swap the two given types.
	*/
	template<typename T>
	NOU_FUNC void swap(T *dataone, T *datatwo);


	template<typename T>
	swap(T *dataone, T *datatwo) 
	{
		T tempdata = NOU_CORE::move(*dataone);
		*dataone = NOU_CORE::move(*datatwo);
		*datatwo = NOU_CORE::move(tempdata);
	}
}

#endif
