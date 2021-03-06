#ifndef NOU_DAT_ALG_HASHFUNCTION_HPP
#define	NOU_DAT_ALG_HASHFUNCTION_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/ErrorHandler.hpp"
#include "nostrautils/dat_alg/StringView.hpp"
#include "nostrautils/dat_alg/String.hpp"
#include "nostrautils/dat_alg/Vector.hpp"
#include <limits>
#include <array>


/** \file Hashing.hpp
\author  Leslie Marxen
\since   1.0.0
\version 1.0.1
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
	\param inputObjectCount The amount of objects that \p inputObject points to. Unless \p inputObject is an 
	                       array, this is always 1.

	\brief A Function that hashes an Object for a HashTable.
	*/

	template <typename T>
	constexpr sizeType hashObj(const T* inputObject, sizeType inputObjectCount = 1, sizeType max = static_cast<sizeType>(std::numeric_limits<sizeType>::max())) {
		NOU_COND_PUSH_ERROR((max < 1), NOU_CORE::getErrorHandler(), NOU_CORE::ErrorCodes::INVALID_OBJECT, "Value max cannot be below 1");
		//T* p = &static_cast<T>(inputObject);
		
		const NOU::byte *bytes = reinterpret_cast<const byte*>(inputObject);
		NOU::sizeType h = 0;

		for (NOU::sizeType i = 0; i < inputObjectCount * sizeof(T); i++)
		{
			h += bytes[i];
		}

		return hashValue(h, max);
	};


	/**
	\param str A given stringview that is going to be hashed
	\param max the maximum value the out hashvalue wii have (0 <= output < max)
	\param inputObjectCount The amount of objects that \p str points to. Unless \p str is an 
	                       array, this is always 1.

	\brief A Function that hashes a stringview for a HashTable
	*/

	template<typename T>
	constexpr sizeType hashObj(const NOU_DAT_ALG::StringView<T> *str, sizeType inputObjectCount = 1, sizeType max = static_cast<sizeType>(std::numeric_limits<sizeType>::max()))
	{
		NOU::NOU_DAT_ALG::Vector<T> b;
		NOU::sizeType s = 0;
		T tmp;
		NOU_DAT_ALG::String<T> tmpStr;
		for(sizeType i = 0; i < inputObjectCount; i++)
		{
			s = str[i].size();
			for(NOU::sizeType j = 0; j < s; j++)
			{
				tmpStr = str[i];
				tmp = tmpStr.at(j);
				b.pushBack(tmp);
			}
		}
		return hashObj(reinterpret_cast<byte*>(b.data()), b.size(), max);
	}

	/**
	\param str A given String that is going to be hashed
	\param max the maximum value the out hashvalue wii have (0 <= output < max)
	\param inputObjectCount The amount of objects that \p str points to. Unless \p str is an 
	                       array, this is always 1.

	\brief A Function that hashes a string for a HashTable
	*/

	template<typename T>
	constexpr sizeType hashObj(const NOU_DAT_ALG::String<T> *str, sizeType inputObjectCount = 1, sizeType max = static_cast<sizeType>(std::numeric_limits<sizeType>::max()))
	{
		NOU::NOU_DAT_ALG::Vector<T> b;
		NOU::sizeType s = 0;
		T tmp;
		NOU_DAT_ALG::String<T> tmpStr;
		for(sizeType i = 0; i < inputObjectCount; i++)
		{
			s = str[i].size();
			for(NOU::sizeType j = 0; j < s; j++)
			{
				tmpStr = str[i];
				tmp = tmpStr.at(j);
				b.pushBack(tmp);
			}
		}
		return hashObj(reinterpret_cast<byte*>(b.data()), b.size(), max);
	}


	/**
	\brief a function that rotates the \p input byte by \p rotations rotations
	\param input the byte where the rotations will be performed on
	\param rotations the count of rotations that will be performed on \p input
	\return returns a rotated byte
	*/
	NOU_FUNC byte leftRotation(const byte input, int32 rotations);
}
#endif