#ifndef NOU_THREAD_THREAD_WRAPPER_HPP
#define NOU_THREAD_THREAD_WRAPPER_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Utils.hpp"

#include <thread>

/**
\file    thread\ThreadWrapper.hpp
\author  Lukas Reichmann
\version 1.0.0
\since   1.0.0

\brief This file contains an platform independent wrapper class for a thread. 

\see nostra::utils::thread::ThreadWrapper
*/

namespace NOU::NOU_THREAD
{
	/**
	\brief A platform independent wrapper for a thread. Currently, std::thread is used.
	*/
	class NOU_CLASS ThreadWrapper
	{
	public:
		/**
		\brief The type of the underlying thread. This may change in the future and may even
		       not be consistent among platforms.
		*/
		using UnderylingType = std::thread;

		/**
		\brief The type that is used to uniquely identify a thread.
		*/
		using ID = std::thread::id;

	private:
		/**
		\brief The thread that this class wraps around.
		*/
		UnderylingType m_thread;

	public:
		/**
		\return The maximum amount of threads that can be run simultaneously on the current CPU.

		\brief Returns the maximum amount of threads that can be run simultaneously on the current CPU,
		       or 0 if that value can not be determined.
		*/
		static uint32 maxThreads();

		/**
		\param function The function to execute.
		\param args     The arguments that will be passed to the function.

		\brief Constructs a new thread wrapper that executes the passed function with the passed arguments.
		*/
		template<typename F, typename... ARGS>
		explicit ThreadWrapper(F &&function, ARGS&&... args);

		/**
		\brief Copying threads is not allowed.
		*/
		ThreadWrapper(const ThreadWrapper&) = delete;

		/**
		\param other The instance to move from.

		\brief Moves the thread from another instance to this one.
		*/
		ThreadWrapper(ThreadWrapper&& other);

		/**
		\return The underlying thread.

		\brief Returns the thread that is being wrapped around.
		*/
		UnderylingType& getUnderlying();

		/**
		\return The underlying thread.

		\brief Returns the thread that is being wrapped around.
		*/
		const UnderylingType& getUnderlying() const;

		/**
		\brief If possible, joins the thread.
		*/
		void join();

		/**
		\brief If possible, joins the thread.
		*/
		void detach();

		/**
		\return Whether the thread is joinable or not.

		\brief Returns whether the thread is joinable or not.
		*/
		boolean joinable() const;

		/**
		\return The ID of the thread.

		\brief Returns the ID of the thread.
		*/
		ID getID() const;
	};

	template<typename F, typename... ARGS>
	ThreadWrapper::ThreadWrapper(F &&function, ARGS&&... args) :
		m_thread(NOU_CORE::forward<F>(function), NOU_CORE::forward<ARGS>(args)...)
	{}
}

#endif