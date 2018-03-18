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
			Type getValue(uint32 x, uint32 y) const;
			void setValue(uint32 x, uint32 y, T value) const;
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


	template<uint32 R, uint32 C, typename T>
	typename Matrix<R, C, T>::Type Matrix<R, C, T>::getValue(uint32 x, uint32 y) const
	{
		// Check bounds
		NOU_COND_PUSH_DBG_ERROR(
			(x >= R || x < 0),
			NOU_CORE::getErrorHandler(),
			NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS,
			"X Index out of bounds!"
		);

		NOU_COND_PUSH_DBG_ERROR(
			(y >= C || y < 0),
			NOU_CORE::getErrorHandler(),
			NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS,
			"Y Index out of bounds!"
		);

		return m_data[y].getCom(x);
	}


	template<uint32 R, uint32 C, typename T>
	void Matrix<R, C, T>::setValue(uint32 x, uint32 y, T value) const
	{
		// Check bounds
		NOU_COND_PUSH_DBG_ERROR(
			(x >= R || x < 0),
			NOU_CORE::getErrorHandler(),
			NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS,
			"X Index out of bounds!"
		);

		NOU_COND_PUSH_DBG_ERROR(
			(y >= C || y < 0),
			NOU_CORE::getErrorHandler(),
			NOU_CORE::ErrorCodes::INDEX_OUT_OF_BOUNDS,
			"Y Index out of bounds!"
		);

		m_data[y].setCom(x, value);
	}
}

#endif

