#ifndef NOU_MATH_MATRIX_HPP
#define NOU_MATH_MATRIX_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\math\Vec.hpp"

namespace NOU::NOU_MATH
{
	/**
	 * R = y
	 * C = x
	 */
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
			Matrix add(const Matrix<R, C, T> & matrix) const;
			Matrix sub(const Matrix<R, C, T> & matrix) const;
			Matrix mult(const Type) const;
			Matrix transpose() const;
			Vec getRow(uint32 index) const;
			Vec getColumn(uint32 index) const;
			uint32 getNumRows() const;
			uint32 getNumColumns() const;

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

		return m_data[x].getCom(y);
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

		m_data[x].setCom(y, value);
	}


	template<uint32 R, uint32 C, typename T>
	Matrix<R, C, T> Matrix<R, C, T>::add(const Matrix<R, C, T> & matrix) const
	{
		Matrix<R, C, T> result = Matrix<R, C, T>;

		sizeType i;
		sizeType j;

		for (i = 0; i < C; i++)
		{
			for (j = 0; j < R; j++)
			{
				result.setValue(j, i, this->getValue(j, i) + matrix.getValue(j, i));
			}
		}

		return result;
	}


	template<uint32 R, uint32 C, typename T>
	Matrix<R, C, T> Matrix<R, C, T>::sub(const Matrix<R, C, T> & matrix) const
	{
		Matrix<R, C, T> result = Matrix<R, C, T>;

		sizeType i;
		sizeType j;

		for (i = 0; i < C; i++)
		{
			for (j = 0; j < R; j++)
			{
				result.setValue(j, i, this->getValue(j, i) - matrix.getValue(j, i));
			}
		}

		return result;
	}


	template<uint32 R, uint32 C, typename T>
	Matrix<R, C, T> Matrix<R, C, T>::mult(const Type num) const
	{
		Matrix<R, C, T> result = Matrix<R, C, T>;

		sizeType i;
		sizeType j;

		for (i = 0; i < C; i++)
		{
			for (j = 0; j < R; j++)
			{
				result.setValue(j, i, this->getValue(j, i) * num);
			}
		}

		return result;
	}


	template<uint32 R, uint32 C, typename T>
	Matrix<C, R, T> Matrix<R, C, T>::transpose() const
	{
		Matrix<C, R, T> result = Matrix<C, R, T>;

		sizeType i;
		sizeType j;

		for (i = 0; i < C; i++)
		{
			for (j = 0; j < R; j++)
			{
				result.setValue(i, j, this->getValue(j, i));
			}
		}

		return result;
	}


	template<uint32 R, uint32 C, typename T>
	Vec<C, T> Matrix<R, C, T>::getRow(uint32 index) const
	{
		T values[C];
		sizeType i;

		for (i = 0; i < C; i++)
		{
			values[i] = this->getValue(i, index);
		}

		return Vec<C, T>(values);
	}


	template<uint32 R, uint32 C, typename T>
	Vec<R, T> Matrix<R, C, T>::getColumn(uint32 index) const
	{
		T values[R];
		sizeType i;

		for (i = 0; i < R; i++)
		{
			values[i] = this->getValue(index, i);
		}

		return Vec<R, T>(values);
	}


	template<uint32 R, uint32 C, typename T>
	uint32 Matrix<R, C, T>::getNumColumns() const
	{
		return C;
	}


	template<uint32 R, uint32 C, typename T>
	uint32 Matrix<R, C, T>::getNumRows() const
	{
		return R;
	}

/*	template<uint32 N, uint32 M, typename T>
	Matrix<N, M, T> Matrix<N, M, T>::add(const Matrix<N, M, T> &matrix)
	{
		Matrix<N, M, T> m Matrix<N, M, T>();

		
		return m;
	}
	*/

}


#endif

