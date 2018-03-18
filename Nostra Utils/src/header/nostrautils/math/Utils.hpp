#ifndef NOU_MATH_UTILS_HPP
#define NOU_MATH_UTILS_HPP

#include "nostrautils\core\StdIncludes.hpp"

#include <cmath>

namespace NOU::NOU_MATH
{
	template<typename T>
	constexpr T pow(T A, NOU::uint64 B)
	{

		T basis = A;
		NOU::uint64 i = 1;

		while (i < B)
		{
			basis = basis * A;
			i++;
		}
		return basis;
	}

	template<typename T>
	constexpr T sqrt(const T &number)
	{
		return ::sqrt<T>(number);
	}

	template<typename T>
	constexpr T cbrt(const T &number)
	{
		return ::cbrt<T>(number);
	}

	template<typename T>
	constexpr float root(float radikant, float wurzel)
	{
		float h;
		float ret;

		if (radikant < 9)
			ret = radikant / (wurzel + 1);

		if ((radikant > 9) && (radikant < 50))
			ret = radikant / (wurzel + 6);

		if (radikant > 50)
			h = 1e-04;

		return ret;
	}
}

#endif