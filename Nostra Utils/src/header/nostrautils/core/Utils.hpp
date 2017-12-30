#ifndef NOU_CORE_UTILS_HPP
#define NOU_CORE_UTILS_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"

#include <utility>

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
	NOU_FUNC remove_reference<T>::type&& move(T&& t);

	template<typename T>
	remove_reference<T>::type&& move(T&& t)
	{
		return std::move(t);
	}
}

#endif
