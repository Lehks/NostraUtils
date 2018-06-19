#ifndef	NOU_THREAD_TASK_HPP
#define	NOU_THREAD_TASK_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Meta.hpp"
#include "nostrautils/dat_alg/Uninitialized.hpp"
#include "nostrautils/mem_mngt/Pointer.hpp"

#include <tuple>
#include <type_traits>

/**
\file thread/Task.hpp

\author  Lukas Reichmann
\version 1.0.0
\since   1.0.0

\brief This file contains the task class(es).

\see nostra::utils::thread::AbstractTask
\see nostra::utils::thread::Task
*/

namespace NOU::NOU_THREAD
{
	namespace internal
	{
		///\todo make work w/ lambdas
		/**
		\brief A parent class of the Task class that does not take or need any template types. This abstract 
		task however, can only execute the stored functionality and not access the results.

		\details
		A parent class of the Task class that does not take or need any template types. This abstract task
		however, can only execute the stored functionality and not access the results.
		*/
		class AbstractTask
		{
		public:
			virtual ~AbstractTask() = default;

			/**
			\return True, if the functionality was actually executed, false if not.

			\brief Executes the stored functionality, if it was not executed yet.
			*/
			virtual void execute() = 0;
		};
	}

	/**
	\tparam R    The return type of the invocable and the task in general.
	\tparam I    The type of the invocable.
	\tparam ARGS The types of the arguments that will be passed to the invocable.

	\brief A task is a class that is a combination of an invocable and the data that is required to execute
	       that invocable.

	\details
	A task is a class that is a combination of an invocable and the data that is required to execute that 
	invocable.

	This class is used by the thread manager to execute functionality in a different thread (Tasks on 
	themselves are not solely suited for multi-threading and do not supply thread safety mechanisms on their
	own).

	Tasks do not allow to store object references and NOU does not provide reference wrappers (like 
	std::reference_wrapper) on its own. Instead, pointers should be used instead of references.
	
	\note 
	\p I must be an invocable according to nostra::utils::core::IsInvocableR<R, I, ARGS...>.
	*/
	template<typename R, typename I, typename... ARGS>
	class Task final : public internal::AbstractTask
	{
#ifdef NOU_EXISTS_FEATURE_IS_INVOCABLE_R
		static_assert(NOU_CORE::IsInvocableR<R, I, ARGS...>::value);
#endif

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
		//RemoveConst b/c otherwise it is not possible to pass const objects to the constructor
		std::tuple<NOU_CORE::RemoveConst_t<ARGS>...> m_args;

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

		\details
		Constructs a new Task that will execute the passed invocable using the passed arguments.

		If the invocable is a member function pointer, the object that is used to call that member function
		needs to be the first parameter in the \p args parameter list.
		*/
		explicit Task(InvocableType &&invocable, ARGS&&... args);

		/**
		\return True, if the invocable was actually executed, false if not.

		\brief Executes the passed invocable.
		*/
		virtual void execute() override;

		/**
		\return The result of the execution of the invocable .

		\brief Returns the result of the invocable. 

		\details
		Returns the result of the invocable. This result is only valid if execute() has at least been called 
		once. If the result is not valid, ErrorCodes::INVALID_OBJECT will be pushed to the error handler.
		*/
		ReturnType& getResult();

		/**
		\return The result of the execution of the invocable .

		\brief Returns the result of the invocable.

		\details
		Returns the result of the invocable. This result is only valid if execute() has at least been called
		once. If the result is not valid, ErrorCodes::INVALID_OBJECT will be pushed to the error handler.
		*/
		const ReturnType& getResult() const;

		/**
		\returns The result of the execution of the invocable as an r-value.

		\brief Returns the result of the execution of the invocable as an r-value.

		\details
		Returns the result of the execution of the invocable as an r-value. This result is only valid if 
		execute() has at least been called once. If the result is not valid, ErrorCodes::INVALID_OBJECT will 
		be pushed to the error handler.

		*/
		ReturnType&& moveResult();
	};

