#ifndef	NOU_THREAD_TASK_HPP
#define	NOU_THREAD_TASK_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"
#include "nostrautils\dat_alg\Uninitialized.hpp"
#include "nostrautils\mem_mngt\Pointer.hpp"

#include <tuple>
#include <type_traits>

/**
\file nostrautils/thread/Task.hpp

\author  Lukas Reichmann
\version 0.0.1
\since   1.0.0

\brief This file contains the task class(es).

\see nostra::utils::thread::AbstractTask
\see nostra::utils::thread::Task
*/

namespace NOU::NOU_THREAD
{
	///\todo make work w/ lambdas
	/**
	\brief A parent class of the Task class that does not take or need any template types. This abstract task
	however, can only execute the stored functionality and not access the results.

	\details
	A parent class of the Task class that does not take or need any template types. This abstract task 
	however, can only execute the stored functionality and not access the results.

	By default, every task can only be executed once. If a task should be executed multiple times, it needs to
	be reset first.
	*/
	class NOU_CLASS AbstractTask
	{
	public:
		/**
		\brief The different states of a task.
		*/
		enum class State
		{
			/**
			\brief The task has not been started yet, or it has been reset.
			*/
			NOT_STARTED,

			/**
			\brief The task is currently being executed.
			*/
			RUNNING,

			/**
			\brief The task is done running.
			*/
			DONE
		};

	protected:
		/**
		\brief The current state.
		*/
		State m_state;

	public:
		virtual ~AbstractTask() = default;

		/**
		\return True, if the functionality was actually executed, false if not.

		\brief Executes the stored functionality, if it was not executed yet.
		*/
		virtual boolean execute() = 0;

		/**
		\brief Resets the task from the DONE state to NOT_STARTED. If the task is currently being executed,
		this will do nothing.
		*/
		virtual void reset();

		/**
		\return The current state.
		
		\brief Returns the current state.
		*/
		virtual State getState() const;
	};

	/**
	\tparam R    The return type of the invocable and the task in general.
	\tparam I    The type of the invocable.
	\tparam ARGS The types of the arguments that will be passed to the invocable.

	\brief An implementation of AbstractTask that uses type parameters. The type parameters must define an
	       invocable as defined by nostra::utils::core::IsInvocableR.
	*/
	template<typename R, typename I, typename... ARGS>
	class NOU_CLASS Task final : public AbstractTask
	{
		static_assert(NOU_CORE::IsInvocableR<R, I, ARGS...>::value);

	public:
		/**
		\brief The return type of the task.
		*/
		using ReturnType = R;

		/**
		\brief The type of the invocable.
		*/
		using InvocableType = I;

	private:
		/**
		\brief The arguments that will be passed to the invocable.
		*/
		std::tuple<ARGS...> m_args;

		/**
		\brief The invocable.
		*/
		InvocableType m_invocable;

		/**
		\brief The result that was produced by the invocable.
		*/
		NOU_DAT_ALG::Uninitialized<ReturnType> m_result;

	public:
		/**
		\param invocable The invocable that will be executed.
		\param args      The arguments that will be passed to the invocable.

		\brief Constructs a new Task that will execute the passed invocable using the passed arguments.
		*/
		explicit Task(InvocableType &&invocable, ARGS&&... args);

		/**
		\return True, if the invocable was actually executed, false if not.

		\brief Executes the passed invocable, but only if the state is AbstractTask::State::NOT_STARTED.
		*/
		virtual boolean execute() override;

		/**
		\return The result of the invocable.

		\brief Returns the result of the invocable. 

		\details
		Returns the result of the invocable. This result is only valid if execute() has at least been called 
		once. If the result is not valid, ErrorCodes::INVALID_OBJECT will be pushed to the error handler.
		*/
		ReturnType& getResult();

		/**
		\return The result of the invocable.

		\brief Returns the result of the invocable.

		\details
		Returns the result of the invocable. This result is only valid if execute() has at least been called
		once. If the result is not valid, ErrorCodes::INVALID_OBJECT will be pushed to the error handler.
		*/
		const ReturnType& getResult() const;
	};

	///\cond
	//A specialization for the task when the return type is void.
	template<typename I, typename... ARGS>
	class NOU_CLASS Task<void, I, ARGS...> final : public AbstractTask
	{
		static_assert(NOU_CORE::IsInvocableR<void, I, ARGS...>::value);

	public:
		using ReturnType = void;
		using InvocableType = I;

	private:
		std::tuple<ARGS...> m_args;
		InvocableType m_invocable;

	public:
		explicit Task(InvocableType&& invocable, ARGS&&... args);

		virtual boolean execute() override;

