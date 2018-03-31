#ifndef NOU_CORE_UTILS_HPP
#define NOU_CORE_UTILS_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Meta.hpp"
#include "nostrautils/dat_alg/Comparator.hpp"

#include <utility>

/**
\file core/Utils.hpp

\author  Lukas Reichmann
\author  Dennis Franz
\version 0.0.1
\since   1.0.0

\brief A file that contains utility functions that are used all over NOU.
*/

/**
\param Type   The type that holds the member \p member.
\param member The member to get the offset of.

\return The offset of \p Member in the class/struct Type.

\brief A macro that returns the offset of the passed member.
*/
#ifndef NOU_OFFSET_OF
#define NOU_OFFSET_OF(Type, member) NOU::sizeType(&((Type*)nullptr)->member)
#endif

namespace NOU::NOU_CORE
{
	/**
	\brief A dummy function that does not do anything, but it forces the generation of a <tt>.lib</tt> file
	       when making a DLL.
	*/
	/**
	\brief "Simple" Function that triggers the move constructor.
	*/
	template<typename T>
	NOU_FUNC typename remove_reference<T>::type&& move(T&& t);
	/**
	\tparam The type of the parameters.

	\param a The first value.
	\param b The second value.
	\return Minimum of the two types.

	\brief A Function to return the minimum of two given types.
	*/
	template<typename T>
	constexpr NOU_FUNC T& min(T &a, T &b); ///\todo min/max: add specializations for primitive types w/o references
	/**
	\tparam The type of the parameters.

	\param a The first value.
	\param b The second value.
	\param comp The comparator that defines the order of the passed parameters.
	\return Minimum of the two types.

	\brief A Function to return the minimum of two given types.
	*/
	template<typename T>
	constexpr NOU_FUNC T& min(T &a, T &b, NOU::NOU_DAT_ALG::Comparator<T> comp); ///\todo min/max: add specializations for primitive types w/o references
	/**
	\tparam The type of the parameters.

	\param a The first value.
	\param b The second value.
	\return Minimum of the two types.

	\brief A Function to return the minimum of two given types.
	*/
	template<typename T>
	constexpr NOU_FUNC const T& min(const T &a,const T &b); ///\todo min/max: add specializations for primitive types w/o references
	/**
	\tparam The type of the parameters.

	\param a The first value.
	\param b The second value.
	\param comp The comparator that defines the order of the passed parameters.
	\return Minimum of the two types.

	\brief A Function to return the minimum of two given types.
	*/
	template<typename T>
	constexpr NOU_FUNC const T& min(const T &a, const T &b, NOU::NOU_DAT_ALG::Comparator<T> comp); ///\todo min/max: add specializations for primitive types w/o references
	/**
	\tparam The type of the parameters.

	\param a The first value.
	\param b The second value.
	\return Maximum of the two types.

	\brief A Function to return the maximum of two given types.
	*/
	template<typename T>
	constexpr NOU_FUNC T& max(T &a, T &b);
	/**
	\tparam The type of the parameters.

	\param a The first value.
	\param b The second value.
	\param comp The comparator that defines the order of the passed parameters.
	\return Maximum of the two types.

	\brief A Function to return the maximum of two given types.
	*/
	template<typename T>
	constexpr NOU_FUNC T& max(T &a, T &b, NOU::NOU_DAT_ALG::Comparator<T> comp);
	/**
	\tparam The type of the parameters.

	\param a The first value.
	\param b The second value.
	\return Maximum of the two types.

	\brief A Function to return the maximum of two given types.
	*/
	template<typename T>
	constexpr NOU_FUNC const T& max(const T &a, const T &b);
	/**
	\tparam The type of the parameters.

	\param a The first value.
	\param b The second value.
	\param comp The comparator that defines the order of the passed parameters.
	\return Maximum of the two types.

	\brief A Function to return the maximum of two given types.
	*/
	template<typename T>
	constexpr NOU_FUNC const T& max(const T &a,const T &b, NOU::NOU_DAT_ALG::Comparator<T> comp);
	/**
	\param arg The argument to forward.

	\return The passed argument as either an l- or r-value.

	\brief Forwards the argument as an l-value if it is an l-value, and as an r-value if it is an r-value.
	*/
	template<typename T>
	constexpr NOU_FUNC auto forward(remove_reference_t<T>& arg);

