#ifndef NOU_DAT_ALG_RANDOM_HPP
#define NOU_DAT_ALG_RANDOM_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/dat_alg/Utils.hpp"
#include "nostrautils/dat_alg/Comparator.hpp"
#include <iostream>	 
#include <ctime>


/** \file Random.hpp
\author  Mahan Karimi
\since   1.0.0
\version 1.0.0
\brief   This file generates you a Random number between an interval.
*/
namespace NOU::NOU_DAT_ALG
{
	class NOU_CLASS Random
	{
	public:
		using Seed = uint64;
		using Value = uint64;

		constexpr static Seed USE_TIME_AS_SEED = -1;

	private:
		Seed m_seed;

	public:
		Random(Seed seed = USE_TIME_AS_SEED);

		/**
		\brief A function that sets a seed for the random function
		\param seed The seed to use.
		*/
		void setSeed(Seed seed);

		/**
		\brief A function that generates you a random number
		\return A random number in the interval \f$\left[0, MAX_INT\right[\f$ with MAX_INT being the maximum value of a 64 bit unsigned integer.
		*/
		Value rand();

		/**
		\brief A function that generates you a random number in an interval.
		\param a where you interval starts (this value is included in the interval)
		\param b where you interval ends (this value is included in the interval)
		\return A random number in the interval \f$\left[a, b\right[\f$.
		*/
		Value rand(Value a, Value b);
	};

}
#endif