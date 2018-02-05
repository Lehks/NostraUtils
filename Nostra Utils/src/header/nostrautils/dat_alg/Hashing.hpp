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

	\brief A Function to hash an Object for a HashTable
	*/

	template <typename T>
	constexpr uint64 hashObj(T* inputObject, uint64_t max) {
		uint64 h;
		T** address;

		address = &inputObject;
		h = (uint64)*address;

		return h % max;
	};



}