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
			using Rows = N;
			using Columns = M;

		private:
			Vec<Rows, Type> m_data[Columns];

		public:
			Matrix();
	};

	template<uint32 N, uint32 M, typename T>
	Matrix<N, M, T>::Matrix()
	{
		
	}
}

#endif

