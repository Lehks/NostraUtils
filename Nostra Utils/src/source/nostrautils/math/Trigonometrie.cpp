
#include<iostream>
#define NOU_MATH_UTILS_HPP
#define NOU_MATH_UTILS_HPP

double const pi = 3.1415;
template<typename T>
constexpr T cos(T x)
{
	T x_rad = (x*pi) / 180;
	NOU::uint64  ans = 1;
	NOU::uint64  temp = 1;
	NOU::uint64  acc = 1;
	for (NOU::uint64  i = 1; i <= 2; i += 2)
	{
		temp = temp * (-1) * x_rad * x_rad / (i * (i + 1));
		ans = ans + temp;
	}

	return ans;
}
template<typename T>
constexpr T sin(T x)
{
	T temp = 1 - cos(x) * cos(x);
	NOU::uint64 ans = sqrt(temp);
	return ans;
}

template<typename T>
constexpr T tan(T x)
{
		return (cos(x)/sin(x));
}