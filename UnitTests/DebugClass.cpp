#include "DebugClass.hpp"

namespace NOU
{
	int64 DebugClass::s_counter = 0;

	int64 DebugClass::getCounter()
	{
		return s_counter;
	}

	DebugClass::DebugClass(int32 value) :
		m_value(value)
	{
		s_counter++;
	}

	DebugClass::DebugClass(const DebugClass &other) :
		m_value(other.get())
	{
		s_counter++;
	}

	DebugClass::DebugClass(DebugClass &&other) :
		m_value(other.get())
	{
		s_counter++;
	}

	DebugClass::~DebugClass()
	{
		s_counter--;
	}

	int32 DebugClass::get() const
	{
		return m_value;
	}

	DebugClass& DebugClass::operator = (const DebugClass &other)
	{
		return *this;
	}

	DebugClass& DebugClass::operator = (DebugClass &&other)
	{
		return *this;
	}

	boolean DebugClass::operator > (const DebugClass &other) const
	{
		return get() > other.get();
	}

	boolean DebugClass::operator < (const DebugClass &other) const
	{
		return get() < other.get();
	}

	boolean DebugClass::operator >= (const DebugClass &other) const
	{
		return get() >= other.get();
	}

	boolean DebugClass::operator <= (const DebugClass &other) const
	{
		return get() <= other.get();
	}

	boolean DebugClass::operator == (const DebugClass &other) const
	{
		return get() == other.get();
	}

	boolean DebugClass::operator != (const DebugClass &other) const
	{
		return get() != other.get();
	}
}
