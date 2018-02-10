#ifndef NOU_DAT_ALG_UTILS_HPP
#define NOU_DAT_ALG_UTILS_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Utils.hpp"
#include "nostrautils\core\Meta.hpp"

/** \file Utils.hpp
\author  Dennis Franz
\author	 Lukas Reichmann
\author	 Lukas Gross
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

	/**
	\tparam CHAR_TYPE The type of the character.

	\param str The string to determine the lenght of.

	\return The lenght of \p str.

	\brief Determines the lenght of a string.
	*/
	template<typename CHAR_TYPE>
	constexpr NOU_FUNC sizeType stringlen(const NOU_CORE::removeConst_t<CHAR_TYPE> *str);

	/**
	\tparam The type of the parameters.

	\param t0 A const reference to the first compared parameter.

	\param t1 A const reference to the second compared parameter.

	\param epsilon A const reference to the passed epsilon.

	\return True if the difference between the two parameters is smaller than the epsilon.

	\brief Compares two parameters to a passed epsilon. 
	*/
	template<typename T>
	constexpr NOU_FUNC T epsilonCompare(const T &t0, const T &t1, const T &epsilon);

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
	constexpr NOU_FUNC T epsilonCompare(const T &t0, const T &t1, const T &epsilon)
	{
		T diff = t0 - t1;
		T abs = (diff < 0 ? -diff : diff);
		return !(abs < epsilon) * (diff < 0 ? -1 : 1);
	}
}

#endif
