#ifndef	NOU_THREAD_TASK_HPP
#define	NOU_THREAD_TASK_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"
#include "nostrautils\dat_alg\Uninitialized.hpp"

#include <tuple>

namespace NOU::NOU_THREAD
{
	class AbstractTask
	{
	public:
		virtual void execute() = 0;

		virtual void* getResult() = 0;
	};

	template<typename T, typename... ARGS>
	class InvocableTask final : public AbstractTask
	{
		static_assert(NOU_CORE::IsInvocable<T, ARGS...>::value);

	public:
		using InvocableType = T*;
		using ReturnType = NOU_CORE::InvokeResult_t<T, ARGS...>;

	private:
		std::tuple<ARGS...> m_args;
		InvocableType m_invocable;
		NOU_DAT_ALG::Uninitialized<ReturnType> m_result;

	public:
		InvocableTask(const InvocableType &invocable, ARGS&&...args);
		InvocableTask(InvocableType &&invocable, ARGS&&...args);

		virtual void execute() override;

		virtual void* getResult() override;
	};

	template<typename T, typename F, typename... ARGS>
	class MemberFunctionTask final : public AbstractTask
	{
	public:
		using StoredType = T;
		using InvocableType = F*;
		using ReturnType = NOU_CORE::InvokeResult_t<T, ARGS...>;

	private:
		std::tuple<ARGS...> m_args;
		StoredType m_stored;
		InvocableType m_invocable;
		NOU_DAT_ALG::Uninitialized<ReturnType> m_result;

	public:
		MemberFunctionTask(const StoredType &stored, InvocableType invocable, ARGS&&...args);
		MemberFunctionTask(StoredType &&stored, InvocableType invocable, ARGS&&...args);

		virtual void execute() override;

		virtual void* getResult() override;
	};

	template<typename T, typename... ARGS>
	InvocableTask<T, ARGS...>::InvocableTask(const InvocableType &invocable, ARGS&&...args) :
		m_invocable(invocable),
		m_args(args...)
	{}

	template<typename T, typename... ARGS>
	InvocableTask<T, ARGS...>::InvocableTask(InvocableType &&invocable, ARGS&&...args) :
		m_invocable(NOU_CORE::move(invocable)),
		m_args(args)
	{}

	template<typename T, typename... ARGS>
	void InvocableTask<T, ARGS...>::execute()
	{
		m_result = std::apply(m_invocable, m_args);
	}

	template<typename T, typename... ARGS>
	void* InvocableTask<T, ARGS...>::getResult()
	{
		return &(*m_result);
	}
}

#endif