#ifndef NOU_CORE_META_HPP
#define NOU_CORE_META_HPP

#include <type_traits>

namespace NOU::NOU_CORE
{
	template<typename T>
	struct remove_reference : public std::remove_reference<T> {};
}

#ifndef NOU_CORE_META_HPP
#define NOU_CORE_META_HPP
#endif

#include "nostrautils\core\StdIncludes.hpp"

#include <type_traits>

namespace NOU::NOU_CORE
{
	/**
	\tparam T The type that will be returned by the function.
	\return The passed type itself.

	\brief A function that returns the type that was passed to it.

	\details
	This function simply returns the type that was passed to it. This function is not useful on itself, but is
	frequently used in combination with inheritance when writing other meta functions.
	*/
	template<typename T>
	struct NOU_CLASS IdentityType
	{
		using type = T;
	};

	/**
	\brief The result of a call to IdentityType.
	*/
	template<typename T>
	using IdentityType_t = typename IdentityType<T>::type;

	/**
	\tparam t The type of the returned value.
	\tparam v The returned value.
	\return The passed value.

	\brief A value constant.

	\details
	This function simply returns the value that was passed to it. This function is not useful on itself, but 
	is frequently used in combination with inheritance when writing other meta functions.
	*/
	template<typename T, T v>
	struct NOU_CLASS Constant
	{
		static constexpr T value = v;
	};

	/**
	\tparam B The value of the boolean.
	\return The passed boolean.

	\brief A boolean constant.
	*/
	template<boolean B>
	using BooleanConstant = Constant<boolean, B>;

	/**
	\brief
	This is a BooleanConstant that is always true.
	*/
	using TrueType = Constant<boolean, true>;

	/**
	\brief
	This is a BooleanConstant that is always false.
	*/
	using FalseType = Constant<boolean, false>;


	/**
	\tparam B  The boolean that determines which type will be choosen.
	\tparam T1 The first type.
	\tparam T2 The second type.
	\return    The choosen type according to B.

	\brief A function that chooses between two types.

	\details
	This functions chooses one of two types. If B is true, the first type will be choosen, otherwise the 
	second one.
	*/
	template<boolean B, typename T1, typename T2>
	struct NOU_CLASS typeIf : IdentityType<T1>{};

	///\cond
	template<typename T1, typename T2>
	struct NOU_CLASS typeIf<false, T1, T2> : IdentityType<T2> {};
	///\endcond

	/**
	\brief The result of a call to typeIf.
	*/
	template<boolean B, typename T1, typename T2>
	using typeIf_t = typename typeIf<B, T1, T2>::type;

	/**
	\tparam T The type to remove const from.
	\return The passed type without const.

	\brief
	This functions removes const from a type.

	\details
	This functions removes const from a type.
	e.g.:
	T	      | Result
	--------- | ------
	int       | int
	const int | int
	*/
	template<typename T>
	struct NOU_CLASS removeConst : IdentityType<T>{};

	///\cond
	template<typename T>
	struct NOU_CLASS removeConst<const T> : IdentityType<T> {};
	///\endcond

	/**
	\brief The result of a call to removeConst.
	*/
	template<typename T>
	using removeConst_t = typename removeConst<T>::type;

	/**
	\tparam The enum the the underlying type should be determined for.

	\brief Determines the underlying type of an enum.
	*/
	template<typename T>
	struct UnderlyingType : std::underlying_type<T> {};

	/**
	\brief The result of a call to UnderlyingType.
	*/
	template<typename T>
	using UnderlyingType_t = typename UnderlyingType<T>::type;
}

#endif