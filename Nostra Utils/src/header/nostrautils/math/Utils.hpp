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
	\return \f$sin(a)\f$

	\brief Returns \f$sin(a)\f$.
	*/
	template<typename T>
	T sin(const T &a);

	/**
	\return \f$cos(a)\f$

	\brief Returns \f$cos(a)\f$.
	*/
	template<typename T>
	T cos(const T &a);

	/**
	\return \f$tan(a)\f$

	\brief Returns \f$tan(a)\f$.
	*/
	template<typename T>
	T tan(const T &a);

	/**
	\return \f$asin(a)\f$

	\brief Returns \f$asin(a)\f$.
	*/
	template<typename T>
	T asin(const T &a);

	/**
	\return \f$acos(a)\f$

	\brief Returns \f$acos(a)\f$.
	*/
	template<typename T>
	T acos(const T &a);

	/**
	\return \f$atan(a)\f$

	\brief Returns \f$atan(a)\f$.
	*/
	template<typename T>
	T atan(const T &a);

	/**
	\return \f$exp(a)\f$

	\brief Returns \f$exp(a)\f$.
	*/
	template<typename T>
	T exp(const T &a);

	/**
	\return \f$pow(a)\f$

	\brief Returns \f$pow(a)\f$.
	*/
	template<typename T>
	T pow(const T &a);

	/**
	\return \f$sqrt(a)\f$

	\brief Returns \f$sqrt(a)\f$.
	*/
	template<typename T>
	T sqrt(const T &a);

	/**
	\return \f$cbrt(a)\f$

	\brief Returns \f$cbrt(a)\f$.
	*/
	template<typename T>
	T cbrt(const T &a);

	/**
	\return \f$abs(a)\f$

	\brief Returns \f$abs(a)\f$.
	*/
	template<typename T>
	T abs(const T &a);

	/**
	\return \f$log(a)\f$

	\brief Returns \f$log(a)\f$.
	*/
	template<typename T>
	T log(const T &a);

	/**
	\return \f$ceil(a)\f$

	\brief Returns \f$ceil(a)\f$.
	*/
	template<typename T>
	T ceil(const T &a);

	/**
	\return \f$floor(a)\f$

	\brief Returns \f$floors(a)\f$.
	*/
	template<typename T>
	T floor(const T &a);

	/**
	\return \f$round(a)\f$

	\brief Returns \f$round(a)\f$.
	*/
	template<typename T>
	T round(const T &a);

	/**
	\return \f$fmod(a)\f$

	\brief Returns \f$fmod(a)\f$.
	*/
	template<typename T>
	T fmod(const T &a);



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
}

#endif