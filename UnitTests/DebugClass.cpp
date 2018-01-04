#include "DebugClass.hpp"

namespace NOU
{
	int64 DebugClass::s_counter = 0;

	int64 DebugClass::getCounter()
	{
		return s_counter;
	}

	DebugClass::DebugClass()
	{
		s_counter++;
	}

	DebugClass::DebugClass(const DebugClass &other)
	{
		s_counter++;
	}

	DebugClass::DebugClass(DebugClass &&other)
	{
		s_counter++;
	}

	DebugClass::~DebugClass()
	{
		s_counter--;
	}
}
