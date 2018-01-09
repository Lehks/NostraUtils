#ifndef	NOU_THREAD_TASK_HPP
#define	NOU_THREAD_TASK_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"

namespace NOU::NOU_THREAD
{
	class AbstractTask
	{
	public:
		virtual void execute() = 0;

		virtual void* getResult() = 0;
	};

	template<typename T, typename... ARGS>
	class InvocableTask final
	{
		static_assert(NOU_CORE::IsInvocable<T, ARGS...>::value);

	public:
		using ReturnType = NOU_CORE::InvokeResult_t<T, ARGS...>;

		T m_invocable;
		ReturnType m_result;

	private:
		InvocableTask(const T &invocable, ARGS&&...args);
		InvocableTask(T &&invocable, ARGS&&...args);

		virtual void execute();

		virtual void* getResult();
	};

	template<typename T, typename... ARGS>
	InvocableTask<T, ARGS...>::InvocableTask(const T &invocable, ARGS&&...args) :
		m_invocable(invocable)
	{

	}
}

#endif