	/**
	\param arg The argument to forward.

	\return The passed argument as either an l- or r-value.

	\brief Forwards the argument as an l-value if it is an l-value, and as an r-value if it is an r-value.
	*/
	template<typename T>
	constexpr NOU_FUNC auto forward(remove_reference_t<T>&& arg);

	template<typename T>
	typename remove_reference<T>::type&& move(T&& t)
	{
		return std::move(t);
	}

	template<typename T>
	constexpr T& min(T &a, T &b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	constexpr T& min(T &a, T &b, NOU::NOU_DAT_ALG::Comparator<T> comp)
	{
		return (comp(a, b) < 0) ? a : b;
	}

	template<typename T>
	constexpr const T& min(const T &a, const T &b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	constexpr const T & min(const T &a, const T &b, NOU::NOU_DAT_ALG::Comparator<T> comp)
	{
		return (comp(a, b) < a) ? a : b; 
	}


	template<typename T>
	constexpr T& max(T &a, T &b)
	{
		return a > b ? a : b;
	}

	template<typename T>
	constexpr T & max(T &a, T &b, NOU::NOU_DAT_ALG::Comparator<T> comp)
	{
		return (comp(a, b) > 0) ? a : b; 
	}

	template<typename T>
	constexpr const T& max(const T &a, const T &b)
	{
		return a > b ? a : b;
	}

	template<typename T>
	constexpr const T& max(const T &a, const T &b, NOU::NOU_DAT_ALG::Comparator<T> comp)
	{
		return (comp(a, b) > 0) ? a : b;
	}
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
	/**
	\tparam The type of the values to clamp.

	\param t    The value to clamp.
	\param min  The minimum value for \p t.
	\param max  The maximum value for \p t.
	\param comp The comparator that defines the order of the passed parameters.

	\brief Clamps a value.

	\details
	Clamps a value. If t is within the interval \f$\left[min, max\right[\f$, t is returned, if \f$ t < min\f$,
	min is returned and if \f$t > max\f$, max is returned. This function uses the operators > and <.
	*/
	template<typename T>
	constexpr NOU_FUNC const T& clamp(const T &t, const T &min, const T &max, NOU::NOU_DAT_ALG::Comparator<T> comp);

	/**
	\tparam The type of the values to clamp.

	\param t    The value to clamp.
	\param min  The minimum value for \p t.
	\param max  The maximum value for \p t.
	\param comp The comparator that defines the order of the passed parameters.

	\brief Clamps a value.

	\details
	Clamps a value. If t is within the interval \f$\left[min, max\right[\f$, t is returned, if \f$ t < min\f$,
	min is returned and if \f$t > max\f$, max is returned. This function uses the operators > and <.
	*/
	template<typename T>
	constexpr NOU_FUNC T& clamp(T &t, T &min, T &max, NOU::NOU_DAT_ALG::Comparator<T> comp);

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
	constexpr const T& clamp(const T &t, const T &min, const T &max, NOU::NOU_DAT_ALG::Comparator<T> comp)
	{
		if (comp(t, min) < 0)
			return min;
		else if (comp(t, min) > 0)
			return max;
		else
			return t;
	}

	template<typename T>
	constexpr T& clamp(T &t, T &min, T &max, NOU::NOU_DAT_ALG::Comparator<T> comp)
	{
		if (comp(t, min) < 0)
			return min;
		else if (comp(t, min) > 0)
			return max;
		else
			return t;
	}

	template<typename T>
	constexpr NOU_FUNC auto forward(remove_reference_t<T>& arg)
	{
		return std::forward<T>(arg);
	}

	template<typename T>
	constexpr NOU_FUNC auto forward(remove_reference_t<T>&& arg)
	{
		return std::forward<T>(arg);
	}

}

#endif