		ReturnType getResult() const;
	};
	///\endcond

	/**
	\tparam I    The invocable type.
	\tparam ARGS The argument types.

	\param invocable The invocable.
	\param args      The arguments.

	\brief This convenience function constructs a task from a function (or function like types, like 
	       functors).
	*/
	template<typename I, typename... ARGS>
	NOU_FUNC Task<NOU_CORE::InvokeResult_t<I, NOU_CORE::remove_reference_t<ARGS>...>, I,
		NOU_CORE::remove_reference_t<ARGS>...> makeTask(I&& invocable, ARGS&&... args);

	/**
	\tparam T    The type that \p I is a member function of.
	\tparam I    The invocable type.
	\tparam ARGS The argument types.

	\param obj       The object that \p invocable will be called on.
	\param invocable The invocable.
	\param args      The arguments.

	\brief This convenience function constructs a task from a member function and an object that function
	       will be called on.
	*/
	template<typename T, typename I, typename... ARGS>
	NOU_FUNC Task<NOU_CORE::InvokeResult_t<I, T, NOU_CORE::remove_reference_t<ARGS>...>, I, T, 
		NOU_CORE::remove_reference_t<ARGS>...> makeMemFuncTask(T&& obj, I&& invocable, ARGS&&...args);

//	template<typename I, typename... ARGS>
//	NOU_FUNC Task makeTaskFromInvocable(I &&invocable, ARGS&&... args);
//
//	template<typename T, typename I, typename... ARGS>
//	NOU_FUNC Task makeTaskFromMemberFunction(T &&t, I invocable, ARGS&&... args);



	template<typename R, typename I, typename... ARGS>
	Task<R, I, ARGS...>::Task(InvocableType&& invocable, ARGS&&... args) :
		m_invocable(NOU_CORE::forward<InvocableType>(invocable)),
		m_args(NOU_CORE::forward<ARGS>(args)...)
	{}

	template<typename R, typename I, typename... ARGS>
	boolean Task<R, I, ARGS...>::execute()
	{
		if (m_state == State::NOT_STARTED)
		{
			m_state = State::RUNNING;
			m_result = std::apply(m_invocable, m_args);
			m_state = State::DONE;
			return true;
		}

		return false;
	}

	template<typename R, typename I, typename... ARGS>
	typename Task<R, I, ARGS...>::ReturnType& Task<R, I, ARGS...>::getResult()
	{
		return *m_result;
	}

	template<typename R, typename I, typename... ARGS>
	const typename Task<R, I, ARGS...>::ReturnType& Task<R, I, ARGS...>::getResult() const
	{
		return *m_result;
	}



	template<typename I, typename... ARGS>
	Task<void, I, ARGS...>::Task(InvocableType&& invocable, ARGS&&... args) :
		m_invocable(NOU_CORE::forward<InvocableType>(invocable)),
		m_args(NOU_CORE::forward<ARGS>(args)...)
	{}

	template<typename I, typename... ARGS>
	boolean Task<void, I, ARGS...>::execute()
	{
		if (m_state == State::NOT_STARTED)
		{
			m_state = State::RUNNING;
			std::apply(m_invocable, m_args);
			m_state = State::DONE;
			return true;
		}

		return false;
	}

	template<typename I, typename... ARGS>
	typename Task<void, I, ARGS...>::ReturnType Task<void, I, ARGS...>::getResult() const
	{}



	template<typename I, typename... ARGS>
	Task<NOU_CORE::InvokeResult_t<I, NOU_CORE::remove_reference_t<ARGS>...>, I, 
		NOU_CORE::remove_reference_t<ARGS>...> makeTask(I&& invocable, ARGS&&... args)
	{
		using TaskType = Task<NOU_CORE::InvokeResult_t<I, NOU_CORE::remove_reference_t<ARGS>...>, I,
			NOU_CORE::remove_reference_t<ARGS>...>;

		return TaskType(NOU_CORE::forward<typename TaskType::InvocableType>(invocable),
			NOU_CORE::forward<NOU_CORE::remove_reference_t<ARGS>>(args)...);
	}

	template<typename T, typename I, typename... ARGS>
	NOU_FUNC Task<NOU_CORE::InvokeResult_t<I, T, NOU_CORE::remove_reference_t<ARGS>...>, I, T,
		NOU_CORE::remove_reference_t<ARGS>...> makeMemFuncTask(T&& obj, I&& invocable, ARGS&&...args)
	{
		return makeTask(NOU_CORE::forward<I>(invocable), NOU_CORE::forward<T>(obj), 
			NOU_CORE::forward<ARGS>(args)...);
	}

}

#endif