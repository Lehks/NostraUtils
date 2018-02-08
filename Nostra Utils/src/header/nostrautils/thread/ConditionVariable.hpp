#ifndef NOU_THREAD_CONDITION_VARIABLE_HPP
#define NOU_THREAD_CONDITION_VARIABLE_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\thread\Lock.hpp"

#include <condition_variable>

namespace NOU::NOU_THREAD
{
	class ConditionVariable
	{
	public:
		using UnderlyingType = std::condition_variable;

	private:
		UnderlyingType m_variable;

	public:
		ConditionVariable();

		void notifyOne();
		void notifyAll();

		void wait(const Lock &lock);

		template<typename PRED>
		void wait(const Lock &lock, PRED predicate);



		ConditionVariable(const ConditionVariable&) = delete;
		ConditionVariable& operator = (const ConditionVariable&) = delete;
	};
}

#endif