	///\cond
	//A specialization for the task when the return type is void.
	template<typename I, typename... ARGS>
	class Task<void, I, ARGS...> final : public internal::AbstractTask
	{
#ifdef NOU_EXISTS_FEATURE_IS_INVOCABLE_R
		static_assert(NOU_CORE::IsInvocableR<void, I, ARGS...>::value);
#endif

	public:
		using ReturnType = void;
		using InvocableType = I;

	private:
		std::tuple<NOU_CORE::RemoveConst_t<ARGS>...> m_args;
		InvocableType m_invocable;

	public:
		explicit Task(InvocableType&& invocable, ARGS&&... args);

		virtual void execute() override;

		ReturnType getResult() const;

		ReturnType moveResult();
	};
	///\endcond

	/**
	\tparam I    The invocable type.
	\tparam ARGS The argument types.

	\param invocable The invocable.
	\param args      The arguments.

	\brief This convenience function constructs a task from a function (or function like types, like 
	       functors).

	\details
	This convenience function constructs a task from a function (or function like types, like functors). If
	used together with \p auto, it is possible to avoid large template parameter lists altogether.

	This function also works with member function pointers as invocable. If such pointer is passed, the first
	parameter must be the object that the member function is called with (the remaining parameters will follow
	after this object).
	*/
	template<typename I, typename... ARGS>
	Task<NOU_CORE::InvokeResult_t<I, NOU_CORE::RemoveReference_t<ARGS>...>, I,
		NOU_CORE::RemoveReference_t<ARGS>...> makeTask(I&& invocable, ARGS&&... args);

	///\cond
	template<typename R, typename I, typename... ARGS>
	Task<R, I, ARGS...>::Task(InvocableType&& invocable, ARGS&&... args) :
		m_invocable(NOU_CORE::forward<InvocableType>(invocable)),
		m_args(NOU_CORE::forward<ARGS>(args)...)
	{}

	template<typename R, typename I, typename... ARGS>
	void Task<R, I, ARGS...>::execute()
	{
		m_result = NOU_CORE::apply(m_invocable, m_args);
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

	template<typename R, typename I, typename... ARGS>
	typename Task<R, I, ARGS...>::ReturnType&& Task<R, I, ARGS...>::moveResult()
	{
		return NOU_CORE::move(*m_result);
	}



	template<typename I, typename... ARGS>
	Task<void, I, ARGS...>::Task(InvocableType&& invocable, ARGS&&... args) :
		m_invocable(NOU_CORE::forward<InvocableType>(invocable)),
		m_args(NOU_CORE::forward<ARGS>(args)...)
	{}

	template<typename I, typename... ARGS>
	void Task<void, I, ARGS...>::execute()
	{
		NOU_CORE::apply(m_invocable, m_args);
	}

	template<typename I, typename... ARGS>
	typename Task<void, I, ARGS...>::ReturnType Task<void, I, ARGS...>::getResult() const
	{}

	template<typename I, typename... ARGS>
	typename Task<void, I, ARGS...>::ReturnType Task<void, I, ARGS...>::moveResult()
	{}

	template<typename I, typename... ARGS>
	Task<NOU_CORE::InvokeResult_t<I, NOU_CORE::RemoveReference_t<ARGS>...>, I, 
		NOU_CORE::RemoveReference_t<ARGS>...> makeTask(I&& invocable, ARGS&&... args)
	{
		using TaskType = Task<NOU_CORE::InvokeResult_t<I, NOU_CORE::RemoveReference_t<ARGS>...>, I,
			NOU_CORE::RemoveReference_t<ARGS>...>;

		return TaskType(NOU_CORE::forward<typename TaskType::InvocableType>(invocable),
			NOU_CORE::forward<NOU_CORE::RemoveReference_t<ARGS>>(args)...);
	}
	///\endcond
}

#endif