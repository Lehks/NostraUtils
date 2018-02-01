#include "nostrautils\core\StdIncludes.hpp";


/** \file Vector.hpp
\author  Leslie Marxen
\since   0.0.1
\version 0.0.1
\brief   This file provides a Hashfunction implementation.
*/

namespace NOU::NOU_DAT_ALG
{

	/**
	\param inputObject the input that will be hashed.
	\param max 0 <= output < max.

	\brief A Function to swap the two given types.
	*/

	template <typename T>
	uint64_t hashObj(T* inputObject, uint64_t max) {
		uint64_t h;
		T** address;

		address = &inputObject;
		h = (uint64_t)*address;

		return h % max;
	};



}