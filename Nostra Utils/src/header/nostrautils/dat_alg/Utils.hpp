#ifndef NOU_DAT_ALG_UTILS_HPP
#define NOU_DAT_ALG_UTILS_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\core\Meta.hpp"

/** \file Utils.hpp
\author  Dennis Franz
\since   0.0.1
\version 0.0.1
\brief   This file provides usefull utility funcitions for dat_alg.
*/

namespace NOU::NOU_DAT_ALG
{
	template<typename O, typename T>
	struct NOU_CLASS Pair
	{
		O	dataOne;
		T	dataTwo;
		Pair<O,T>(const T& dataOne, const O& dataTwo);
	};
	/**
	\param dataone First Type.
	\param datatwo Second Type.

	\brief A Function to swap the two given types.
	*/
	template<typename T>
	NOU_FUNC void swap(T *dataone, T *datatwo);

	/**
	\tparam CHAR_TYPE The type of the character.

	\param str The string to determine the lenght of.

	\return The lenght of \p str.

	\brief Determines the lenght of a string.
	*/
	template<typename CHAR_TYPE>
	constexpr NOU_FUNC sizeType stringlen(const NOU_CORE::removeConst_t<CHAR_TYPE> *str);

	template<typename T>
	constexpr NOU_FUNC int32 epsilonCompare(const T &t0, const T &t1, const T &epsilon);

	template<typename T>
	void swap(T *dataone, T *datatwo) 
	{
		T tempdata = NOU_CORE::move(*dataone);
		*dataone = NOU_CORE::move(*datatwo);
		*datatwo = NOU_CORE::move(tempdata);
	}

	template<typename CHAR_TYPE>
	constexpr NOU_FUNC sizeType stringlen(const NOU_CORE::removeConst_t<CHAR_TYPE> *str)
	{
		return *str != 0 ? stringlen<CHAR_TYPE>(str + 1) + 1 : 0;
	}

	template<typename T>
	constexpr NOU_FUNC int32 epsilonCompare(const T &t0, const T &t1, const T &epsilon)
	{
		T diff = t0 - t1;
		T abs = (diff < 0 ? -diff : diff);
		return !(abs < epsilon) * (diff < 0 ? -1 : 1);
	}


	template<typename O, typename T>
	Pair<O, T>::Pair(const T& dataOne, const O& dataTwo) :
		dataOne(dataOne),
		dataTwo(dataTwo)
	{}
}

#endif
