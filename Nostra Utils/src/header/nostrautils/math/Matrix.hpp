#ifndef NOU_MATH_MATRIX_HPP
#define NOU_MATH_MATRIX_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/math/Vector.hpp"

#include <initializer_list>

/** \file math/Matrix.hpp
\author	 Lukas Reichmann
\since   1.0.0
\version 1.0.0
\brief   This file provides functionality to work with matrices.
*/


namespace NOU::NOU_MATH
{
	/**
	\tparam The type of the matrix base class.

	\brief A single row in a matrix.



	\details
	A single row in a matrix. The purpose of this class is to allow access to the elements of a matrix by 
	using two array subscript operators.

	Instances of this class are not meant to be stored.
	*/
	template<typename MatBase>
	class NOU_CLASS MatrixRow
	{
	private:
		/**
		\brief The type of the matrix base.
		*/
		using Type = typename MatBase::Type;

		/**
		\brief A pointer to the matrix that this row is from
		*/
		MatBase  *m_mat;

		/**
		\brief The index of the row in the matrix.
		*/
		sizeType  m_row;

	public:
		/**
		\param mat The matrix that this row is in.
		\param row The index of the row in the matrix.

		\brief Constructs a new row from the passed parameters.
		*/
		MatrixRow(MatBase &mat, sizeType row);

		/**
		\param col The column of the element to return.

		\return The element in the passed column in this row.

		\brief Returns the element in the passed column in this row.
		*/
		Type& operator [] (sizeType col);

		/**
		\param col The column of the element to return.

		\return The element in the passed column in this row.

		\brief Returns the element in the passed column in this row.
		*/
		const Type& operator [] (sizeType col) const;
	};

	/**
	\tparam T The type of the elements in the matrix.
	\tparam R The amount of rows in the matrix.
	\tparam C The amount of columns in the matrix.

	\brief The base class of all matrix types.

	\details
	The base class of all matrix types. This class provides the storage for the matrices and access to that 
	storage.

	\note
	This class stores all elements in row major order.
	*/
    template<typename T, sizeType R, sizeType C>
    class NOU_CLASS MatrixBase
    {
        static_assert(R > 1, "There must be at least two rows in a matrix.");
        static_assert(C > 1, "There must be at least two columns in a matrix.");

    public:
		/**
		\brief The type of initializer list used by one of the constructors.
		*/
        template<typename U>
        using InitializerList = std::initializer_list<U>;

		/**
		\brief The type of the elements in the matrix.
		*/
		using Type = T;

    private:
		/**
		\brief The array in which the elements are stored in.
		*/
        T m_data[C][R];

    public:
		/**
		\brief Constructs a new instance without initializing any of the elements.
		*/
        MatrixBase() = default;

		/**
		\param values The values of the matrix.

		\brief Initializes all of the elements in the matrix.

		\details
		Initializes all of the elements in the matrix. The inner initializer list are the columns and the
		outer list the rows.

		That means, that such a construct of initializer lists:

		\code{.cpp}
		{{1, 2, 3},
		 {4, 5, 6},
		 {7, 8, 9}}
		\endcode

		would result in such a matrix:

		\f$
		\begin{matrix}
		1 & 2 & 3 \\
		4 & 5 & 6 \\
		7 & 8 & 9
		\end{matrix}
		\f$
		*/
        MatrixBase(const InitializerList<InitializerList<T>> &values);

        const T& value(sizeType row, sizeType col) const;
        T& value(sizeType row, sizeType col);

		MatrixRow<MatrixBase> operator [] (sizeType row);
		const MatrixRow<const MatrixBase> operator [] (sizeType row) const;

        sizeType rows() const;
        sizeType columns() const;

        const T* data() const;
        T* data();
    };

    template<typename T, sizeType R, sizeType C>
    class NOU_CLASS Matrix : public MatrixBase<T, R, C>
    {
    public:
        using Base = MatrixBase<T, R, C>;

        static Matrix<T, R, C> zeroes();
        static Matrix<T, R, C> identity();

        Matrix() = default;
        Matrix(const typename MatrixBase<T, R, C>::template InitializerList<typename MatrixBase<T, R, C>::template InitializerList<T>> &values);

        Matrix add(const Matrix &other) const;
        Matrix& addAssign(const Matrix &other);

        Matrix sub(const Matrix &other) const;
        Matrix& subAssign(const Matrix &other);

        template<NOU::sizeType OC>
        Matrix<T, R, OC> mult(const Matrix<T, C, OC> &other) const;

        Vector<T, R> mult(const Vector<T, C> &other) const;

        Matrix mult(const T &other) const;
        Matrix& multAssign(const T &other);

        Matrix<T, C, R> transpose() const;
        
        Matrix copy() const;

        boolean equal(const Matrix &other) const;
        boolean unequal(const Matrix &other) const;

        Matrix operator + (const Matrix &other) const;
        Matrix& operator += (const Matrix &other);

        Matrix operator - (const Matrix &other) const;
        Matrix& operator -= (const Matrix &other);

        template<NOU::sizeType OC>
        Matrix<T, R, OC> operator * (const Matrix<T, C, OC> &other) const;

        Vector<T, R> operator * (const Vector<T, C> &other) const;

        Matrix operator * (const T &other) const;
        Matrix& operator *= (const T &other);

        boolean operator == (const Matrix &other) const;
        boolean operator != (const Matrix &other) const;
    };

    template<typename T>
    class NOU_CLASS Matrix<T, 2, 2> : public MatrixBase<T, 2, 2>
    {
    public:
        using Base = MatrixBase<T, 2, 2>;

        static Matrix<T, 2, 2> zeroes();
        static Matrix<T, 2, 2> identity();

        Matrix() = default;
        Matrix(const typename MatrixBase<T, 2, 2>::template InitializerList<typename MatrixBase<T, 2, 2>::template InitializerList<T>> &values);
        Matrix(const T &index00, const T &index01, const T &index10, const T &index11);

        Matrix add(const Matrix &other) const;
        Matrix& addAssign(const Matrix &other);

        Matrix sub(const Matrix &other) const;
        Matrix& subAssign(const Matrix &other);

        template<NOU::sizeType OC>
        Matrix<T, 2, OC> mult(const Matrix<T, 2, OC> &other) const;

        Matrix<T, 2, 2> mult(const Matrix<T, 2, 2> &other) const;

        Vector<T, 2> mult(const Vector<T, 2> &other) const;

        Matrix mult(const T &other) const;
        Matrix& multAssign(const T &other);

        Matrix<T, 2, 2> transpose() const;

        Matrix copy() const;

        boolean equal(const Matrix &other) const;
        boolean unequal(const Matrix &other) const;

        Matrix operator + (const Matrix &other) const;
        Matrix& operator += (const Matrix &other);

        Matrix operator - (const Matrix &other) const;
        Matrix& operator -= (const Matrix &other);

        template<NOU::sizeType OC>
        Matrix<T, 2, OC> operator * (const Matrix<T, 2, OC> &other) const;

        Vector<T, 2> operator * (const Vector<T, 2> &other) const;

        Matrix operator * (const T &other) const;
        Matrix& operator *= (const T &other);

        boolean operator == (const Matrix &other) const;
        boolean operator != (const Matrix &other) const;
    };

    template<typename T>
    class NOU_CLASS Matrix<T, 3, 3> : public MatrixBase<T, 3, 3>
    {
    public:
        using Base = MatrixBase<T, 3, 3>;

