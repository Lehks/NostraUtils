#ifndef	NOU_DAT_ALG_COMPARTOR_HPP
#define	NOU_DAT_ALG_COMPARTOR_HPP

#include "nostrautils\core\StdIncludes.hpp"

namespace NOU::NOU_DAT_ALG
{
	/**
	\brief The result of a comparison produced by a Comparator.

	\details
	The result of a comparison  produced by a Comparator.
	In the following table, there are two values of the same type, a and b that are being compared.
	*/
	enum class CompareResult
	{
		//Important: Do not change the numeric values of the elements, or invert() will break

		/**
		\brief Equivalent to a < b. \"a is SMALLER than b\".
		*/
		SMALLER = -1,
		/**
		\brief Equivalent to a == b. \"a is EQUAL to b\".
		*/
		EQUAL = 0,
		/**
		\brief Equivalent to a > b. \"a is BIGGER than b\".
		*/
		BIGGER = 1
	};

	/**
	\param result The result to be inverted.
	\return       The converted result.
	\brief Inverst a CompareResult.

	\details
	Inverts a CompareResult.
	The resulting values are:\n
	SMALLER => BIGGER\n
	EQUAL   => EQUAL\n
	BIGGER  => SMALLER
	*/
	NOU_FUNC CompareResult invert(CompareResult result);

	/**
	\tparam T The type of the objects that will be compared.

	\brief The type of the function that a comparable function must have.
	*/
	template<typename T>
	using Comparator = CompareResult(*)(const T &a, const T &b);


	/**
	\tparam T The type of the objects that will be compared.
	\param  a The first object.
	\param  b The second object.
	\return The CompareResult that was produced by a and b.
	\brief Compares two ojects in ascending order.

	\details
	This function only works for types that support the operators \> and \<.
	The results look like this:\n
	a >  b => SMALLER\n
	a == b => EQUAL\n
	a <  b => BIGGER
	
	\todo Propperly implement specilisations for char8, char16 and char32 (that take in account other 
	      languages)
	*/
	template<typename T>
	NOU_FUNC CompareResult genericComparator(const T &a, const T &b);

	///\todo comment
	///\cond
	template<>
	NOU_FUNC CompareResult genericComparator<char8>(const char8 &a, const char8 &b);

	template<>
	NOU_FUNC CompareResult genericComparator<char16>(const char16 &a, const char16 &b);

	template<>
	NOU_FUNC CompareResult genericComparator<char32>(const char32 &a, const char32 &b);
	///\endcond

	/**
	\tparam T The type of the objects that will be compared.
	\param  a The first object.
	\param  b The second object.
	\return The CompareResult that was produced by a and b in an inverted order.
	\brief Compares two ojects in descending order.

	\details
	This function only works for types that support the operators \> and \<.
	The results look like this:\n
	a >  b => BIGGER\n
	a == b => EQUAL\n
	a <  b => SMALLER\n
	\n
	This function first calls genericComparator() and then inverts the result
	using invert().
	*/
	template<typename T>
	NOU_FUNC CompareResult genericInvertedComparator(const T &a, const T &b);

	template<typename T>
	CompareResult genericComparator(const T &a, const T &b)
	{
		if (a < b)
			return CompareResult::SMALLER;
		else if (a > b)
			return CompareResult::BIGGER;
		else
			return CompareResult::EQUAL;
	}

	template<typename T>
	CompareResult genericInvertedComparator(const T &a, const T &b)
	{
		return invert(genericComparator(a, b));
	}
}

#endif