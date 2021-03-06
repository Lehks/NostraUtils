#ifndef NOU_CORE_TIME_HPP
#define NOU_CORE_TIME_HPP
#include "nostrautils/core/StdIncludes.hpp"

/** \file Time.hpp
\author  Leslie Marxen
\version 1.0.1
\since   1.0.0
\brief   This file provides some functionality to work with time values and constants.
*/



namespace NOU::NOU_CORE {

	/**
	\brief returns the UNIX epoch time in ms
	\return returns the Time since the UNIX epoch in milliseconds
	*/

	uint32 NOU_FUNC currentTimeMillis();

	/**
	\brief returns the current time in nanoseconds
	\return returns the current time in nanoseconds
	*/
	uint64 NOU_FUNC currentTimeNanos();
}
#endif