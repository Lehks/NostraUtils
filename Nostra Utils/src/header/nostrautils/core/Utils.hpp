#ifndef NOU_CORE_UTILS_HPP
#define NOU_CORE_UTILS_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"

#include <utility>

/** \file Utils.hpp
\author  Lukas Reichmann, Dennis Franz
\since   0.0.1
\version 0.0.1
\brief   This file provides usefull utility funcitions.
*/

namespace NOU::NOU_CORE
{
	/**
	\brief A dummy function that does not do anything, but it forces the generation of a <tt>.lib</tt> file
	       when making a DLL.
	*/
	NOU_FUNC void dummy();
	/**
	\brief "Simple" Function that triggers the move constructor.
	*/
	template<typename T>
	NOU_FUNC typename remove_reference<T>::type&& move(T&& t);
	/**
	\param a First Type.
	\param b Second Type.
	\return Minimum of the two types.

	\brief A Function to return the minimum of two given types.
	*/
	template<typename T>
	constexpr NOU_FUNC T& min(T &a, T &b); ///\todo min/max: add specialisations for primitve types w/o references
	/**
	\param a First Type.
	\param b Second Type.
	\return Minimum of the two types.

	\brief A Function to return the minimum of two given types.
	*/
	template<typename T>
	constexpr NOU_FUNC const T& min(const T &a,const T &b); ///\todo min/max: add specialisations for primitve types w/o references
	/**
	\param a First Type.
	\param b Second Type.
	\return Maximum of the two types.

	\brief A Function to return the maximum of two given types.
	*/
	template<typename T>
	constexpr NOU_FUNC T& max(T &a, T &b);
	/**
	\param a First Type.
	\param b Second Type.
	\return Maximum of the two types.

	\brief A Function to return the maximum of two given types.
	*/
	template<typename T>
	constexpr NOU_FUNC const T& max(const T &a,const T &b);



	template<typename T>
	typename remove_reference<T>::type&& move(T&& t)
	{
		return std::move(t);
	}

	template<typename T>
	constexpr T& min(T &a, T &b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	constexpr const T& min(const T &a, const T &b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	constexpr T& max(T &a, T &b)
	{
		return a > b ? a : b;
	}

	template<typename T>
	constexpr const T& max(const T &a, const T &b)
	{
		return a > b ? a : b;
	}
}

#endif
