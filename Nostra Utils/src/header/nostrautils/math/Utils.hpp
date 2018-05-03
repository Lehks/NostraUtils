#ifndef NOU_MATH_UTILS_HPP
#define NOU_MATH_UTILS_HPP

#include "nostrautils/core/StdIncludes.hpp"

#include <cmath>

namespace NOU::NOU_MATH
{
	struct Constants
	{
	private:
		Constants();

	public:
		constexpr static float64 PI = 3.14159265358979323846;
		constexpr static float64 E = 2.71828182845904523536;
	};

	template<typename T>
	T NOU_FUNC sin(const T &a);

	template<typename T>
	T NOU_FUNC cos(const T &a);

	template<typename T>
	T NOU_FUNC tan(const T &a);

	template<typename T>
	T NOU_FUNC asin(const T &a);

	template<typename T>
	T NOU_FUNC acos(const T &a);

	template<typename T>
	T NOU_FUNC atan(const T &a);

	template<typename T>
	T NOU_FUNC exp(const T &a);

	template<typename T>
	T NOU_FUNC pow(const T &a);

	template<typename T>
	T NOU_FUNC sqrt(const T &a);

	template<typename T>
	T NOU_FUNC cbrt(const T &a);

	template<typename T>
	T NOU_FUNC abs(const T &a);

	template<typename T>
	T NOU_FUNC log(const T &a);

	template<typename T>
	T NOU_FUNC ceil(const T &a);

	template<typename T>
	T NOU_FUNC floor(const T &a);

	template<typename T>
	T NOU_FUNC round(const T &a);

	template<typename T>
	T NOU_FUNC fmod(const T &a);



	template<typename T>
	T NOU_FUNC sin(const T &a)
	{
		return std::sin(a);
	}

	template<typename T>
	T NOU_FUNC cos(const T &a)
	{
		return std::cos(a);
	}

	template<typename T>
	T NOU_FUNC tan(const T &a)
	{
		return std::tan(a);
	}

	template<typename T>
	T NOU_FUNC asin(const T &a)
	{
		return std::asin(a);
	}

	template<typename T>
	T NOU_FUNC acos(const T &a)
	{
		return std::acos(a);
	}

	template<typename T>
	T NOU_FUNC atan(const T &a)
	{
		return std::atan(a);
	}

	template<typename T>
	T NOU_FUNC exp(const T &a)
	{
		return std::exp(a);
	}

	template<typename T>
	T NOU_FUNC pow(const T &a)
	{
		return std::pow(a);
	}

	template<typename T>
	T NOU_FUNC sqrt(const T &a)
	{
		return std::sqrt(a);
	}

	template<typename T>
	T NOU_FUNC cbrt(const T &a)
	{
		return std::cbrt(a);
	}

	template<typename T>
	T NOU_FUNC abs(const T &a)
	{
		return std::abs(a);
	}

	template<typename T>
	T NOU_FUNC log(const T &a)
	{
		return std::log(a);
	}

	template<typename T>
	T NOU_FUNC ceil(const T &a)
	{
		return std::ceil(a);
	}

	template<typename T>
	T NOU_FUNC floor(const T &a)
	{
		return std::floor(a);
	}

	template<typename T>
	T NOU_FUNC round(const T &a)
	{
		return std::round(a);
	}

	template<typename T>
	T NOU_FUNC fmod(const T &a)
	{
		return std::fmod(a);
	}
}

#endif