#ifndef NOU_CORE_META_HPP
#define NOU_CORE_META_HPP

#include "nostrautils/core/StdIncludes.hpp"

#include <type_traits>
#include <utility>

/** \file Meta.hpp
\author	 Lukas Reichmann
\since   1.0.0
\version 1.0.0
\brief   This file provides a collection of meta functions.
*/

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
	struct IdentityType
	{
		using type = T;
	};

	/**
	\brief The result of a call to IdentityType.
	*/
	template<typename T>
	using IdentityType_t = typename IdentityType<T>::type;

	/**
	\tparam The type to remove the reference from.

	\brief Removes any references from a type.

	\details
	Removes any references from a type.
	E.g.:
	T     | Returned Type
	----- | -------------
	int   | int
	int&  | int
	int&& | int
	*/
	template<typename T>
	struct RemoveReference : public IdentityType<std::remove_reference_t<T>> {};

	/**
	\brief The result of a call to RemoveReference.
	*/
	template<typename T>
	using RemoveReference_t = typename RemoveReference<T>::type;

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
	struct Constant
	{
		/**
		\brief The stored value.
		*/
		static constexpr T value = v;
	};

	template<typename T, T v>
	constexpr T Constant<T, v>::value;

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
	\tparam B  The boolean that determines which type will be chosen.
	\tparam T1 The first type.
	\tparam T2 The second type.
	\return    The chosen type according to B.

	\brief A function that chooses between two types.

	\details
	This functions chooses one of two types. If B is true, the first type will be chosen, otherwise the 
	second one.
	*/
	template<boolean B, typename T1, typename T2>
	struct typeIf : IdentityType<T1>{};

	///\cond
	template<typename T1, typename T2>
	struct typeIf<false, T1, T2> : IdentityType<T2> {};
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
	struct removeConst : IdentityType<T>{};

	///\cond
	template<typename T>
	struct removeConst<const T> : IdentityType<T> {};
	///\endcond

	/**
	\brief The result of a call to removeConst.
	*/
	template<typename T>
	using removeConst_t = typename removeConst<T>::type;

	/**
	\tparam The enum the underlying type should be determined for.

	\brief Determines the underlying type of an enum.
	*/
	template<typename T>
	struct UnderlyingType : std::underlying_type<T> {};

	/**
	\brief The result of a call to UnderlyingType.
	*/
	template<typename T>
	using UnderlyingType_t = typename UnderlyingType<T>::type;

	/**
	\tparam T0 The type to compare the other types to.
	\tparam T1 The second (required) type.
	\tparam T2 Other types that may also be passed and that also need to be the same as \p T0 in order for the
	           function to return TrueType.

	\return TrueType, if all passed types are the same, FalseType if not.

	\brief Checks if one or more types are the same.
	*/
	template<typename T0, typename T1, typename... T2>
	struct AreSame : FalseType {};

	///\cond
	template<typename T0, typename... T2>
	struct AreSame<T0, T0, T2...> : AreSame<T0, T2...> {};

	template<typename T0, typename T1>
	struct AreSame<T0, T1> : FalseType {};

	template<typename T>
	struct AreSame<T, T> : TrueType {};
	///\endcond

	/**
	\tparam T The invocable to check the result of.

	\return The result type of the passed invocable.

	\brief Returns the result type of the passed invocable.

	\warning 
	This feature only exists if the C++ version is >= C++17. If the features exists, NOU_EXISTS_FEATURE_INVOKE_RESULT
	is defined.
	*/
#ifndef NOU_CPP14_COMPATIBILITY
	template<typename T, typename...ARGS>
	struct InvokeResult : IdentityType<std::invoke_result_t<T, ARGS...>> {};
	#define NOU_EXISTS_FEATURE_INVOKE_RESULT
#else
	namespace internal
	{
		template<boolean IS_PTR, typename T, typename...ARGS>
		struct InvokeResultImpl : IdentityType<std::result_of_t<T(ARGS...)>> {};

		template<typename T, typename...ARGS>
		struct InvokeResultImpl<false, T, ARGS...> : IdentityType<std::result_of_t<std::add_pointer_t<T>(ARGS...)>> {};
	}

	template<typename T, typename...ARGS>
	struct InvokeResult : internal::InvokeResultImpl<std::is_pointer<T>::value, T, ARGS...> {};
#endif

	/**
	\brief The result of a call to InvokeResult.

	\warning 
	This feature only exists if the C++ version is >= C++17. If the features exists, NOU_EXISTS_FEATURE_INVOKE_RESULT
	is defined.
	*/
	template<typename T, typename...ARGS>
	using InvokeResult_t = typename InvokeResult<T, ARGS...>::type;

	/**
	\tparam T    The type to check if it is invocable.
	\tparam ARGS The types that \p T needs to be invoked with.

	\return TrueType, if the type \p T is invocable with the parameters \p ARGS, FalseType if not.

	\brief Checks if a type is invocable using the passed parameter types.

	\warning 
	This feature only exists if the C++ version is >= C++17. If the features exists, NOU_EXISTS_FEATURE_IS_INVOCABLE
	is defined.
	*/
#ifndef NOU_CPP14_COMPATIBILITY
	template<typename T, typename... ARGS>
	struct IsInvocable : typeIf_t<std::is_invocable<T, ARGS...>::value, TrueType, FalseType> {};
	#define NOU_EXISTS_FEATURE_IS_INVOCABLE
#endif
	/**
	\tparam R    The return type.
	\tparam T    The type to check if it is invocable.
	\tparam ARGS The types that \p T needs to be invoked with.

	\return TrueType, if the type \p T is invocable with the parameters \p ARGS and it's return type is
	        convertible to \p R, FalseType if not.

	\brief Checks if a type is invocable using the passed parameter types and it's return type is convertible 
	       to \p R.

	\warning 
	This feature only exists if the C++ version is >= C++17. If the features exists, NOU_EXISTS_FEATURE_IS_INVOCABLE_R
	is defined.
	*/
#ifndef NOU_CPP14_COMPATIBILITY
	template<typename R, typename T, typename... ARGS>
	struct IsInvocableR : typeIf_t<std::is_invocable_r<R, T, ARGS...>::value, TrueType, FalseType> {};
	#define NOU_EXISTS_FEATURE_IS_INVOCABLE_R
#endif

	/**
	\tparam T    The type to check.

	\return TrueType, if the type \p T is default constructible, FalseType if not.

	\brief Checks whether a type is default constructible or not.
	*/
	template<typename T>
	struct IsDefaultConstructible : typeIf_t<std::is_default_constructible<T>::value, 
		TrueType, FalseType> {};

	/**
	\tparam B The type to check.
	\tparam D The class that \p B is supposed to derive from.

	\return True, if \p B is a parent of \p D, false if not.

	\brief Checks whether \p B is a base class of \p D.
	*/
	template<typename B, typename D>
	struct IsBaseOf : BooleanConstant<std::is_base_of<B, D>::value> {};
}

#endif