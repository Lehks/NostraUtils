#ifndef NOU_CORE_UTILS_HPP
#define NOU_CORE_UTILS_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"

#include <utility>

namespace NOU::NOU_CORE
{
	/**
	\brief A dummy function that does not do anything, but it forces the generation of a <tt>.lib</tt> file
	       when making a DLL.
	*/
	NOU_CLASS void dummy();

	template<typename T>
	NOU_FUNC remove_reference<T>::type&& move(T&& t);

	template<typename T>
	remove_reference<T>::type&& move(T&& t)
	{
		return std::move(t);
	}
}

#endif
