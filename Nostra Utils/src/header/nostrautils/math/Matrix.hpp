#ifndef NOU_MATH_MATRIX_HPP
#define NOU_MATH_MATRIX_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\math\Vec.hpp"

namespace NOU::NOU_MATH
{
	template<uint32 N, uint32 M, typename T = float32>
	class NOU_CLASS Matrix
	{
		public:
			using Type = T;

		private:
			Vec<N, Type> m_data[M];

		public:
			Matrix();
			void setValue(uint32 x, uint32 y, T value);
			Matrix add(const Matrix &matrix);
	};

	template<uint32 N, uint32 M, typename T>
	Matrix<N, M, T>::Matrix()
	{
		
	}

	template<uint32 N, uint32 M, typename T>
	Matrix<N, M, T> Matrix<N, M, T>::add(const Matrix<N, M, T> &matrix)
	{
		Matrix<N, M, T> m Matrix<N, M, T>();

		
		return m;
	}


}

#endif

