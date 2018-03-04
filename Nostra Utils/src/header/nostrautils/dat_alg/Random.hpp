#ifndef NOU_DAT_ALG_RANDOM_HPP
#define NOU_DAT_ALG_RANDOM_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\dat_alg\Comparator.hpp"
#include <iostream>


/** \file Random.hpp
\author  Mahan Karimi
\since   0.0.1
\version 0.0.1
\brief   This file generates you a Random number between a interval.
*/
namespace NOU::NOU_DAT_ALG
{
	/*
	\ Const for the random function
	*/
	static const double A = 0.001342;
	static const double C = 0.00025194;
	static const double m = 1.0;

	/**
	\This function generates you a random number
	\return a random number
	*/

	template <typename T >
	T rand();

	/**
	\ This function gives you a random number beetween an interval from a to b
	\ tparam a , a is the start number from your interval
	\ tparam b , b is the end number from your interval
	\ tparam n , n must be choiced so that n is in your interval for example  a = 5 , b = 10 and for n must valid {a <= n && n >= b }
	\ return a random number from your interval
	*/
	
	sizeType randTwo(sizeType a, sizeType b, sizeType n);


	
	sizeType rand()
	{
		sizeType prev = 0;
		prev = A * prev + fmod(C, m);
		return prev;
	}

	
	sizeType randTwo(sizeType a, sizeType b, sizeType n)
	{

		if (a <= n && n >= b)
			n = rand();

		return n;
	}





}
#endif