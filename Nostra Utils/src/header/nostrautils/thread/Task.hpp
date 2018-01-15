#ifndef	NOU_THREAD_TASK_HPP
#define	NOU_THREAD_TASK_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"
#include "nostrautils\dat_alg\Uninitialized.hpp"
#include "nostrautils\mem_mngt\Pointer.hpp"

#include <tuple>
#include <type_traits>

namespace NOU::NOU_THREAD
{
	class NOU_CLASS AbstractTask
	{
	public:
		virtual ~AbstractTask() = default;

		virtual boolean execute() = 0;

		virtual void* getResultPtr() = 0;
		virtual const void* getResultPtr() const = 0;
	};

	template<typename R, typename I, typename... ARGS>
	class NOU_CLASS Task final : AbstractTask
	{
		static_assert(NOU_CORE::IsInvocableR<R, I, ARGS...>::value);

	public:
		using ReturnType = R;
		using InvocableType = I;

	private:
		std::tuple<ARGS...> m_args;
		InvocableType m_invocable;
		NOU_DAT_ALG::Uninitialized<ReturnType> m_result;

	public:
		explicit Task(InvocableType&& invocable, ARGS&&... args);

		virtual boolean execute() override;

		virtual void* getResultPtr() override;
		virtual const void* getResultPtr() const override;
		ReturnType& getResult();
		const ReturnType& getResult() const;
	};

	template<typename I, typename... ARGS>
	NOU_FUNC Task<std::invoke_result_t<I, std::remove_reference_t<ARGS>...>, I, 
		std::remove_reference_t<ARGS>...>makeTask(I&& invocable, ARGS&&... args);

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
		m_result = std::apply(m_invocable, m_args);
		return false;
	}

	template<typename R, typename I, typename... ARGS>
	void* Task<R, I, ARGS...>::getResultPtr()
	{
		return m_result.data();
	}

	template<typename R, typename I, typename... ARGS>
	const void* Task<R, I, ARGS...>::getResultPtr() const
	{
		return m_result.data();
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
	Task<std::invoke_result_t<I, std::remove_reference_t<ARGS>...>, I, std::remove_reference_t<ARGS>...>
		makeTask(I&& invocable, ARGS&&... args)
	{
		using TaskType = Task<std::invoke_result_t<I, std::remove_reference_t<ARGS>...>, I,
			std::remove_reference_t<ARGS>...>;

		return TaskType(NOU_CORE::forward<typename TaskType::InvocableType>(invocable),
			NOU_CORE::forward<std::remove_reference_t<ARGS>>(args)...);
	}
}

#endif