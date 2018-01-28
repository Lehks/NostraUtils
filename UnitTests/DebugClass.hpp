#ifndef NOU_UNIT_TESTS_DEBUG_CLASS_HPP
#define NOU_UNIT_TESTS_DEBUG_CLASS_HPP

#include "nostrautils\core\StdIncludes.hpp"

namespace NOU
{
	/**
	\brief A class that is made to test containers.

	\details
	This class counts how many instances of it were constructed and how many were destructed
	(stored in a counter, that can be retrieved via getCounter()). For every construction the
	counter is incremented by one, for every destruction it is decremented by one. As long as 
	all constructed instances were also destructed, this counter should always be 0 after a
	container was in use.

	It also can store an integer value. May be used to compare instances of this class (the
	overloaded compare operators will simply compare that value) and it can also be used to 
	check weather an instance that, e.g. was popped from a container is the correct one by 
	checking the value.
	*/
	class NOU_CLASS DebugClass
	{
	private:
		/**
		\brief The counter of instances.
		*/
		static int64 s_counter;

		/**
		\brief The value stored with each instance.
		*/
		int32 m_value;

	public:
		/**
		\return s_counter

		\brief Returns s_counter.
		*/
		static int64 getCounter();

		/**
		\param value The value that is stored with the instance.

		\brief Constructs a new instance with the passed value.
		*/
		explicit DebugClass(int32 value = 0);
		DebugClass(const DebugClass &other);
		DebugClass(DebugClass &&other);

		~DebugClass();

		/**
		\return m_value

		\brief Returns m_value.
		*/
		int32 get() const;

		/**
		\brief Does nothing, this is just here to avoid deletion of this operator.
		*/
		DebugClass& operator = (const DebugClass &other);

		/**
		\brief Does nothing, this is just here to avoid deletion of this operator.
		*/
		DebugClass& operator = (DebugClass &&other);

		/**
		\param other The instance to compare against.

		\return get() > other.get()

		\brief Checks if get() > other.get().
		*/
		boolean operator > (const DebugClass &other) const;

		/**
		\param other The instance to compare against.

		\return get() < other.get()

		\brief Checks if get() < other.get().
		*/
		boolean operator < (const DebugClass &other) const;

		/**
		\param other The instance to compare against.

		\return get() => other.get()

		\brief Checks if get() => other.get().
		*/
		boolean operator >= (const DebugClass &other) const;

		/**
		\param other The instance to compare against.

		\return get() <= other.get()

		\brief Checks if get() <= other.get().
		*/
		boolean operator <= (const DebugClass &other) const;

		/**
		\param other The instance to compare against.

		\return get() == other.get()

		\brief Checks if get() == other.get().
		*/
		boolean operator == (const DebugClass &other) const;

		/**
		\param other The instance to compare against.

		\return get() != other.get()

		\brief Checks if get() != other.get().
		*/
		boolean operator != (const DebugClass &other) const;
	};
}

#endif
