 #ifndef NOU_MATH_UTILS_HPP
#define NOU_MATH_UTILS_HPP

#include "nostrautils/core/StdIncludes.hpp"

#include <cmath>

/** \file math/Matrix.hpp
\author	 Lukas Reichmann
\since   1.0.0
\version 1.0.0
\brief   This file provides a collection of math related functions and constants.
*/

namespace NOU::NOU_MATH
{
	/**
	\brief A class that provides a collection math constants.
	*/
	struct Constants
	{
	private:
		Constants();

	public:
		/**
		\brief A constant for PI.
		*/
		constexpr static float64 PI = 3.14159265358979323846;

		/**
		\brief A constant for E.
		*/
		constexpr static float64 E = 2.71828182845904523536;
	};

	/**
	\return \f$std::sin(a)\f$

	\brief Returns \f$std::sin(a)\f$.
	*/
	template<typename T>
	T sin(const T &a);

	/**
	\return \f$std::cos(a)\f$

	\brief Returns \f$std::cos(a)\f$.
	*/
	template<typename T>
	T cos(const T &a);

	/**
	\return \f$std::tan(a)\f$

	\brief Returns \f$std::tan(a)\f$.
	*/
	template<typename T>
	T tan(const T &a);

	/**
	\return \f$std::asin(a)\f$

	\brief Returns \f$std::asin(a)\f$.
	*/
	template<typename T>
	T asin(const T &a);

	/**
	\return \f$std::acos(a)\f$

	\brief Returns \f$std::acos(a)\f$.
	*/
	template<typename T>
	T acos(const T &a);

	/**
	\return \f$std::atan(a)\f$

	\brief Returns \f$std::atan(a)\f$.
	*/
	template<typename T>
	T atan(const T &a);

	/**
	\return \f$std::exp(a)\f$

	\brief Returns \f$std::exp(a)\f$.
	*/
	template<typename T>
	T exp(const T &a);

	/**
	\return \f$std::pow(a)\f$

	\brief Returns \f$std::pow(a)\f$.
	*/
	template<typename T>
	T pow(const T &a);

	/**
	\return \f$std::sqrt(a)\f$

	\brief Returns \f$std::sqrt(a)\f$.
	*/
	template<typename T>
	T sqrt(const T &a);

	/**
	\return \f$std::cbrt(a)\f$

	\brief Returns \f$std::cbrt(a)\f$.
	*/
	template<typename T>
	T cbrt(const T &a);

	/**
	\return \f$std::abs(a)\f$

	\brief Returns \f$std::abs(a)\f$.
	*/
	template<typename T>
	T abs(const T &a);

	/**
	\return \f$std::log(a)\f$

	\brief Returns \f$std::log(a)\f$.
	*/
	template<typename T>
	T log(const T &a);

	/**
	\return \f$std::ceil(a)\f$

	\brief Returns \f$std::ceil(a)\f$.
	*/
	template<typename T>
	T ceil(const T &a);

	/**
	\return \f$std::floor(a)\f$

	\brief Returns \f$std::floors(a)\f$.
	*/
	template<typename T>
	T floor(const T &a);

	/**
	\return \f$std::round(a)\f$

	\brief Returns \f$std::round(a)\f$.
	*/
	template<typename T>
	T round(const T &a);

	/**
	\return \f$std::fmod(a)\f$

	\brief Returns \f$std::fmod(a)\f$.
	*/
	template<typename T>
	T fmod(const T &a);

	/**
	\param a The radians value to convert.

	\return The passed parameter in degrees.

	\brief Converts from radians to degrees.
	*/
	template<typename T>
	T deg(const T &a);

	/**
	\param a The degrees value to convert.

	\return The passed parameter in radians.

	\brief Converts from degrees to radians.
	*/
	template<typename T>
	T rad(const T &a);



	template<typename T>
	T sin(const T &a)
	{
		return std::sin(a);
	}

	template<typename T>
	T cos(const T &a)
	{
		return std::cos(a);
	}

	template<typename T>
	T tan(const T &a)
	{
		return std::tan(a);
	}

	template<typename T>
	T asin(const T &a)
	{
		return std::asin(a);
	}

	template<typename T>
	T acos(const T &a)
	{
		return std::acos(a);
	}

	template<typename T>
	T atan(const T &a)
	{
		return std::atan(a);
	}

	template<typename T>
	T exp(const T &a)
	{
		return std::exp(a);
	}

	template<typename T>
	T pow(const T &a)
	{
		return std::pow(a);
	}

	template<typename T>
	T sqrt(const T &a)
	{
		return std::sqrt(a);
	}

	template<typename T>
	T cbrt(const T &a)
	{
		return std::cbrt(a);
	}

	template<typename T>
	T abs(const T &a)
	{
		return std::abs(a);
	}

	template<typename T>
	T log(const T &a)
	{
		return std::log(a);
	}

	template<typename T>
	T ceil(const T &a)
	{
		return std::ceil(a);
	}

	template<typename T>
	T floor(const T &a)
	{
		return std::floor(a);
	}

	template<typename T>
	T round(const T &a)
	{
		return std::round(a);
	}

	template<typename T>
	T fmod(const T &a)
	{
		return std::fmod(a);
	}

	template<typename T>
	T deg(const T &a)
	{
		return a * T(57.295779513); //1 radian = 57.295779513 degrees
	}

	template<typename T>
	T rad(const T &a)
	{
		return a * T(0.01745329252); //1 degree = 0.01745329252 radians
	}
}

#endif