        static Matrix<T, 3, 3> zeroes();
        static Matrix<T, 3, 3> identity();

        Matrix() = default;
        Matrix(const typename MatrixBase<T, 3, 3>::template InitializerList<typename MatrixBase<T, 3, 3>::template InitializerList<T>> &values);
        Matrix(const T &index00, const T &index01, const T &index02, const T &index10, const T &index11, 
            const T &index12, const T &index20, const T &index21, const T &index22);

        Matrix add(const Matrix &other) const;
        Matrix& addAssign(const Matrix &other);

        Matrix sub(const Matrix &other) const;
        Matrix& subAssign(const Matrix &other);

        template<NOU::sizeType OC>
        Matrix<T, 3, OC> mult(const Matrix<T, 3, OC> &other) const;

        Matrix<T, 3, 3> mult(const Matrix<T, 3, 3> &other) const;

        Vector<T, 3> mult(const Vector<T, 3> &other) const;

        Matrix mult(const T &other) const;
        Matrix& multAssign(const T &other);

        Matrix<T, 3, 3> transpose() const;

        Matrix copy() const;

        boolean equal(const Matrix &other) const;
        boolean unequal(const Matrix &other) const;

        Matrix operator + (const Matrix &other) const;
        Matrix& operator += (const Matrix &other);

        Matrix operator - (const Matrix &other) const;
        Matrix& operator -= (const Matrix &other);

        template<NOU::sizeType OC>
        Matrix<T, 3, OC> operator * (const Matrix<T, 3, OC> &other) const;

        Vector<T, 3> operator * (const Vector<T, 3> &other) const;

        Matrix operator * (const T &other) const;
        Matrix& operator *= (const T &other);

        boolean operator == (const Matrix &other) const;
        boolean operator != (const Matrix &other) const;
    };

    template<typename T>
    class NOU_CLASS Matrix<T, 4, 4> : public MatrixBase<T, 4, 4>
    {
    public:
        using Base = MatrixBase<T, 4, 4>;

        static Matrix<T, 4, 4> zeroes();
        static Matrix<T, 4, 4> identity();

        Matrix() = default;
        Matrix(const typename MatrixBase<T, 4, 4>::template InitializerList<typename MatrixBase<T, 4, 4>::template InitializerList<T>> &values);
        Matrix(
            const T &index00, const T &index01, const T &index02, const T &index03,
            const T &index10, const T &index11, const T &index12, const T &index13,
            const T &index20, const T &index21, const T &index22, const T &index23,
            const T &index30, const T &index31, const T &index32, const T &index33);

        Matrix add(const Matrix &other) const;
        Matrix& addAssign(const Matrix &other);

        Matrix sub(const Matrix &other) const;
        Matrix& subAssign(const Matrix &other);

        template<NOU::sizeType OC>
        Matrix<T, 4, OC> mult(const Matrix<T, 4, OC> &other) const;

        Matrix<T, 4, 4> mult(const Matrix<T, 4, 4> &other) const;

        Vector<T, 4> mult(const Vector<T, 4> &other) const;

        Matrix mult(const T &other) const;
        Matrix& multAssign(const T &other);

        Matrix<T, 4, 4> transpose() const;

        Matrix copy() const;

        boolean equal(const Matrix &other) const;
        boolean unequal(const Matrix &other) const;

        Matrix operator + (const Matrix &other) const;
        Matrix& operator += (const Matrix &other);

        Matrix operator - (const Matrix &other) const;
        Matrix& operator -= (const Matrix &other);

        template<NOU::sizeType OC>
        Matrix<T, 4, OC> operator * (const Matrix<T, 4, OC> &other) const;

        Vector<T, 4> operator * (const Vector<T, 4> &other) const;

        Matrix operator * (const T &other) const;
        Matrix& operator *= (const T &other);

        boolean operator == (const Matrix &other) const;
        boolean operator != (const Matrix &other) const;
    };

    template<sizeType R, sizeType C>
    using Matf = Matrix<float32, R, C>;

    template<sizeType R, sizeType C>
    using Mati = Matrix<int32, R, C>;

    using Mat2  = Matf<2, 2>;
    using Mat2i = Mati<2, 2>;
    using Mat3  = Matf<3, 3>;
    using Mat3i = Mati<3, 3>;
    using Mat4  = Matf<4, 4>;
    using Mat4i = Mati<4, 4>;



	template<typename MatBase>
	MatrixRow<MatBase>::MatrixRow(MatBase &mat, sizeType row) :
		m_mat(&mat),
		m_row(row)
	{}

	template<typename MatBase>
	typename MatrixRow<MatBase>::Type& MatrixRow<MatBase>::operator [] (sizeType col)
	{
		return m_mat->value(m_row, col);
	}

	template<typename MatBase>
	const typename MatrixRow<MatBase>::Type& MatrixRow<MatBase>::operator [] (sizeType col) const
	{
		return m_mat->value(m_row, col);
	}



