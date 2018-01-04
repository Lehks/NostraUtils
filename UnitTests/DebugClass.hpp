#ifndef NOU_UNIT_TESTS_DEBUG_CLASS_HPP
#define NOU_UNIT_TESTS_DEBUG_CLASS_HPP

#include "nostrautils\core\StdIncludes.hpp"

namespace NOU
{
	class NOU_CLASS DebugClass
	{
	private:
		static int64 s_counter;

	public:
		static int64 getCounter();

		DebugClass();
		DebugClass(const DebugClass &other);
		DebugClass(DebugClass &&other);

		~DebugClass();

		DebugClass& operator = (const DebugClass &other);
		DebugClass& operator = (DebugClass &&other);
	};
}

#endif
