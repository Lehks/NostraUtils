#ifndef NOU_DAT_ALG_HASHFUNCTION_HPP
#define	NOU_DAT_ALG_HASHFUNCTION_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/ErrorHandler.hpp"
#include "nostrautils/dat_alg/StringView.hpp"
#include "nostrautils/dat_alg/String.hpp"
#include "nostrautils/dat_alg/Vector.hpp"
#include <array>
//#include <limits>


/** \file Hashing.hpp
\author  Leslie Marxen
\since   0.0.1
\version 0.0.1
\brief   This file provides some Hashing implementations.
*/

namespace NOU::NOU_DAT_ALG
{


	/**
	\param value input value
	\param max the maximum value the out hashvalue wii have (0 <= output < max)

	\return hashed value
	\brief a function that hashes a value between a specific interval.
	*/

	NOU_FUNC NOU::sizeType hashValue(NOU::sizeType value, NOU::sizeType max);

	/**
	\param inputObject the input that will be hashed.
	\param max the maximum value the out hashvalue wii have (0 <= output < max)

	\brief A Function that hashes an Object for a HashTable.
	*/

	template <typename T>
	NOU_FUNC constexpr sizeType hashObj(T* inputObject, sizeType max = static_cast<sizeType>(std::numeric_limits<sizeType>::max())) {
		NOU_COND_PUSH_ERROR((max < 1), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Value max cannot be below 1");
		//T* p = &static_cast<T>(inputObject);
		
		const NOU::byte *bytes = reinterpret_cast<const byte*>(inputObject);
		NOU::sizeType h = 0;

		for (NOU::sizeType i = 0; i < sizeof(T); i++)
		{
			h += bytes[i];
		}

		return hashValue(h, max);
	};


	/**
	\param str A given stringview that is going to be hashed
	\param max the maximum value the out hashvalue wii have (0 <= output < max)

	\brief A Function that hashes a stringview for a HashTable
	*/

	template<typename T>
	NOU_FUNC constexpr sizeType hashObj(NOU_DAT_ALG::StringView<T> *str, sizeType max)
	{
		return hashObj(str->rawStr(), max);
	}

	/**
	\param str A given String that is going to be hashed
	\param max the maximum value the out hashvalue wii have (0 <= output < max)

	\brief A Function that hashes a string for a HashTable
	*/

	template<typename T>
	NOU_FUNC constexpr sizeType hashObj(NOU_DAT_ALG::String<T> *str, sizeType max)
	{
		return hashObj(str->rawStr(), max);
	}

	template<sizeType N>
	using Hash = std::array<byte, N>;
	using MD5Hash = Hash<16>;

	/**
	\param input beginning of a byte array that will be hashed
	\param size length of the given byte array

	\return hash as a 128bit byte array
	\brief Hashes a given input similar to the md5 hash algorithm
	*/

	NOU_FUNC MD5Hash md5(const NOU::byte *input, sizeType size);

	/**
	\param input a StringView that will be hashed

	\return Hash as a 128bit byte Array
	\brief Hashes a given input similar to the md5 hash algorithm
	*/

	template<typename T>
	NOU_FUNC MD5Hash md5(const NOU_DAT_ALG::StringView<T> &str)
	{
		return md5(reinterpret_cast<const byte*>(str.rawStr()), str.size());
	}

	/**
	\param input a string that will be hashed

	\return Hashed input as a 128bit byte array
	\brief Hashes a given input similar to the md5 hash
	*/

	template<typename T>
	NOU_FUNC MD5Hash md5(const NOU_DAT_ALG::String<T> &str)
	{
		return md5(reinterpret_cast<const byte*>(str.rawStr()), str.size());
	}

	/**
	\param input an input byte that will be rotated
	\param rotations how often the byte will be rotated

	\return the byte after the rotation

	\brief Performs a leftRotation to a given input
	*/
	NOU_FUNC byte leftRotation(const byte input, int32 rotations);
}
#endif