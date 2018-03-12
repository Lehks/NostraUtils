#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include <iostream>
#include <array>
//#include <limits>


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

	NOU_FUNC NOU::sizeType hashValue(NOU::sizeType value, NOU::sizeType max);

	/**
	\param inputObject the input that will be hashed.
	\param max 0 < output < max. defaults to the biggest number available for ease of use

	\brief A Function to hash an Object for a HashTable
	*/

	template<sizeType N>
	using Hash = std::array<byte, N>;
	using MD5Hash = Hash<16>;

	template <typename T>
	constexpr sizeType hashObj(T* inputObject, sizeType max = static_cast<sizeType>(std::numeric_limits<sizeType>::max())) {
		NOU_COND_PUSH_ERROR((max < 1), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Value max cannot be below 1");
		sizeType h;
		T** address;

		address = &inputObject;
		h = reinterpret_cast<sizeType>(*address);

		return h % max;
	};

	template<typename T>
	NOU_FUNC constexpr sizeType hashObj(NOU_DAT_ALG::StringView<T> *str, sizeType max)
	{
		return hashObj(str->rawStr(), max);
	}

	template<typename T>
	NOU_FUNC constexpr sizeType hashObj(NOU_DAT_ALG::String<T> *str, sizeType max)
	{
		return hashObj(str->rawStr(), max);
	}


	NOU_FUNC MD5Hash md5(NOU::char8 *message);

	NOU_FUNC byte leftRotation(byte input, int32 rotations);
}
#endif