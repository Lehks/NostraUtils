#ifndef NOU_CORE_META_HPP
#define NOU_CORE_META_HPP

#include "nostrautils\core\StdIncludes.hpp"

namespace NOU::NOU_CORE
{
	template<typename T>
	struct NOU_CLASS IdentityType
	{
		using type = T;
	};

	template<typename T>
	using IdentityType_t = typename IdentityType<T>::type;

	template<typename T>
	struct SelectParameterType : IdentityType<T&> {};

	template<>
	struct SelectParameterType<int8> : IdentityType<int8> {};

	template<typename T>
	using SelectParameterType_t = typename SelectParameterType<T>::type;
}

#endif