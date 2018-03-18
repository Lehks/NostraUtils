#ifndef NOU_MATH_MATRIX_HPP
#define NOU_MATH_MATRIX_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\math\Vec.hpp"

namespace NOU::NOU_MATH
{
	template<uint32 R, uint32 C, typename T = float32>
	class NOU_CLASS Matrix
	{
		public:
			using Type = T;

		private:
			Vec<R, Type> m_data[C];

		public:
			Matrix();
	};

	template<uint32 R, uint32 C, typename T>
	Matrix<R, C, T>::Matrix()
	{
		// Fill Matrix with vectors of value 0.
		for (i = 0; i < C; i++)
		{
			m_data[i] = Vec<R, T>();
		}
	}
}

#endif

