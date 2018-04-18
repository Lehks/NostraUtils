#ifndef NOU_DAT_ALG_LAZY_EVALUATION_PROPERTY_HPP
#define NOU_DAT_ALG_LAZY_EVALUATION_PROPERTY_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Meta.hpp"
#include "nostrautils/dat_alg/Uninitialized.hpp"

/** \file LazyEvaluationProperty.hpp
\author  Lukas Reichmann
\since   1.0.0
\version 1.0.0
\brief   This file contains a container that stores a value that is lazily evaluated.
*/

namespace NOU::NOU_DAT_ALG
{
	/**
	\tparam T              The type of the value that will be evaluated.
	\tparam EVAL_FUNC      The function that will be used to make the stored value.
	\tparam EVAL_FUNC_ARGS The parameters that will be passed to the function that 
	                       will be used to make the stored value.

	\brief A container that stores a value without initializing it until the value is requested.

	\details 
	A container that stores a value without initializing it until the value is requested using 
	the passed function to make it. It is also possible to reevaluate the value multiple times,
	if necessary, even with different functions.
	*/
	template<typename T, typename EVAL_FUNC, typename... EVAL_FUNC_ARGS>
	class NOU_CLASS LazyEvaluationProperty final
	{
//		static_assert(NOU_CORE::IsInvocableR<T, EVAL_FUNC, EVAL_FUNC_ARGS>::value);

	private:
		/**
		\brief The stored value.
		*/
		Uninitialized<T> m_data;

		/**
		\brief True, if the value is evaluated, false if not.
		*/
		boolean           m_evaluated;

		/**
		The function used to evaluate the value.
		*/
		EVAL_FUNC         m_evaluationFunc;

	public:
		/**
		\param evaluationFunc The function that is used to evaluate the value later on.

		\brief Constructs a new instance using the passed function as the evaluation function.
		*/
		LazyEvaluationProperty(EVAL_FUNC evaluationFunc);

		/**
		\param args The parameters that will be passed to the evaluation function.
		\return A reference to the stored, evaluated value.

		\brief Returns a reference to the stored the evaluated value.

		\details
		Returns a reference to the evaluated value. If not evaluated yet, the value will be
		evaluated at this point.
		*/
		T& get(EVAL_FUNC_ARGS&... args);

		/**
		\param args The parameters that will be passed to the evaluation function.
		\return A const reference to the stored, evaluated value.
	
		\brief Returns a const reference to the stored the evaluated value.
	
		\details
		Returns a const reference to the evaluated value. If not evaluated yet, the value will be
		evaluated at this point.
		*/
		const T& get(EVAL_FUNC_ARGS&... args) const;

		/**
		\param evaluationFunc A new function that is from now on used to evaluate the value.
		\param args The parameters that will be passed to the evaluation function.

		\brief Reevaluates the value at this point and may set a new function.

		\details
		Reevaluates the value at this point and may set a new function. If the passed function 
		is nullptr, the old evaluation function will be kept.
		*/
		void reevaluate(EVAL_FUNC evaluationFunc = nullptr, EVAL_FUNC_ARGS&... args);

		/**
		\param value The new value.

		\brief Manually set the stored value to the passed one. This function will set the
		instance to the evaluated state.
		*/
		void set(const T &value);

		/**
		\param evaluationFunc A new function that is from now on used to evaluate the value.

		\brief Sets up the value for reevaluation and may set a new function.

		\details
		Sets up the value for reevaluation and may set a new function. If the passed function
		is nullptr, the old evaluation function will be kept.
		The value will NOT be evaluated at this point. This will happen at the next call to
		get().
		*/
		void needsReevaluation(EVAL_FUNC evaluationFunc = nullptr);

		/**
		\return A pointer to the stored object.
		\brief  Returns a pointer to the stored object for direct access of
		methods.
		\note This only works if ARGS is empty.
		*/
		T* operator -> ();

