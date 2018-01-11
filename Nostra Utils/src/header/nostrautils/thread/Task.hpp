#ifndef	NOU_THREAD_TASK_HPP
#define	NOU_THREAD_TASK_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\Meta.hpp"
#include "nostrautils\dat_alg\Uninitialized.hpp"
#include "nostrautils\mem_mngt\Pointer.hpp"

#include <tuple>

namespace NOU::NOU_THREAD
{
	class AbstractTask
	{
	public:
		virtual ~AbstractTask() = default;

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
		using InvocableType = F;
		using ReturnType = NOU_CORE::InvokeResult_t<F, T, ARGS...>;

	private:
		std::tuple<T, ARGS...> m_args;
		InvocableType m_invocable;
		NOU_DAT_ALG::Uninitialized<ReturnType> m_result;

	public:
		MemberFunctionTask(const StoredType &stored, InvocableType invocable, ARGS&&...args);
		MemberFunctionTask(StoredType &&stored, InvocableType invocable, ARGS&&...args);

		virtual void execute() override;

		virtual void* getResult() override;
	};

	template<typename T, typename F, typename... ARGS>
	class MemberFunPtrWrapper
	{
		static_assert(std::is_pointer_v<T>);

	private:
		T m_ptr;
		F m_invocable;

	public:
		MemberFunPtrWrapper(T ptr, F invocable);
		auto operator () (ARGS&... args);
	};

	template<typename T, typename F, typename... ARGS>
	class MemberFunctionTask<T*, F, ARGS...> final : public AbstractTask
	{
	public:
		using StoredType = T*;
		using InvocableType = F;
		using ReturnType = int;//NOU_CORE::InvokeResult_t<F, NOU_CORE::removeConst_t<T>, ARGS...>;

	private:
		MemberFunPtrWrapper<StoredType, F, ARGS...> m_invocableAndStored;
		std::tuple<ARGS...> m_args;
		NOU_DAT_ALG::Uninitialized<ReturnType> m_result;

	public:
		MemberFunctionTask(StoredType stored, InvocableType invocable, ARGS&&...args);

		virtual void execute() override;

		virtual void* getResult() override;
	};

	using Task = NOU_MEM_MNGT::UniquePtr<AbstractTask>;

	template<typename I, typename... ARGS>
	NOU_FUNC Task makeTaskFromInvocable(const I &invocable, ARGS&&... args);

	template<typename I, typename... ARGS>
	NOU_FUNC Task makeTaskFromInvocable(I &&invocable, ARGS&&... args);

	template<typename T, typename I, typename... ARGS>
	NOU_FUNC Task makeTaskFromMemberFunction(const T &t, I invocable, ARGS&&... args);

	template<typename T, typename I, typename... ARGS>
	NOU_FUNC Task makeTaskFromMemberFunction(T &&t, I invocable, ARGS&&... args);

	template<typename T, typename... ARGS>
	InvocableTask<T, ARGS...>::InvocableTask(const InvocableType &invocable, ARGS&&... args) :
		m_invocable(invocable),
		m_args(NOU_CORE::forward<ARGS>(args)...)
	{}

	template<typename T, typename... ARGS>
	InvocableTask<T, ARGS...>::InvocableTask(InvocableType &&invocable, ARGS&&...args) :
		m_invocable(invocable),
		m_args(NOU_CORE::forward<ARGS>(args)...)
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

	template<typename T, typename F, typename... ARGS>
	MemberFunctionTask<T, F, ARGS...>::MemberFunctionTask(const StoredType &stored, InvocableType invocable, 
		ARGS&&...args) :
		m_invocable(invocable),
		m_args(std::forward_as_tuple(stored, NOU_CORE::forward<ARGS>(args)...))
	{}

	template<typename T, typename F, typename... ARGS>
	MemberFunctionTask<T, F, ARGS...>::MemberFunctionTask(StoredType &&stored, InvocableType invocable, 
		ARGS&&...args) :
		m_invocable(invocable),
		m_args(std::forward_as_tuple(std::forward<StoredType>(stored), NOU_CORE::forward<ARGS>(args)...))
	{}

	template<typename T, typename F, typename... ARGS>
	void MemberFunctionTask<T, F, ARGS...>::execute()
	{
		//create &m_stored to avoid copy
		m_result = std::apply(m_invocable, m_args);
	}

	template<typename T, typename F, typename... ARGS>
	void* MemberFunctionTask<T, F, ARGS...>::getResult()
	{
		return &(*m_result);
	}



	template<typename T, typename F, typename... ARGS>
	MemberFunPtrWrapper<T, F, ARGS...>::MemberFunPtrWrapper(T ptr, F invocable) :
		m_ptr(ptr),
		m_invocable(invocable)
	{}

	template<typename T, typename F, typename... ARGS>
	auto MemberFunPtrWrapper<T, F, ARGS...>::operator () (ARGS&... args)
	{
		return (m_ptr->*m_invocable)(NOU_CORE::forward<ARGS>(args)...);
	}



	template<typename T, typename F, typename... ARGS>
	MemberFunctionTask<T*, F, ARGS...>::MemberFunctionTask(StoredType stored, InvocableType invocable,
		ARGS&&...args) :
		m_invocableAndStored(stored, invocable),
		m_args(NOU_CORE::forward<ARGS>(args)...)
	{}

	template<typename T, typename F, typename... ARGS>
	void MemberFunctionTask<T*, F, ARGS...>::execute()
	{
		m_result = std::apply(m_invocableAndStored, m_args);
	}

	template<typename T, typename F, typename... ARGS>
	void* MemberFunctionTask<T*, F, ARGS...>::getResult()
	{
		return &(*m_result);
	}




	template<typename I, typename... ARGS>
	NOU_FUNC Task makeTaskFromInvocable(const I &invocable, ARGS&&... args)
	{
		///\todo Replace new with appropriate allocator
		return Task(new InvocableTask<I, ARGS...>(invocable, NOU_CORE::forward<ARGS...>(args)),
			NOU_MEM_MNGT::defaultDeleter);
	}

	template<typename I, typename... ARGS>
	NOU_FUNC Task makeTaskFromInvocable(I &&invocable, ARGS&&... args)
	{
		///\todo Replace new with appropriate allocator
		return Task(new InvocableTask<I, ARGS...>(NOU_CORE::forward<I>(invocable), NOU_CORE::forward<ARGS...>(args)),
			NOU_MEM_MNGT::defaultDeleter);
	}

	template<typename T, typename I, typename... ARGS>
	NOU_FUNC Task makeTaskFromMemberFunction(const T &t, I invocable, ARGS&&... args)
	{
		///\todo Replace new with appropriate allocator
		return Task(new MemberFunctionTask<T, I, ARGS...>(t, invocable,
			NOU_CORE::forward<ARGS>(args)...), NOU_MEM_MNGT::defaultDeleter);
	}

	template<typename T, typename I, typename... ARGS>
	NOU_FUNC Task makeTaskFromMemberFunction(T &&t, I invocable, ARGS&&... args)
	{
		///\todo Replace new with appropriate allocator
		return Task(new MemberFunctionTask<T, I, ARGS...>(NOU_CORE::forward<T>(t), NOU_CORE::forward<I>(invocable),
			NOU_CORE::forward<ARGS>(args)...), NOU_MEM_MNGT::defaultDeleter);
	}
}

#endif