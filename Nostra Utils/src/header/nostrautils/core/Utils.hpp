#ifndef NOU_CORE_UTILS_HPP
#define NOU_CORE_UTILS_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"

/**
\file core/Utils.hpp

\author  Lukas Reichmann
\author  Dennis Franz
\version 0.0.1
\since   1.0.0

\brief A file that contains utility funtions that are used all over NOU.
*/

namespace NOU::NOU_CORE
{
	/**
	\brief A dummy function that does not do anything, but it forces the generation of a <tt>.lib</tt> file
	       when making a DLL.
	*/
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

	/**
	\param arg The argument to forward.

	\return The passed argument as either an l- or r-value.

	\brief Forwards the argument as an l-value if it is an l-value, and as an r-value if it is an r-value.
	*/
	template<typename T>
	constexpr NOU_FUNC auto forward(remove_reference_t<T>& arg);

	/**
	\param arg The argument to forward.

	\return The passed argument as either an l- or r-value.

	\brief Forwards the argument as an l-value if it is an l-value, and as an r-value if it is an r-value.
	*/
	template<typename T>
	constexpr NOU_FUNC auto forward(remove_reference_t<T>&& arg);

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

	/**
	\tparam The type of the values to clamp.

	\param t   The value to clamp.
	\param min The minimum value for \p t.
	\param max The maximum value for \p t.

	\brief Clamps a value.

	\details
	Clamps a value. If t is within the interval \f$\left[min, max\right[\f$, t is returned, if \f$ t < min\f$,
	min is returned and if \f$t > max\f$, max is returned. This function uses the operators > and <.
	*/
	template<typename T>
	constexpr NOU_FUNC const T& clamp(const T &t, const T &min, const T &max);

	/**
	\tparam The type of the values to clamp.

	\param t   The value to clamp.
	\param min The minimum value for \p t.
	\param max The maximum value for \p t.

	\brief Clamps a value.

	\details
	Clamps a value. If t is within the interval \f$\left[min, max\right[\f$, t is returned, if \f$ t < min\f$,
	min is returned and if \f$t > max\f$, max is returned. This function uses the operators > and <.
	*/
	template<typename T>
	constexpr NOU_FUNC T& clamp(T &t, T &min, T &max);

	template<typename T>
	constexpr const T& clamp(const T &t, const T &min, const T &max)
	{
		if (t < min)
			return min;
		else if (t > max)
			return max;
		else
			return t;
	}

	template<typename T>
	constexpr T& clamp(T &t, T &min, T &max)
	{
		if (t < min)
			return min;
		else if (t > max)
			return max;
		else
			return t;
	}

	template<typename T>
	constexpr NOU_FUNC auto forward(remove_reference_t<T>& arg)
	{
		return std::forward<T>(arg);
	}

	template<typename T>
	constexpr NOU_FUNC auto forward(remove_reference_t<T>&& arg)
	{
		return std::forward<T>(arg);
	}

}

#endif