		/**
		\return A const pointer to the stored object.
		\brief  Returns a const pointer to the stored object for direct access of
		methods.
		\note This only works if ARGS is empty.
		*/
		const T* operator -> () const;

		/**
		\return A reference to the stored object.
		\brief  Returns a reference to the stored object.
		\note This only works if ARGS is empty.
		*/
		T& operator * ();

		/**
		\return A const reference to the stored object.
		\brief  Returns a const reference to the stored object.
		\note This only works if ARGS is empty.
		*/
		const T& operator * () const;
	};

	template<typename T, typename EVAL_FUNC, typename... EVAL_FUNC_ARGS>
	LazyEvaluationProperty<T, EVAL_FUNC, EVAL_FUNC_ARGS...>::LazyEvaluationProperty(EVAL_FUNC evaluationFunc) :
		m_evaluated(false),
		m_evaluationFunc(evaluationFunc)
	{}

	template<typename T, typename EVAL_FUNC, typename... EVAL_FUNC_ARGS>
	T& LazyEvaluationProperty<T, EVAL_FUNC, EVAL_FUNC_ARGS...>::get(EVAL_FUNC_ARGS&... args)
	{
		if (!m_evaluated)
			reevaluate(nullptr, args...);

		return *m_data;
	}

	template<typename T, typename EVAL_FUNC, typename... EVAL_FUNC_ARGS>
	const T& LazyEvaluationProperty<T, EVAL_FUNC, EVAL_FUNC_ARGS...>::get(EVAL_FUNC_ARGS&... args) const
	{
		if (!m_evaluated)
			reevaluate(nullptr, args...);
	
		return *m_data;
	}

	template<typename T, typename EVAL_FUNC, typename... EVAL_FUNC_ARGS>
	void LazyEvaluationProperty<T, EVAL_FUNC, EVAL_FUNC_ARGS...>::reevaluate(EVAL_FUNC evaluationFunc, EVAL_FUNC_ARGS&... args)
	{
		if (evaluationFunc != nullptr)
			m_evaluationFunc = evaluationFunc;

		m_data = m_evaluationFunc(args...);
		m_evaluated = true;
	}

	template<typename T, typename EVAL_FUNC, typename... EVAL_FUNC_ARGS>
	void LazyEvaluationProperty<T, EVAL_FUNC, EVAL_FUNC_ARGS...>::set(const T &value)
	{
		m_data = value;
		m_evaluated = true;
	}

	template<typename T, typename EVAL_FUNC, typename... EVAL_FUNC_ARGS>
	void LazyEvaluationProperty<T, EVAL_FUNC, EVAL_FUNC_ARGS...>::needsReevaluation(EVAL_FUNC evaluationFunc)
	{
		if (evaluationFunc != nullptr)
			m_evaluationFunc = evaluationFunc;

		m_evaluated = false;
	}

	template<typename T, typename EVAL_FUNC, typename... EVAL_FUNC_ARGS>
	T* LazyEvaluationProperty<T, EVAL_FUNC, EVAL_FUNC_ARGS...>::operator -> ()
	{
		return &get();
	}

	template<typename T, typename EVAL_FUNC, typename... EVAL_FUNC_ARGS>
	const T* LazyEvaluationProperty<T, EVAL_FUNC, EVAL_FUNC_ARGS...>::operator -> () const
	{
		return &get();
	}

	template<typename T, typename EVAL_FUNC, typename... EVAL_FUNC_ARGS>
	T& LazyEvaluationProperty<T, EVAL_FUNC, EVAL_FUNC_ARGS...>::operator * ()
	{
		return get();
	}

	template<typename T, typename EVAL_FUNC, typename... EVAL_FUNC_ARGS>
	const T& LazyEvaluationProperty<T, EVAL_FUNC, EVAL_FUNC_ARGS...>::operator * () const
	{
		return get();
	}
}

#endif