#ifndef NOU_DAT_ALG_RANDOM_HPP
#define NOU_DAT_ALG_RANDOM_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\dat_alg\Comparator.hpp"
#include <iostream>
#include <ctime>

#include <cstdlib>

/** \file Random.hpp
\author  Mahan Karimi
\since   0.0.1
\version 0.0.1
\brief   This file generates you a Random number between a interval.
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
		\param s {s for seed }
		*/
		void setSeed(Seed seed);

		/**
		\brief A function that generates you a random function
		\return A random number in the interval \f$\left[0, MAX_INT\right[\f$ with MAX_INT being the maximum 
		        value of a 64 bit unsigned integer.
		*/
		Value rand();

		/**
		\brief A function that generates you a random number in an interval.
		\param a Where you interval begins (this value is included in the interval)
		\param b Where you interval ends (this value is included in the interval)
		\return A random number in the interval \f$\left[a, b\right[\f$.
		*/
		Value rand(Value a, Value b);
	};

}
#endif