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
	constexpr T fak(const T &number)
	{
		T i = 1, fak = 1;

		while (i <= x)
		{
			fak = i * fak;
			i++;
		}
		return fak;
	}

	template<typename T>
	constexpr T sqrt(const T &number)
	{
		T basis;
		NOU::uint64 b = 0.5;
		number = pow(basis, b);
		return nuumber;
	}

	template<typename T>
	constexpr T cbrt(const T &number)
	{
		T basis;
		NOU::uint64 b = 0.33333333333333;
		number = pow(basis, b);
		return number;
	}		
}

#endif
