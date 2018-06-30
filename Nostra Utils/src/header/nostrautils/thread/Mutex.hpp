#ifndef NOU_THREAD_MUTEX_HPP
#define	NOU_THREAD_MUTEX_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Utils.hpp"

#include <mutex>

/** \file Mutex.hpp
\author	 Lukas Reichmann
\since   1.0.0
\version 1.0.1
\brief   This file provides a mutex class.

\see nostra::utils::thread::Mutex
*/

namespace NOU::NOU_THREAD
{
	/**
	\brief A mutex with very little overhead, but also limited capabilities. This mutex can only be locked and
	       unlocked. As of now, this class is merely a wrapper for std::mutex.
	*/
	class Mutex
	{
	public:
		/**
		\brief The type of the mutex that is internally used.
		*/
		using UnderlyingType = std::mutex;

	private:
		/**
		\brief The mutex that is being wrapped around.
		*/
		UnderlyingType m_mutex;

	public:
		/**
		\brief Locks the mutex.
		*/
		NOU_FUNC void lock();

		/**
		\brief Unlocks the mutex.
		*/
		NOU_FUNC void unlock();

		/**
		\return True, if the mutex was locked, false if not (it was already locked in that case).

		\brief If the mutex is unlocked, it will be locked. Otherwise nothing will happen.
		*/
		NOU_FUNC boolean tryLock();

		/**
		\return The underlying mutex.

		\brief Returns the underlying mutex.
		*/
		NOU_FUNC UnderlyingType& getUnderlying();

		/**
		\return The underlying mutex.

		\brief Returns the underlying mutex.
		*/
		NOU_FUNC const UnderlyingType& getUnderlying() const;
	};
}

#endif