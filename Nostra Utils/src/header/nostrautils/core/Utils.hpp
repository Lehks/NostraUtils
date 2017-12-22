#ifndef NOU_CORE_UTILS_HPP
#define NOU_CORE_UTILS_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"

namespace NOU::NOU_CORE
{
	/**
	\brief A dummy function that does not do anything, but it forces the generation of a <tt>.lib</tt> file
	       when making a DLL.
	*/
	NOU_FUNC void dummy();

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
	NOU_FUNC typename SelectParameterType_t<T> clamp(SelectParameterType_t<T> &t, SelectParameterType_t<T> &min, SelectParameterType_t<T> &max);

	template<typename T>
	SelectParameterType_t<T> clamp(SelectParameterType_t<T> t, SelectParameterType_t<T> min, SelectParameterType_t<T> max)
	{
		if (t < min)
			return min;
		else if (t > max)
			return max;
		else
			return t;
	}

	template<>
	SelectParameterType_t<int8> clamp<int8>(SelectParameterType_t<int8> t, SelectParameterType_t<int8> min, SelectParameterType_t<int8> max)
	{
		if (t < min)
			return min;
		else if (t > max)
			return max;
		else
			return t;
	}
}

#endif
