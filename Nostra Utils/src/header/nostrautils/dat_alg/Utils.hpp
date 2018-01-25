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
	void swap(T *dataone, T *datatwo) 
	{
		struct alignas (T)
		{
			byte data[sizeof(T)];
		} tmpdata;

		T *tmp = (T*)tmpdata.data;

		new (tmpdata.data) T(NOU_CORE::move(*dataone));
		dataone->~T();

		new (dataone) T(NOU_CORE::move(*datatwo));
		datatwo->~T();

		new (datatwo) T(NOU_CORE::move(*tmp));
		tmp->~T();
	}

	template<typename CHAR_TYPE>
	constexpr NOU_FUNC sizeType stringlen(const NOU_CORE::removeConst_t<CHAR_TYPE> *str)
	{
		return *str != 0 ? stringlen<CHAR_TYPE>(str + 1) + 1 : 0;
	}
}

#endif
