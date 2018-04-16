#ifndef	NOU_DAT_ALG_COMPARTOR_HPP
#define	NOU_DAT_ALG_COMPARTOR_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Meta.hpp"

/** \file Comparator.hpp
\author	 Lukas Reichmann
\since   1.0.0
\version 1.0.0
\brief   This file provides mechanics to compare objects without relying on operators.
*/

namespace NOU::NOU_DAT_ALG
{
	/**
	\brief A type that can always be used a a result type for any comparator.
	*/
	using CompareResult = int32;

	/**
	\tparam R     The type of the returned value of the comparison that should be inverted.

	\param result The result to be inverted.
	\return       The converted result.
	\brief Inverts a CompareResult.

	\details
	Inverts a CompareResult.

	The type \p R must be invertible using the - operator.

	The resulting values are:\n
	-1 => 1\n
	0  => 0\n
	1  => -1
	*/
	template<typename R = CompareResult>
	NOU_FUNC constexpr R invert(const R& result);

	/**
	\tparam T The type of the objects that will be compared.
	\tparam R The type of the result. This result must be able to be compared to 0 using the operators \<, \>, <=, >=
	          and ==.

	\brief The type of the function that a comparable function must have.
	*/
	template<typename T, typename R = CompareResult>
	using Comparator = R(*)(const T &a, const T &b);


	/**
	\tparam T The type of the objects that will be compared.
	\param  a The first object.
	\param  b The second object.
	\return The CompareResult that was produced by a and b.
	\brief Compares two objects in ascending order.

	\details
	This function only works for types that support the operators \>, \<, >=, <=, == and -.
	The results look like this:\n
	a >  b => Result is > 0\n
	a == b => Result is == 0\n
	a <  b => Result is < 0
	
	\todo Properly implement specialization for char8, char16 and char32 (that take in account other 
	      languages)
	*/
	template<typename T, typename R = CompareResult>
	NOU_FUNC constexpr R genericComparator(const T &a, const T &b);

	/**
	\tparam T The type of the objects that will be compared.
	\param  a The first object.
	\param  b The second object.
	\return The CompareResult that was produced by a and b in an inverted order.
	\brief Compares two objects in descending order.

	\details
	This function only works for types that support the operators \>, \<, >=, <=, == and -.
	The results look like this:\n
	a >  b => Result is < 0\n
	a == b => Result is == 0\n
	a <  b => Result is > 0\n
	\n
	This function first calls genericComparator() and then inverts the result
	using invert().
	*/
	template<typename T, typename R = CompareResult>
	NOU_FUNC constexpr R genericInvertedComparator(const T &a, const T &b);

	///\todo comment
	///\cond
	template<>
	NOU_FUNC constexpr CompareResult genericComparator<char8, CompareResult>(const char8 &a, const char8 &b);

	template<>
	NOU_FUNC constexpr CompareResult genericComparator<char16, CompareResult>(const char16 &a, const char16 &b);

	template<>
	NOU_FUNC constexpr CompareResult genericComparator<char32, CompareResult>(const char32 &a, const char32 &b);
	///\endcond

	template<typename R>
	constexpr R invert(const R& result)
	{
		return -result;
	}

	template<typename T, typename R>
	constexpr R genericComparator(const T &a, const T &b)
	{
		return static_cast<R>(a - b);
	}

	template<typename T, typename R>
	constexpr R genericInvertedComparator(const T &a, const T &b)
	{
		return invert(genericComparator(a, b));
	}

	template<>
	constexpr CompareResult genericComparator<char8, CompareResult>(const char8 &a, const char8 &b)
	{
		char8 lowerCaseCharA = a >= 'A' && a <= 'Z' ? a + 'a' - 'A' : a;
		char8 lowerCaseCharB = b >= 'A' && b <= 'Z' ? b + 'a' - 'A' : b;

		return genericComparator<int8, CompareResult>(lowerCaseCharA, lowerCaseCharB);
	}

	template<>
	constexpr CompareResult genericComparator<char16, CompareResult>(const char16 &a, const char16 &b)
	{
		char16 lowerCaseCharA = a >= u'A' && a <= u'Z' ? a + u'a' - u'A' : a;
		char16 lowerCaseCharB = b >= u'A' && b <= u'Z' ? b + u'a' - u'A' : b;

		return genericComparator<int16, CompareResult>(lowerCaseCharA, lowerCaseCharB);
	}

	template<>
	constexpr CompareResult genericComparator<char32, CompareResult>(const char32 &a, const char32 &b)
	{
		char32 lowerCaseCharA = a >= U'A' && a <= U'Z' ? a + U'a' - U'A' : a;
		char32 lowerCaseCharB = b >= U'A' && b <= U'Z' ? b + U'a' - U'A' : b;

		return genericComparator<int32, CompareResult>(lowerCaseCharA, lowerCaseCharB);
	}
}

#endif