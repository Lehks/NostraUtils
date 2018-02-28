#ifndef NOU_DAT_ALG_HASHFUNCTION_HPP
#define	NOU_DAT_ALG_HASHFUNCTION_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include <limits>


/** \file Vector.hpp
\author  Leslie Marxen
\since   0.0.1
\version 0.0.1
\brief   This file provides a Hashfunction implementation.
*/

namespace NOU::NOU_DAT_ALG
{


	/**
	\param value input value
	\param max 0 <= output < max

	\return hased value
	\brief a function that hashes a value between a specific interval
	*/

	NOU::sizeType hashValue(NOU::sizeType value, NOU::sizeType max);

	/**
	\param inputObject the input that will be hashed.
	\param max 0 <= output < max.

	\brief A Function to hash an Object for a HashTable
	*/

	template <typename T>
	constexpr sizeType hashObj(T* inputObject, sizeType max) {
		NOU_COND_PUSH_ERROR((max < 1), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Value max cannot be below 1");


		sizeType h;
		T** address;

		address = &inputObject;
		h = reinterpret_cast<sizeType>(*address);

		return hashValue(h, max);
	};

	
}
#endif