    template<typename T, sizeType R, sizeType C>
    MatrixBase<T, R, C>::MatrixBase(const InitializerList<InitializerList<T>> &values)
    {
        NOU_ASSERT(values.size() == R);

#ifdef NOU_DEBUG
        for (auto i = values.begin(); i != values.end(); i++)
            NOU_ASSERT(i->size() == C);
#endif

        sizeType col = 0;
        sizeType row = 0;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            for (auto j = i->begin(); j != i->end(); j++)
            {
                value(row, col) = *j;
                col++;
            }

            col = 0;
            row++;
        }
    }

    template<typename T, sizeType R, sizeType C>
    const T& MatrixBase<T, R, C>::value(sizeType row, sizeType col) const
    {
        return m_data[col][row];
    }

    template<typename T, sizeType R, sizeType C>
    T& MatrixBase<T, R, C>::value(sizeType row, sizeType col)
    {
        return m_data[col][row];
    }

    template<typename T, sizeType R, sizeType C>
    sizeType MatrixBase<T, R, C>::rows() const
    {
        return R;
    }

    template<typename T, sizeType R, sizeType C>
    sizeType MatrixBase<T, R, C>::columns() const
    {
        return C;
    }

    template<typename T, sizeType R, sizeType C>
    const T* MatrixBase<T, R, C>::data() const
    {
        return reinterpret_cast<const T*>(m_data);
    }

    template<typename T, sizeType R, sizeType C>
    T* MatrixBase<T, R, C>::data()
    {
        return reinterpret_cast<T*>(m_data);
    }

	template<typename T, sizeType R, sizeType C>
	MatrixRow<MatrixBase<T, R, C>> MatrixBase<T, R, C>::operator [] (sizeType row)
	{
		return MatrixRow<MatrixBase<T, R, C>>(*this, row);
	}

	template<typename T, sizeType R, sizeType C>
	const MatrixRow<const MatrixBase<T, R, C>> MatrixBase<T, R, C>::operator [] (sizeType row) const
	{
		return MatrixRow<const MatrixBase<T, R, C>>(*this, row);
	}




    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C> Matrix<T, R, C>::zeroes()
    {
        Matrix<T, R, C> ret;

        for (sizeType i = 0; i < R * C; i++)
            ret.data()[i] = 0;

        return ret;
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C> Matrix<T, R, C>::identity()
    {
        Matrix<T, R, C> ret = zeroes();

        sizeType cap = NOU_CORE::min(R, C);

        for (sizeType i = 0; i < cap; i++)
        {
            ret.value(i, i) = 1;
        }

        return ret;
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C>::Matrix(const typename MatrixBase<T, R, C>::template InitializerList<typename MatrixBase<T, R, C>::template InitializerList<T>> &values) :
        MatrixBase<T, R, C>(values)
    {}

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C> Matrix<T, R, C>::add(const Matrix &other) const
    {
        Matrix<T, R, C> ret;

        for (sizeType row = 0; row < Base::rows(); row++)
            for (sizeType col = 0; col < Base::columns(); col++)
                ret.value(row, col) = Base::value(row, col) + other.value(row, col);

        return ret;
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C>& Matrix<T, R, C>::addAssign(const Matrix<T, R, C> &other)
    {
        for (sizeType row = 0; row < Base::rows(); row++)
            for (sizeType col = 0; col < Base::columns(); col++)
                Base::value(row, col) += other.value(row, col);

        return *this;
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C> Matrix<T, R, C>::sub(const Matrix<T, R, C> &other) const
    {
        Matrix<T, R, C> ret;

        for (sizeType row = 0; row < Base::rows(); row++)
            for (sizeType col = 0; col < Base::columns(); col++)
                ret.value(row, col) = Base::value(row, col) - other.value(row, col);

        return ret;
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C>& Matrix<T, R, C>::subAssign(const Matrix<T, R, C> &other)
    {
        for (sizeType row = 0; row < Base::rows(); row++)
            for (sizeType col = 0; col < Base::columns(); col++)
                Base::value(row, col) -= other.value(row, col);

        return *this;
    }

    template<typename T, sizeType R, sizeType C>
    template<NOU::sizeType OC>
    Matrix<T, R, OC> Matrix<T, R, C>::mult(const Matrix<T, C, OC> &other) const
    {
        Matrix<T, R, OC> ret = Matrix<T, R, OC>::zeroes();

        for (sizeType row = 0; row < R; row++)
            for (sizeType col = 0; col < OC; col++)
                for (sizeType j = 0; j < Base::rows(); j++)
                    ret.value(row, col) += Base::value(row, j) * other.value(j, col);
                    
        return ret;
    }

    template<typename T, sizeType R, sizeType C>
    Vector<T, R> Matrix<T, R, C>::mult(const Vector<T, C> &other) const
    {
        Vector<T, R> ret;

        for (sizeType row = 0; row < Base::rows(); row++)
        {
            T rowVal = Base::value(row, 0) * other.value(0); //col 0; avoid having to initialize with 0

            for (sizeType col = 1; col < Base::columns(); col++)
            {
                rowVal += Base::value(row, col) * other.value(col);
            }

            ret.value(row) = rowVal;
        }

        return ret;
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C> Matrix<T, R, C>::mult(const T &other) const
    {
        Matrix<T, R, C> ret;

        for (sizeType row = 0; row < Base::rows(); row++)
            for (sizeType col = 0; col < Base::columns(); col++)
                ret.value(row, col) = Base::value(row, col) * other;

        return ret;
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C>& Matrix<T, R, C>::multAssign(const T &other)
    {
        for (sizeType row = 0; row < Base::rows(); row++)
            for (sizeType col = 0; col < Base::columns(); col++)
                Base::value(row, col) *= other;

        return *this;
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, C, R> Matrix<T, R, C>::transpose() const
    {
        Matrix<T, C, R> ret;

        for (sizeType row = 0; row < Base::rows(); row++)
            for (sizeType col = 0; col < Base::columns(); col++)
                ret.value(col, row) = Base::value(row, col);

        return ret;
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C> Matrix<T, R, C>::copy() const
    {
        Matrix<T, R, C> ret;

        for (sizeType i = 0; i < Base::rows() * Base::columns(); i++)
            ret.data()[i] =  Base::data()[i];

        return ret;
    }

    template<typename T, sizeType R, sizeType C>
    boolean Matrix<T, R, C>::equal(const Matrix<T, R, C> &other) const
    {
        if ( Base::data() == other.data())
            return true;

        for (sizeType i = 0; i < Base::rows() * Base::columns(); i++)
            if ( Base::data()[i] != other.data()[i])
                return false;

        return true;
    }

    template<typename T, sizeType R, sizeType C>
    boolean Matrix<T, R, C>::unequal(const Matrix &other) const
    {
        return !equal(other);
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C> Matrix<T, R, C>::operator + (const  Matrix<T, R, C> &other) const
    {
        return add(other);
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C>& Matrix<T, R, C>::operator += (const  Matrix<T, R, C> &other)
    {
        return addAssign(other);
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C> Matrix<T, R, C>::operator - (const  Matrix<T, R, C> &other) const
    {
        return sub(other);
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C>& Matrix<T, R, C>::operator -= (const  Matrix<T, R, C> &other)
    {
        return subAssign(other);
    }

    template<typename T, sizeType R, sizeType C>
    template<NOU::sizeType OC>
    Matrix<T, R, OC> Matrix<T, R, C>::operator * (const Matrix<T, C, OC> &other) const
    {
        return mult(other);
    }

    template<typename T, sizeType R, sizeType C>
    Vector<T, R> Matrix<T, R, C>::operator * (const Vector<T, C> &other) const
    {
        return mult(other);
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C> Matrix<T, R, C>::operator * (const T &other) const
    {
        return mult(other);
    }

    template<typename T, sizeType R, sizeType C>
    Matrix<T, R, C>& Matrix<T, R, C>::operator *= (const T &other)
    {
        return multAssign(other);
    }

    template<typename T, sizeType R, sizeType C>
    boolean Matrix<T, R, C>::operator == (const Matrix<T, R, C> &other) const
    {
        return equal(other);
    }

    template<typename T, sizeType R, sizeType C>
    boolean Matrix<T, R, C>::operator != (const Matrix<T, R, C> &other) const
    {
        return unequal(other);
    }






    template<typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::zeroes()
    {
        return Matrix<T, 2, 2>(0, 0, 0, 0);
    }

    template<typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::identity()
    {
        return Matrix<T, 2, 2>(1, 0, 0, 1);
    }

    template<typename T>
    Matrix<T, 2, 2>::Matrix(const typename MatrixBase<T, 2, 2>::template InitializerList<typename MatrixBase<T, 2, 2>::template InitializerList<T>> &values) :
        MatrixBase<T, 2, 2>(values)
    {}

    template<typename T>
    Matrix<T, 2, 2>::Matrix(const T &index00, const T &index01, const T &index10, const T &index11)
    {
        Base::value(0, 0) = index00;
        Base::value(0, 1) = index01;
        Base::value(1, 0) = index10;
        Base::value(1, 1) = index11;
    }

    template<typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::add(const Matrix &other) const
    {
        Matrix<T, 2, 2> ret;

        ret.value(0, 0) = Base::value(0, 0) + other.value(0, 0);
        ret.value(0, 1) = Base::value(0, 1) + other.value(0, 1);
        ret.value(1, 0) = Base::value(1, 0) + other.value(1, 0);
        ret.value(1, 1) = Base::value(1, 1) + other.value(1, 1);

        return ret;
    }

    template<typename T>
    Matrix<T, 2, 2>& Matrix<T, 2, 2>::addAssign(const Matrix<T, 2, 2> &other)
    {
        Base::value(0, 0) += other.value(0, 0);
        Base::value(0, 1) += other.value(0, 1);
        Base::value(1, 0) += other.value(1, 0);
        Base::value(1, 1) += other.value(1, 1);

        return *this;
    }

    template<typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::sub(const Matrix<T, 2, 2> &other) const
    {
        Matrix<T, 2, 2> ret;

        ret.value(0, 0) = Base::value(0, 0) - other.value(0, 0);
        ret.value(0, 1) = Base::value(0, 1) - other.value(0, 1);
        ret.value(1, 0) = Base::value(1, 0) - other.value(1, 0);
        ret.value(1, 1) = Base::value(1, 1) - other.value(1, 1);

        return ret;
    }

    template<typename T>
    Matrix<T, 2, 2>& Matrix<T, 2, 2>::subAssign(const Matrix<T, 2, 2> &other)
    {
        Base::value(0, 0) -= other.value(0, 0);
        Base::value(0, 1) -= other.value(0, 1);
        Base::value(1, 0) -= other.value(1, 0);
        Base::value(1, 1) -= other.value(1, 1);

        return *this;
    }

    template<typename T>
    template<NOU::sizeType OC>
    Matrix<T, 2, OC> Matrix<T, 2, 2>::mult(const Matrix<T, 2, OC> &other) const
    {
        Matrix<T, 2, OC> ret = Matrix<T, 2, OC>::zeroes();

        for (sizeType row = 0; row < 2; row++)
            for (sizeType col = 0; col < OC; col++)
                for (sizeType inner = 0; inner < Base::columns(); inner++)
                    ret.value(row, col) += Base::value(row, inner) * other.value(inner, col);

        return ret;
    }

    template<typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::mult(const Matrix<T, 2, 2> &other) const
    {
        Matrix<T, 2, 2> ret = zeroes();

        ret.value(0, 0) = Base::value(0, 0) * other.value(0, 0) + Base::value(0, 1) * other.value(1, 0);
        ret.value(0, 1) = Base::value(0, 0) * other.value(0, 1) + Base::value(0, 1) * other.value(1, 1);
        ret.value(1, 0) = Base::value(1, 0) * other.value(0, 0) + Base::value(1, 1) * other.value(1, 0); 
        ret.value(1, 1) = Base::value(1, 0) * other.value(0, 1) + Base::value(1, 1) * other.value(1, 1);

        return ret;
    }

    template<typename T>
    Vector<T, 2> Matrix<T, 2, 2>::mult(const Vector<T, 2> &other) const
    {
        Vector<T, 2> ret;

        ret.value(0) = Base::value(0, 0) * other.value(0) + Base::value(0, 1) * other.value(1);
        ret.value(1) = Base::value(1, 0) * other.value(0) + Base::value(1, 1) * other.value(1);

        return ret;
    }

    template<typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::mult(const T &other) const
    {
        Matrix<T, 2, 2> ret;

        ret.value(0, 0) = Base::value(0, 0) * other;
        ret.value(0, 1) = Base::value(0, 1) * other;
        ret.value(1, 0) = Base::value(1, 0) * other;
        ret.value(1, 1) = Base::value(1, 1) * other;

        return ret;
    }

    template<typename T>
    Matrix<T, 2, 2>& Matrix<T, 2, 2>::multAssign(const T &other)
    {
        Base::value(0, 0) *= other;
        Base::value(0, 1) *= other;
        Base::value(1, 0) *= other;
        Base::value(1, 1) *= other;

        return *this;
    }

    template<typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::transpose() const
    {
        Matrix<T, 2, 2> ret;

        ret.value(0, 0) = Base::value(0, 0);
        ret.value(0, 1) = Base::value(1, 0);
        ret.value(1, 0) = Base::value(0, 1);
        ret.value(1, 1) = Base::value(1, 1);

        return ret;
    }

    template<typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::copy() const
    {
        Matrix<T, 2, 2> ret;

        ret.value(0, 0) = Base::value(0, 0);
        ret.value(0, 1) = Base::value(0, 1);
        ret.value(1, 0) = Base::value(1, 0);
        ret.value(1, 1) = Base::value(1, 1);

        return ret;
    }

    template<typename T>
    boolean Matrix<T, 2, 2>::equal(const Matrix<T, 2, 2> &other) const
    {
        return ( Base::data() == other.data()) || 
            ( Base::value(0, 0) == other.value(0, 0) && 
                Base::value(0, 1) == other.value(0, 1) &&
                Base::value(1, 0) == other.value(1, 0) &&
                Base::value(1, 1) == other.value(1, 1));
    }

    template<typename T>
    boolean Matrix<T, 2, 2>::unequal(const Matrix &other) const
    {
        return !equal(other);
    }

    template<typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::operator + (const  Matrix<T, 2, 2> &other) const
    {
        return add(other);
    }

    template<typename T>
    Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator += (const  Matrix<T, 2, 2> &other)
    {
        return addAssign(other);
    }

    template<typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::operator - (const  Matrix<T, 2, 2> &other) const
    {
        return sub(other);
    }

    template<typename T>
    Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator -= (const  Matrix<T, 2, 2> &other)
    {
        return subAssign(other);
    }

    template<typename T>
    template<NOU::sizeType OC>
    Matrix<T, 2, OC> Matrix<T, 2, 2>::operator * (const Matrix<T, 2, OC> &other) const
    {
        return mult(other);
    }

    template<typename T>
    Vector<T, 2> Matrix<T, 2, 2>::operator * (const Vector<T, 2> &other) const
    {
        return mult(other);
    }

    template<typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::operator * (const T &other) const
    {
        return mult(other);
    }

    template<typename T>
    Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator *= (const T &other)
    {
        return multAssign(other);
    }

    template<typename T>
    boolean Matrix<T, 2, 2>::operator == (const Matrix<T, 2, 2> &other) const
    {
        return equal(other);
    }

    template<typename T>
    boolean Matrix<T, 2, 2>::operator != (const Matrix<T, 2, 2> &other) const
    {
        return unequal(other);
    }






    template<typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::zeroes()
    {
        return Matrix<T, 3, 3>(0, 0, 0, 0, 0, 0, 0, 0, 0);
    }

    template<typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::identity()
    {
        return Matrix<T, 3, 3>(1, 0, 0, 0, 1, 0, 0, 0, 1);
    }

    template<typename T>
    Matrix<T, 3, 3>::Matrix(const typename MatrixBase<T, 3, 3>::template InitializerList<typename MatrixBase<T, 3, 3>::template InitializerList<T>> &values) :
        MatrixBase<T, 3, 3>(values)
    {}

    template<typename T>
    Matrix<T, 3, 3>::Matrix(const T &index00, const T &index01, const T &index02, const T &index10,
        const T &index11, const T &index12, const T &index20, const T &index21, const T &index22)
    {
        Base::value(0, 0) = index00;
        Base::value(0, 1) = index01;
        Base::value(0, 2) = index02;
        Base::value(1, 0) = index10;
        Base::value(1, 1) = index11;
        Base::value(1, 2) = index12;
        Base::value(2, 0) = index20;
        Base::value(2, 1) = index21;
        Base::value(2, 2) = index22;
    }

    template<typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::add(const Matrix &other) const
    {
        Matrix<T, 3, 3> ret;

        ret.value(0, 0) = Base::value(0, 0) + other.value(0, 0);
        ret.value(0, 1) = Base::value(0, 1) + other.value(0, 1);
        ret.value(0, 2) = Base::value(0, 2) + other.value(0, 2);
        ret.value(1, 0) = Base::value(1, 0) + other.value(1, 0);
        ret.value(1, 1) = Base::value(1, 1) + other.value(1, 1);
        ret.value(1, 2) = Base::value(1, 2) + other.value(1, 2);
        ret.value(2, 0) = Base::value(2, 0) + other.value(2, 0);
        ret.value(2, 1) = Base::value(2, 1) + other.value(2, 1);
        ret.value(2, 2) = Base::value(2, 2) + other.value(2, 2);

        return ret;
    }

    template<typename T>
    Matrix<T, 3, 3>& Matrix<T, 3, 3>::addAssign(const Matrix<T, 3, 3> &other)
    {
        Base::value(0, 0) += other.value(0, 0);
        Base::value(0, 1) += other.value(0, 1);
        Base::value(0, 2) += other.value(0, 2);
        Base::value(1, 0) += other.value(1, 0);
        Base::value(1, 1) += other.value(1, 1);
        Base::value(1, 2) += other.value(1, 2);
        Base::value(2, 0) += other.value(2, 0);
        Base::value(2, 1) += other.value(2, 1);
        Base::value(2, 2) += other.value(2, 2);

        return *this;
    }

    template<typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::sub(const Matrix<T, 3, 3> &other) const
    {
        Matrix<T, 3, 3> ret;

        ret.value(0, 0) = Base::value(0, 0) - other.value(0, 0);
        ret.value(0, 1) = Base::value(0, 1) - other.value(0, 1);
        ret.value(0, 2) = Base::value(0, 2) - other.value(0, 2);
        ret.value(1, 0) = Base::value(1, 0) - other.value(1, 0);
        ret.value(1, 1) = Base::value(1, 1) - other.value(1, 1);
        ret.value(1, 2) = Base::value(1, 2) - other.value(1, 2);
        ret.value(2, 0) = Base::value(2, 0) - other.value(2, 0);
        ret.value(2, 1) = Base::value(2, 1) - other.value(2, 1);
        ret.value(2, 2) = Base::value(2, 2) - other.value(2, 2);

        return ret;
    }

    template<typename T>
    Matrix<T, 3, 3>& Matrix<T, 3, 3>::subAssign(const Matrix<T, 3, 3> &other)
    {
        Base::value(0, 0) -= other.value(0, 0);
        Base::value(0, 1) -= other.value(0, 1);
        Base::value(0, 2) -= other.value(0, 2);
        Base::value(1, 0) -= other.value(1, 0);
        Base::value(1, 1) -= other.value(1, 1);
        Base::value(1, 2) -= other.value(1, 2);
        Base::value(2, 0) -= other.value(2, 0);
        Base::value(2, 1) -= other.value(2, 1);
        Base::value(2, 2) -= other.value(2, 2);

        return *this;
    }

    template<typename T>
    template<NOU::sizeType OC>
    Matrix<T, 3, OC> Matrix<T, 3, 3>::mult(const Matrix<T, 3, OC> &other) const
    {
        Matrix<T, 3, OC> ret = Matrix<T, 3, OC>::zeroes();

        for (sizeType row = 0; row < 3; row++)
            for (sizeType col = 0; col < OC; col++)
                for (sizeType inner = 0; inner < Base::columns(); inner++)
                    ret.value(row, col) += Base::value(row, inner) * other.value(inner, col);

        return ret;
    }

    template<typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::mult(const Matrix<T, 3, 3> &other) const
    {
        Matrix<T, 3, 3> ret;

        ret.value(0, 0) = Base::value(0, 0) * other.value(0, 0) + Base::value(0, 1) * other.value(1, 0) + Base::value(0, 2) * other.value(2, 0);
        ret.value(0, 1) = Base::value(0, 0) * other.value(0, 1) + Base::value(0, 1) * other.value(1, 1) + Base::value(0, 2) * other.value(2, 1);
        ret.value(0, 2) = Base::value(0, 0) * other.value(0, 2) + Base::value(0, 1) * other.value(1, 2) + Base::value(0, 2) * other.value(2, 2);
        ret.value(1, 0) = Base::value(1, 0) * other.value(0, 0) + Base::value(1, 1) * other.value(1, 0) + Base::value(1, 2) * other.value(2, 0);
        ret.value(1, 1) = Base::value(1, 0) * other.value(0, 1) + Base::value(1, 1) * other.value(1, 1) + Base::value(1, 2) * other.value(2, 1);
        ret.value(1, 2) = Base::value(1, 0) * other.value(0, 2) + Base::value(1, 1) * other.value(1, 2) + Base::value(1, 2) * other.value(2, 2);
        ret.value(2, 0) = Base::value(2, 0) * other.value(0, 0) + Base::value(2, 1) * other.value(1, 0) + Base::value(2, 2) * other.value(2, 0);
        ret.value(2, 1) = Base::value(2, 0) * other.value(0, 1) + Base::value(2, 1) * other.value(1, 1) + Base::value(2, 2) * other.value(2, 1);
        ret.value(2, 2) = Base::value(2, 0) * other.value(0, 2) + Base::value(2, 1) * other.value(1, 2) + Base::value(2, 2) * other.value(2, 2);

        return ret;
    }

    template<typename T>
    Vector<T, 3> Matrix<T, 3, 3>::mult(const Vector<T, 3> &other) const
    {
        Vector<T, 3> ret;

        ret.value(0) = Base::value(0, 0) * other.value(0) + Base::value(0, 1) * other.value(1) + Base::value(0, 2) * other.value(2);
        ret.value(1) = Base::value(1, 0) * other.value(0) + Base::value(1, 1) * other.value(1) + Base::value(1, 2) * other.value(2);
        ret.value(2) = Base::value(2, 0) * other.value(0) + Base::value(2, 1) * other.value(1) + Base::value(2, 2) * other.value(2);

        return ret;
    }

    template<typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::mult(const T &other) const
    {
        Matrix<T, 3, 3> ret;

        ret.value(0, 0) = Base::value(0, 0) * other;
        ret.value(0, 1) = Base::value(0, 1) * other;
        ret.value(0, 2) = Base::value(0, 2) * other;
        ret.value(1, 0) = Base::value(1, 0) * other;
        ret.value(1, 1) = Base::value(1, 1) * other;
        ret.value(1, 2) = Base::value(1, 2) * other;
        ret.value(2, 0) = Base::value(2, 0) * other;
        ret.value(2, 1) = Base::value(2, 1) * other;
        ret.value(2, 2) = Base::value(2, 2) * other;

        return ret;
    }

    template<typename T>
    Matrix<T, 3, 3>& Matrix<T, 3, 3>::multAssign(const T &other)
    {
        Base::value(0, 0) *= other;
        Base::value(0, 1) *= other;
        Base::value(0, 2) *= other;
        Base::value(1, 0) *= other;
        Base::value(1, 1) *= other;
        Base::value(1, 2) *= other;
        Base::value(2, 0) *= other;
        Base::value(2, 1) *= other;
        Base::value(2, 2) *= other;

        return *this;
    }

    template<typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::transpose() const
    {
        Matrix<T, 3, 3> ret;

        ret.value(0, 0) = Base::value(0, 0);
        ret.value(0, 1) = Base::value(1, 0);
        ret.value(0, 2) = Base::value(2, 0);
        ret.value(1, 0) = Base::value(0, 1);
        ret.value(1, 1) = Base::value(1, 1);
        ret.value(1, 2) = Base::value(2, 1);
        ret.value(2, 0) = Base::value(0, 2);
        ret.value(2, 1) = Base::value(1, 2);
        ret.value(2, 2) = Base::value(2, 2);

        return ret;
    }

    template<typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::copy() const
    {
        Matrix<T, 3, 3> ret;

        ret.value(0, 0) = Base::value(0, 0);
        ret.value(0, 1) = Base::value(0, 1);
        ret.value(0, 2) = Base::value(0, 2);
        ret.value(1, 0) = Base::value(1, 0);
        ret.value(1, 1) = Base::value(1, 1);
        ret.value(1, 2) = Base::value(1, 2);
        ret.value(2, 0) = Base::value(2, 0);
        ret.value(2, 1) = Base::value(2, 1);
        ret.value(2, 2) = Base::value(2, 2);

        return ret;
    }

    template<typename T>
    boolean Matrix<T, 3, 3>::equal(const Matrix<T, 3, 3> &other) const
    {
        return ( Base::data() == other.data()) ||
               (Base::value(0, 0) == other.value(0, 0) &&
                Base::value(0, 1) == other.value(0, 1) && 
                Base::value(0, 1) == other.value(0, 1) &&

                Base::value(1, 0) == other.value(1, 0) &&
                Base::value(1, 1) == other.value(1, 1) && 
                Base::value(1, 2) == other.value(1, 2) &&

                Base::value(2, 0) == other.value(2, 0) &&
                Base::value(2, 1) == other.value(2, 1) &&
                Base::value(2, 2) == other.value(2, 2));
    }

    template<typename T>
    boolean Matrix<T, 3, 3>::unequal(const Matrix &other) const
    {
        return !equal(other);
    }

    template<typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::operator + (const  Matrix<T, 3, 3> &other) const
    {
        return add(other);
    }

    template<typename T>
    Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator += (const  Matrix<T, 3, 3> &other)
    {
        return addAssign(other);
    }

    template<typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::operator - (const  Matrix<T, 3, 3> &other) const
    {
        return sub(other);
    }

    template<typename T>
    Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator -= (const  Matrix<T, 3, 3> &other)
    {
        return subAssign(other);
    }

    template<typename T>
    template<NOU::sizeType OC>
    Matrix<T, 3, OC> Matrix<T, 3, 3>::operator * (const Matrix<T, 3, OC> &other) const
    {
        return mult(other);
    }

    template<typename T>
    Vector<T, 3> Matrix<T, 3, 3>::operator * (const Vector<T, 3> &other) const
    {
        return mult(other);
    }

    template<typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::operator * (const T &other) const
    {
        return mult(other);
    }

    template<typename T>
    Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator *= (const T &other)
    {
        return multAssign(other);
    }

    template<typename T>
    boolean Matrix<T, 3, 3>::operator == (const Matrix<T, 3, 3> &other) const
    {
        return equal(other);
    }

    template<typename T>
    boolean Matrix<T, 3, 3>::operator != (const Matrix<T, 3, 3> &other) const
    {
        return unequal(other);
    }








    template<typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::zeroes()
    {
        return Matrix<T, 4, 4>(
            0, 0, 0, 0, 
            0, 0, 0, 0, 
            0, 0, 0, 0, 
            0, 0, 0, 0);
    }

    template<typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::identity()
    {
        return Matrix<T, 4, 4>(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    }

    template<typename T>
    Matrix<T, 4, 4>::Matrix(const typename MatrixBase<T, 4, 4>::template InitializerList<typename MatrixBase<T, 4, 4>::template InitializerList<T>> &values) :
        MatrixBase<T, 4, 4>(values)
    {}

    template<typename T>
    Matrix<T, 4, 4>::Matrix(
        const T &index00, const T &index01, const T &index02, const T &index03,
        const T &index10, const T &index11, const T &index12, const T &index13,
        const T &index20, const T &index21, const T &index22, const T &index23,
        const T &index30, const T &index31, const T &index32, const T &index33)
    {
        Base::value(0, 0)	= index00;
        Base::value(0, 1) = index01;
        Base::value(0, 2) = index02;
        Base::value(0, 3) = index03;
        Base::value(1, 0) = index10;
        Base::value(1, 1) = index11;
        Base::value(1, 2) = index12;
        Base::value(1, 3) = index13;
        Base::value(2, 0) = index20;
        Base::value(2, 1) = index21;
        Base::value(2, 2) = index22;
        Base::value(2, 3) = index23;
        Base::value(3, 0) = index30;
        Base::value(3, 1) = index31;
        Base::value(3, 2) = index32;
        Base::value(3, 3) = index33;
    }

    template<typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::add(const Matrix &other) const
    {
        Matrix<T, 4, 4> ret;

        ret.value(0, 0) = Base::value(0, 0) + other.value(0, 0);
        ret.value(0, 1) = Base::value(0, 1) + other.value(0, 1);
        ret.value(0, 2) = Base::value(0, 2) + other.value(0, 2);
        ret.value(0, 3) = Base::value(0, 3) + other.value(0, 3);
        ret.value(1, 0) = Base::value(1, 0) + other.value(1, 0);
        ret.value(1, 1) = Base::value(1, 1) + other.value(1, 1);
        ret.value(1, 2) = Base::value(1, 2) + other.value(1, 2);
        ret.value(1, 3) = Base::value(1, 3) + other.value(1, 3);
        ret.value(2, 0) = Base::value(2, 0) + other.value(2, 0);
        ret.value(2, 1) = Base::value(2, 1) + other.value(2, 1);
        ret.value(2, 2) = Base::value(2, 2) + other.value(2, 2);
        ret.value(2, 3) = Base::value(2, 3) + other.value(2, 3);
        ret.value(3, 0) = Base::value(3, 0) + other.value(3, 0);
        ret.value(3, 1) = Base::value(3, 1) + other.value(3, 1);
        ret.value(3, 2) = Base::value(3, 2) + other.value(3, 2);
        ret.value(3, 3) = Base::value(3, 3) + other.value(3, 3);

        return ret;
    }

    template<typename T>
    Matrix<T, 4, 4>& Matrix<T, 4, 4>::addAssign(const Matrix<T, 4, 4> &other)
    {
        Base::value(0, 0) += other.value(0, 0);
        Base::value(0, 1) += other.value(0, 1);
        Base::value(0, 2) += other.value(0, 2);
        Base::value(0, 3) += other.value(0, 3);
        Base::value(1, 0) += other.value(1, 0);
        Base::value(1, 1) += other.value(1, 1);
        Base::value(1, 2) += other.value(1, 2);
        Base::value(1, 3) += other.value(1, 3);
        Base::value(2, 0) += other.value(2, 0);
        Base::value(2, 1) += other.value(2, 1);
        Base::value(2, 2) += other.value(2, 2);
        Base::value(2, 3) += other.value(2, 3);
        Base::value(3, 0) += other.value(3, 0);
        Base::value(3, 1) += other.value(3, 1);
        Base::value(3, 2) += other.value(3, 2);
        Base::value(3, 3) += other.value(3, 3);

        return *this;
    }

    template<typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::sub(const Matrix<T, 4, 4> &other) const
    {
        Matrix<T, 4, 4> ret;

        ret.value(0, 0) = Base::value(0, 0) - other.value(0, 0);
        ret.value(0, 1) = Base::value(0, 1) - other.value(0, 1);
        ret.value(0, 2) = Base::value(0, 2) - other.value(0, 2);
        ret.value(0, 3) = Base::value(0, 3) - other.value(0, 3);
        ret.value(1, 0) = Base::value(1, 0) - other.value(1, 0);
        ret.value(1, 1) = Base::value(1, 1) - other.value(1, 1);
        ret.value(1, 2) = Base::value(1, 2) - other.value(1, 2);
        ret.value(1, 3) = Base::value(1, 3) - other.value(1, 3);
        ret.value(2, 0) = Base::value(2, 0) - other.value(2, 0);
        ret.value(2, 1) = Base::value(2, 1) - other.value(2, 1);
        ret.value(2, 2) = Base::value(2, 2) - other.value(2, 2);
        ret.value(2, 3) = Base::value(2, 3) - other.value(2, 3);
        ret.value(3, 0) = Base::value(3, 0) - other.value(3, 0);
        ret.value(3, 1) = Base::value(3, 1) - other.value(3, 1);
        ret.value(3, 2) = Base::value(3, 2) - other.value(3, 2);
        ret.value(3, 3) = Base::value(3, 3) - other.value(3, 3);

        return ret;
    }

    template<typename T>
    Matrix<T, 4, 4>& Matrix<T, 4, 4>::subAssign(const Matrix<T, 4, 4> &other)
    {
        Base::value(0, 0) -= other.value(0, 0);
        Base::value(0, 1) -= other.value(0, 1);
        Base::value(0, 2) -= other.value(0, 2);
        Base::value(0, 3) -= other.value(0, 3);
        Base::value(1, 0) -= other.value(1, 0);
        Base::value(1, 1) -= other.value(1, 1);
        Base::value(1, 2) -= other.value(1, 2);
        Base::value(1, 3) -= other.value(1, 3);
        Base::value(2, 0) -= other.value(2, 0);
        Base::value(2, 1) -= other.value(2, 1);
        Base::value(2, 2) -= other.value(2, 2);
        Base::value(2, 3) -= other.value(2, 3);
        Base::value(3, 0) -= other.value(3, 0);
        Base::value(3, 1) -= other.value(3, 1);
        Base::value(3, 2) -= other.value(3, 2);
        Base::value(3, 3) -= other.value(3, 3);

        return *this;
    }

    template<typename T>
    template<NOU::sizeType OC>
    Matrix<T, 4, OC> Matrix<T, 4, 4>::mult(const Matrix<T, 4, OC> &other) const
    {
        Matrix<T, 4, OC> ret = Matrix<T, 4, OC>::zeroes();

        for (sizeType row = 0; row < 4; row++)
            for (sizeType col = 0; col < OC; col++)
                for (sizeType inner = 0; inner < Base::columns(); inner++)
                    ret.value(row, col) += Base::value(row, inner) * other.value(inner, col);

        return ret;
    }

    template<typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::mult(const Matrix<T, 4, 4> &other) const
    {
        Matrix<T, 4, 4> ret; 
        
        ret.value(0, 0) = Base::value(0, 0) * other.value(0, 0) + Base::value(0, 1) * other.value(1, 0) + Base::value(0, 2) * other.value(2, 0) + Base::value(0, 3) * other.value(3, 0);
        ret.value(0, 1) = Base::value(0, 0) * other.value(0, 1) + Base::value(0, 1) * other.value(1, 1) + Base::value(0, 2) * other.value(2, 1) + Base::value(0, 3) * other.value(3, 1);
        ret.value(0, 2) = Base::value(0, 0) * other.value(0, 2) + Base::value(0, 1) * other.value(1, 2) + Base::value(0, 2) * other.value(2, 2) + Base::value(0, 3) * other.value(3, 2);
        ret.value(0, 3) = Base::value(0, 0) * other.value(0, 3) + Base::value(0, 1) * other.value(1, 3) + Base::value(0, 2) * other.value(2, 3) + Base::value(0, 3) * other.value(3, 3);
        ret.value(1, 0) = Base::value(1, 0) * other.value(0, 0) + Base::value(1, 1) * other.value(1, 0) + Base::value(1, 2) * other.value(2, 0) + Base::value(1, 3) * other.value(3, 0);
        ret.value(1, 1) = Base::value(1, 0) * other.value(0, 1) + Base::value(1, 1) * other.value(1, 1) + Base::value(1, 2) * other.value(2, 1) + Base::value(1, 3) * other.value(3, 1);
        ret.value(1, 2) = Base::value(1, 0) * other.value(0, 2) + Base::value(1, 1) * other.value(1, 2) + Base::value(1, 2) * other.value(2, 2) + Base::value(1, 3) * other.value(3, 2);
        ret.value(1, 3) = Base::value(1, 0) * other.value(0, 3) + Base::value(1, 1) * other.value(1, 3) + Base::value(1, 2) * other.value(2, 3) + Base::value(1, 3) * other.value(3, 3);
        ret.value(2, 0) = Base::value(2, 0) * other.value(0, 0) + Base::value(2, 1) * other.value(1, 0) + Base::value(2, 2) * other.value(2, 0) + Base::value(2, 3) * other.value(3, 0);
        ret.value(2, 1) = Base::value(2, 0) * other.value(0, 1) + Base::value(2, 1) * other.value(1, 1) + Base::value(2, 2) * other.value(2, 1) + Base::value(2, 3) * other.value(3, 1);
        ret.value(2, 2) = Base::value(2, 0) * other.value(0, 2) + Base::value(2, 1) * other.value(1, 2) + Base::value(2, 2) * other.value(2, 2) + Base::value(2, 3) * other.value(3, 2);
        ret.value(2, 3) = Base::value(2, 0) * other.value(0, 3) + Base::value(2, 1) * other.value(1, 3) + Base::value(2, 2) * other.value(2, 3) + Base::value(2, 3) * other.value(3, 3);
        ret.value(3, 0) = Base::value(3, 0) * other.value(0, 0) + Base::value(3, 1) * other.value(1, 0) + Base::value(3, 2) * other.value(2, 0) + Base::value(3, 3) * other.value(3, 0);
        ret.value(3, 1) = Base::value(3, 0) * other.value(0, 1) + Base::value(3, 1) * other.value(1, 1) + Base::value(3, 2) * other.value(2, 1) + Base::value(3, 3) * other.value(3, 1);
        ret.value(3, 2) = Base::value(3, 0) * other.value(0, 2) + Base::value(3, 1) * other.value(1, 2) + Base::value(3, 2) * other.value(2, 2) + Base::value(3, 3) * other.value(3, 2);
        ret.value(3, 3) = Base::value(3, 0) * other.value(0, 3) + Base::value(3, 1) * other.value(1, 3) + Base::value(3, 2) * other.value(2, 3) + Base::value(3, 3) * other.value(3, 3);

        return ret;
    }

    template<typename T>
    Vector<T, 4> Matrix<T, 4, 4>::mult(const Vector<T, 4> &other) const
    {
        Vector<T, 4> ret;

        ret.value(0) = Base::value(0, 0) * other.value(0) + Base::value(0, 1) * other.value(1) + Base::value(0, 2) * other.value(2) + Base::value(0, 3) * other.value(3);
        ret.value(1) = Base::value(1, 0) * other.value(0) + Base::value(1, 1) * other.value(1) + Base::value(1, 2) * other.value(2) + Base::value(1, 3) * other.value(3);
        ret.value(2) = Base::value(2, 0) * other.value(0) + Base::value(2, 1) * other.value(1) + Base::value(2, 2) * other.value(2) + Base::value(2, 3) * other.value(3);
        ret.value(3) = Base::value(3, 0) * other.value(0) + Base::value(3, 1) * other.value(1) + Base::value(3, 2) * other.value(2) + Base::value(3, 3) * other.value(3);

        return ret;
    }

    template<typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::mult(const T &other) const
    {
        Matrix<T, 4, 4> ret;

        ret.value(0, 0) = Base::value(0, 0) * other;
        ret.value(0, 1) = Base::value(0, 1) * other;
        ret.value(0, 2) = Base::value(0, 2) * other;
        ret.value(0, 3) = Base::value(0, 3) * other;
        ret.value(1, 0) = Base::value(1, 0) * other;
        ret.value(1, 1) = Base::value(1, 1) * other;
        ret.value(1, 2) = Base::value(1, 2) * other;
        ret.value(1, 3) = Base::value(1, 3) * other;
        ret.value(2, 0) = Base::value(2, 0) * other;
        ret.value(2, 1) = Base::value(2, 1) * other;
        ret.value(2, 2) = Base::value(2, 2) * other;
        ret.value(2, 3) = Base::value(2, 3) * other;
        ret.value(3, 0) = Base::value(3, 0) * other;
        ret.value(3, 1) = Base::value(3, 1) * other;
        ret.value(3, 2) = Base::value(3, 2) * other;
        ret.value(3, 3) = Base::value(3, 3) * other;

        return ret;
    }

    template<typename T>
    Matrix<T, 4, 4>& Matrix<T, 4, 4>::multAssign(const T &other)
    {
        Base::value(0, 0) *= other;
        Base::value(0, 1) *= other;
        Base::value(0, 2) *= other;
        Base::value(0, 3) *= other;
        Base::value(1, 0) *= other;
        Base::value(1, 1) *= other;
        Base::value(1, 2) *= other;
        Base::value(1, 3) *= other;
        Base::value(2, 0) *= other;
        Base::value(2, 1) *= other;
        Base::value(2, 2) *= other;
        Base::value(2, 3) *= other;
        Base::value(3, 0) *= other;
        Base::value(3, 1) *= other;
        Base::value(3, 2) *= other;
        Base::value(3, 3) *= other;

        return *this;
    }

    template<typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::transpose() const
    {
        Matrix<T, 4, 4> ret;

        ret.value(0, 0) = Base::value(0, 0);
        ret.value(0, 1) = Base::value(1, 0);
        ret.value(0, 2) = Base::value(2, 0);
        ret.value(0, 3) = Base::value(3, 0);
        ret.value(1, 0) = Base::value(0, 1);
        ret.value(1, 1) = Base::value(1, 1);
        ret.value(1, 2) = Base::value(2, 1);
        ret.value(1, 3) = Base::value(3, 1);
        ret.value(2, 0) = Base::value(0, 2);
        ret.value(2, 1) = Base::value(1, 2);
        ret.value(2, 2) = Base::value(2, 2);
        ret.value(2, 3) = Base::value(3, 2);
        ret.value(3, 0) = Base::value(0, 3);
        ret.value(3, 1) = Base::value(1, 3);
        ret.value(3, 2) = Base::value(2, 3);
        ret.value(3, 3) = Base::value(3, 3);

        return ret;
    }

    template<typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::copy() const
    {
        Matrix<T, 4, 4> ret;

        ret.value(0, 0) = Base::value(0, 0);
        ret.value(0, 1) = Base::value(0, 1);
        ret.value(0, 2) = Base::value(0, 2);
        ret.value(0, 3) = Base::value(0, 3);
        ret.value(1, 0) = Base::value(1, 0);
        ret.value(1, 1) = Base::value(1, 1);
        ret.value(1, 2) = Base::value(1, 2);
        ret.value(1, 3) = Base::value(1, 3);
        ret.value(2, 0) = Base::value(2, 0);
        ret.value(2, 1) = Base::value(2, 1);
        ret.value(2, 2) = Base::value(2, 2);
        ret.value(2, 3) = Base::value(2, 3);
        ret.value(3, 0) = Base::value(3, 0);
        ret.value(3, 1) = Base::value(3, 1);
        ret.value(3, 2) = Base::value(3, 2);
        ret.value(3, 3) = Base::value(3, 3);

        return ret;
    }

    template<typename T>
    boolean Matrix<T, 4, 4>::equal(const Matrix<T, 4, 4> &other) const
    {
        return ( Base::data() == other.data()) ||
            (   Base::value(0, 0) == other.value(0, 0) &&
                Base::value(0, 1) == other.value(0, 1) &&
                Base::value(0, 1) == other.value(0, 1) &&
                Base::value(0, 3) == other.value(0, 3) &&

                Base::value(1, 0) == other.value(1, 0) &&
                Base::value(1, 1) == other.value(1, 1) &&
                Base::value(1, 2) == other.value(1, 2) &&
                Base::value(1, 3) == other.value(1, 3) &&

                Base::value(2, 0) == other.value(2, 0) &&
                Base::value(2, 1) == other.value(2, 1) &&
                Base::value(2, 2) == other.value(2, 2) &&
                Base::value(2, 3) == other.value(2, 3) &&

                Base::value(3, 0) == other.value(3, 0) &&
                Base::value(3, 1) == other.value(3, 1) &&
                Base::value(3, 2) == other.value(3, 2) &&
                Base::value(3, 3) == other.value(3, 3));
    }

    template<typename T>
    boolean Matrix<T, 4, 4>::unequal(const Matrix &other) const
    {
        return !equal(other);
    }

    template<typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::operator + (const  Matrix<T, 4, 4> &other) const
    {
        return add(other);
    }

    template<typename T>
    Matrix<T, 4, 4>& Matrix<T, 4, 4>::operator += (const  Matrix<T, 4, 4> &other)
    {
        return addAssign(other);
    }

    template<typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::operator - (const  Matrix<T, 4, 4> &other) const
    {
        return sub(other);
    }

    template<typename T>
    Matrix<T, 4, 4>& Matrix<T, 4, 4>::operator -= (const  Matrix<T, 4, 4> &other)
    {
        return subAssign(other);
    }

    template<typename T>
    template<NOU::sizeType OC>
    Matrix<T, 4, OC> Matrix<T, 4, 4>::operator * (const Matrix<T, 4, OC> &other) const
    {
        return mult(other);
    }

    template<typename T>
    Vector<T, 4> Matrix<T, 4, 4>::operator * (const Vector<T, 4> &other) const
    {
        return mult(other);
    }

    template<typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::operator * (const T &other) const
    {
        return mult(other);
    }

    template<typename T>
    Matrix<T, 4, 4>& Matrix<T, 4, 4>::operator *= (const T &other)
    {
        return multAssign(other);
    }

    template<typename T>
    boolean Matrix<T, 4, 4>::operator == (const Matrix<T, 4, 4> &other) const
    {
        return equal(other);
    }

    template<typename T>
    boolean Matrix<T, 4, 4>::operator != (const Matrix<T, 4, 4> &other) const
    {
        return unequal(other);
    }
}

#endif