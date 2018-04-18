#ifndef NOU_THREAD_CONDITION_VARIABLE_HPP
#define NOU_THREAD_CONDITION_VARIABLE_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/thread/Lock.hpp"

#include <condition_variable>

/** \file ConditionVariable.hpp
\author	 Lukas Reichmann
\since   1.0.0
\version 1.0.0
\brief   This file provides a condition variable class.

\see nostra::utils::thread::CondtionVariable
*/

namespace NOU::NOU_THREAD
{
	/**
	\brief A condition variable to synchronize threads using a variable. 

	\details
	A condition variable to synchronize threads using a variable. In other words, a condition variable can
	make one or more threads wait until a certain variable has a certain value (and the condition variable is
	notified of a change).
	*/
	class NOU_CLASS ConditionVariable
	{
	public:
		/**
		\brief The internally used type.
		*/
		using UnderlyingType = std::condition_variable;

	private:
		/**
		\brief The internal variable.
		*/
		UnderlyingType m_variable;

	public:
		ConditionVariable() = default;

		/**
		\brief Notifies one variable that is waiting.
		*/
		void notifyOne();

		/**
		\brief Notifies all variables that are waiting.
		*/
		void notifyAll();

		/**
		\param lock The lock that will be used to lock the waiting thread.

		\brief Waits until the variable is notified.
		*/
		void wait(UniqueLock &lock);

		/**
		\tparam PRED The type of the predicate.

		\param lock      The lock that will be used to lock the waiting thread.
		\param predicate The predicate that will be used to evaluate whether the thread can continue or not.
		                 This predicate must have the signature 
						 \code
						 boolean pred()
						 \endcode.

		\brief Waits until the variable is notified and \p predicate returns true.
		*/
		template<typename PRED>
		void wait(UniqueLock &lock, PRED predicate);

		/**
		\brief Not copy construct-able.
		*/
		ConditionVariable(const ConditionVariable&) = delete;

		/**
		\brief Not copy assign-able.
		*/
		ConditionVariable& operator = (const ConditionVariable&) = delete;
	};

	template<typename PRED>
	void ConditionVariable::wait(UniqueLock &lock, PRED predicate)
	{
		m_variable.wait(lock.getUnderlying(), predicate);
	}
}

#endif