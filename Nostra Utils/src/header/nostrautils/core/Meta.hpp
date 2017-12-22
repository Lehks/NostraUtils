#ifndef NOU_CORE_META_HPP
#define NOU_CORE_META_HPP

#include <type_traits>

namespace NOU::NOU_CORE
{
	template<typename T>
	struct remove_reference : public std::remove_reference<T> {};
}

#endif