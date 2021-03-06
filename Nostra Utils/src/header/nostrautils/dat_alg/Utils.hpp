#ifndef NOU_DAT_ALG_UTILS_HPP
#define NOU_DAT_ALG_UTILS_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Utils.hpp"
#include "nostrautils/core/Meta.hpp"

/** \file dat_alg/Utils.hpp
\author  Dennis Franz
\author	 Lukas Reichmann
\author	 Lukas Gross
\since   1.0.0
\version 1.0.0
\brief   This file provides useful utility functions for dat_alg.
*/

namespace NOU::NOU_DAT_ALG
{
	/**
	\param CLASSNAME The name of the pair class.
	\param DATAONE_NAME The name of the first data field.
	\param DATATWO_NAME The name of the second data field.

	\brief Defines a templated pair class with custom names for the two data fields. There is a default
	implementation called Pair.
	*/
#define NOU_DEFINE_PAIR(CLASSNAME, DATAONE_NAME, DATATWO_NAME)	 \
	template<typename O, typename T>							 \
	struct CLASSNAME									 \
	{															 \
		O	DATAONE_NAME;										 \
		T	DATATWO_NAME;										 \
																 \
		CLASSNAME(const O &DATAONE_NAME, const T &DATATWO_NAME): \
			DATAONE_NAME(DATAONE_NAME),							 \
			DATATWO_NAME(DATATWO_NAME)							 \
		{}														 \
																 \
		CLASSNAME(O&& DATAONE_NAME, T&& DATATWO_NAME) :			 \
			DATAONE_NAME(NOU::NOU_CORE::move(DATAONE_NAME)),	 \
			DATATWO_NAME(NOU::NOU_CORE::move(DATATWO_NAME))		 \
		{}														 \
	};

	NOU_DEFINE_PAIR(Pair, dataOne, dataTwo)

	/**
	\param dataone First Type.
	\param datatwo Second Type.

	\brief A Function to swap the two given types.
	*/
	template<typename T>
	void swap(T *dataone, T *datatwo);

	/**
	\tparam CHAR_TYPE The type of the character.

	\param str The string to determine the length of.

	\return The length of \p str.

	\brief Determines the length of a string.
	*/
	template<typename CHAR_TYPE>
	constexpr sizeType stringlen(const NOU_CORE::RemoveConst_t<CHAR_TYPE> *str);

	/**
	\tparam The type of the parameters.

	\param t0 A const reference to the first compared parameter.

	\param t1 A const reference to the second compared parameter.

	\param epsilon A const reference to the passed epsilon.

	\return True if the difference between the two parameters is smaller or equal to the epsilon.

	\brief Compares two parameters using a passed epsilon. 

	\details 
	Compares two parameters using a passed epsilon. This can be used to properly compare floating point 
	numbers and also works fine with integers if the epsilon is 0 (however, the latter one is usually not
	useful).
	*/
	template<typename T>
	constexpr T epsilonCompare(const T &t0, const T &t1, const T &epsilon);

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
	constexpr sizeType stringlen(const NOU_CORE::RemoveConst_t<CHAR_TYPE> *str)
	{
		return *str != 0 ? stringlen<CHAR_TYPE>(str + 1) + 1 : 0;
	}

	template<typename T>
	constexpr T epsilonCompare(const T &t0, const T &t1, const T &epsilon)
	{
		T diff = t0 - t1;
		T abs = (diff < static_cast<T>(0) ? -diff : diff);
		return !(abs <= epsilon) * (diff < T(0) ? T(-1): T(1));
	}


}

#endif
