#ifndef NOU_CORE_TIME_HPP
#define NOU_CORE_TIME_HPP
#include "nostrautils/core/StdIncludes.hpp"

/** \file Vector.hpp
\author  Leslie Marxen
\brief   This file provides some functionallity to work with time values and constants.
*/



namespace NOU::NOU_CORE {

	/**
	\brief returns the UNIX epoch time in ms
	\return returns the Time since the UNIX epoch in milliseconds
	*/

	uint32 NOU_FUNC currentTimeMillis();
}
#endif