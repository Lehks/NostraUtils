//
// Created by GaetanTayouNganmo on 26.04.18.
//

#ifndef UNTITLED3_MYMATHFUNCTION_HPP
#define UNTITLED3_MYMATHFUNCTION_HPP
#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\math\Vec.hpp"

namespace NOU::NOU_MATH
{


	template<class T>
	class MyMathFunction {

	public:


		static T abs(T number);

		static T pow(T number, T exponent);

		static T sqrt(T number);

		static T exp(T number);

		static T fac(T number);

		static T log(T number);

		static T cos(T number);

		static T sin(T number);

		static T tan(T number);

		static T acos(T number);

		static T asin(T number);

		static T atan(T number);
	};

	template <class T>
	T MyMathFunction<T>::abs(T number) {

		if (number < 0) {
			return -number;
		}
		else {
			return number;
		}

	}

	template <class T>
	T MyMathFunction<T>::pow(T number, T exponent) {
		T result = 1;

		for (int i = 0; i < abs(exponent); i++)
			result *= number;
		result = (exponent < 0) ? 1 / result : result;

		return result;
	}

	template <class T>
	T MyMathFunction<T>::sqrt(T number) {
		double e = 0.00001; //define the precision of your result
		T result = number;

		while ((result - number / result) > e) //loop until precision satisfied
		{
			result = (result + number / result) / 2;
		}
		return result;
	}

	template <class T>
	T MyMathFunction<T>::exp(T number) {
		if (number == 0) {
			return 1;
		}
		else if (number == 1) {
			const double e = 2.7182818284590454;
			return e;

		}
		else {
			return exp(number - 1);
		}

	}

	template <class T>
	T MyMathFunction<T>::fac(T number) {
		int i = 1;
		T fac = 1;

		while (i <= number) {
			fac *= i;
			i++;
		}
		return fac;

	}

	template <class T>
	T MyMathFunction<T>::log(T number) {
		T A = (number - 1);
		T B = (number + 1);
		// int j = 1;
		T result = A / B + pow(A, 3) / 3 * pow(B, 3) + pow(A, 5) / 5 * pow(B, 5) + pow(A, 7) / 7 * pow(B, 7) +
			pow(A, 9) / 9 * pow(B, 9) + pow(A, 11) / 11 * pow(B, 11) + pow(A, 13) / 13 * pow(B, 13);
		/*for(int j = 3; j <= 13; j+=2){

			result += (pow(A, j)/j*pow(B,j));
		}*/

		return 2 * result;

	}

	template<class T>
	T MyMathFunction<T>::cos(T number) {
		number = number * 3.14 / 180;
		//T result = 1;
		T result = 1 - pow(number, 2) / fac(2) + pow(number, 4) / fac(4) - pow(number, 6) / fac(6) + pow(number, 8) / fac(8);

		return result;
	}

	template<class T>
	T MyMathFunction<T>::sin(T number) {
		number = number * 3.14 / 180;
		T result = number - pow(number, 3) / fac(3) + pow(number, 5) / fac(5) - pow(number, 7) / fac(7);
		return result;
	}

	template<class T>
	T MyMathFunction<T>::tan(T number) {
		T result = (sin(number) / cos(number));
		return result;
	}

	template<class T>
	T MyMathFunction<T>::acos(T number) {
		T result = 1 / cos(number);
		return result;
	}

	template<class T>
	T MyMathFunction<T>::asin(T number) {
		T result = 1 / sin(number);
		return result;
	}

	template<class T>
	T MyMathFunction<T>::atan(T number) {
		T result = 1 / tan(number);
		return result;
	}


}

#endif //UNTITLED3_MYMATHFUNCTION_HPP