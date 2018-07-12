#ifndef NOU_MATH_VECTOR
#define NOU_MATH_VECTOR

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Assertions.hpp"
#include "nostrautils/math/Utils.hpp"
#include "Matrix.hpp"

#include <initializer_list>

/** \file math/Vector.hpp
\author	 Lukas Reichmann
\since   1.0.0
\version 1.0.0
\brief   This file provides functionality to work with vectors.
*/

namespace NOU::NOU_MATH
{
	/**
	\tparam T The type of the components in the vector.
	\tparam N The amount of components that the vector has.

	\brief The base class of all vector types.

	\details
	The base class of all vector types. This class provides the storage for the vectors and access to that 
	storage.
	*/
	template<typename T, sizeType N>
	class VectorBase
	{
		static_assert(N > 1, "A vector can not have 0 or 1 rows.");

	private:
		/*
		/Vector Quaternion components.
		\x, y, w, z
		*/
		T x;
		T y;
		T z;
		T w;


    public:
        using InitializerList = std::initializer_list<T>;

    protected:
		/**
		\brief The single components.
		*/
        T m_data[N];

		/**
		\brief Constructs a new instance without initializing any of the components.
		*/
        VectorBase() = default;

		/**
		\param values The values of the components.

		\brief Initializes all of the components in the vector with the passed values.

		\details
		Initializes all of the components in the vector with the passed values.

		Sonstruct of initializer lists:

		\code{.cpp}
		{1, 2, 3}
		\endcode

		would result in such a vector:

		\f$
		\begin{pmatrix}
		1 \\ 2 \\ 3
		\end{pmatrix}
		\f$
		*/
        VectorBase(const InitializerList &values);

    public:
		/**
		\param index The index of the component.

		\return The value of the component at the specified index.

		\brief Returns the value of the component at the specified index.

		\note
		Typically, the components in a vector have names like \f$x\f$ or \f$y\f$. The vector does not provide
		names like that, but the indices are meant like this: index 0 is \f$x\f$, index 1 is \f$y\f$ and so 
		on.
		*/
        const T& value(sizeType index) const;

		/**
		\param index The index of the component.

		\return The value of the component at the specified index.

		\brief Returns the value of the component at the specified index.

		\note
		Typically, the components in a vector have names like \f$x\f$ or \f$y\f$. The vector does not provide
		names like that, but the indices are meant like this: index 0 is \f$x\f$, index 1 is \f$y\f$ and so
		on.
		*/
        T& value(sizeType index);

		/**
		\return The amount of components in the vector. This is the same as the template parameter \p N.

		\brief Returns the amount of components in the vector.
		*/
        sizeType size() const;

		/**
		\return The data of the vector as an array.

		\brief Returns the data of the vector as an array.
		*/
        const T* data() const;

		/**
		\return The data of the vector as an array.

		\brief Returns the data of the vector as an array.
		*/
        T* data();

		/**
		\param index The index of the component.

		\return Same as <tt>value()</tt>.

		\brief Same as <tt>value()</tt>.
		*/
		const T& operator [](sizeType index) const;

		/**
		\param index The index of the component.

		\return Same as <tt>value()</tt>.

		\brief Same as <tt>value()</tt>.
		*/
		T& operator [](sizeType index);
    };

	template<typename T, sizeType N>
	class Vector : public VectorBase<T, N>
	{
	public:
		/**
		\return The null vector.

		\brief Returns the null vector.
		*/
		static Vector nullVector();

		/**
		\brief Constructs a new instance without initializing any of its components.
		*/
        Vector() = default;

		/**
		\param values The values of the components.

		\brief Initializes all of the components in the vector with the passed values.

		\details
		Initializes all of the components in the vector with the passed values.

		Sonstruct of initializer lists:

		\code{.cpp}
		{1, 2, 3}
		\endcode

		would result in such a vector:

		\f$
		\begin{pmatrix}
		1 \\ 2 \\ 3
		\end{pmatrix}
		\f$
		*/
        Vector(const typename VectorBase<T, N>::InitializerList &values);

		/**
		\param vec    A vector that contains the first two values.
		\param values The values of the remaining components.

		\brief Initializes all of the components in the vector with the passed values.

		\details
		Initializes all of the components in the vector with the passed values.

		Sonstruct of initializer lists:

		\code{.cpp}
		Vector<int32, 6>(Vec2i(1, 2), {3, 4, 5, 6})
		\endcode

		would result in such a vector:

		\f$
		\begin{pmatrix}
		1 \\ 2 \\ 3 \\ 4 \\ 5 \\ 6
		\end{pmatrix}
		\f$
		*/
        Vector(const Vector<T, 2> &vec, const typename VectorBase<T, N>::InitializerList &values);

		/**
		\param vec    A vector that contains the first three values.
		\param values The values of the remaining components.

		\brief Initializes all of the components in the vector with the passed values.

		\details
		Initializes all of the components in the vector with the passed values.

		Sonstruct of initializer lists:

		\code{.cpp}
		Vector<int32, 6>(Vec3i(1, 2, 3), {4, 5, 6})
		\endcode

		would result in such a vector:

		\f$
		\begin{pmatrix}
		1 \\ 2 \\ 3 \\ 4 \\ 5 \\ 6
		\end{pmatrix}
		\f$
		*/
        Vector(const Vector<T, 3> &vec, const typename VectorBase<T, N>::InitializerList &values);

		/**
		\param vec    A vector that contains the first four values.
		\param values The values of the remaining components.

		\brief Initializes all of the components in the vector with the passed values.

		\details
		Initializes all of the components in the vector with the passed values.

		Sonstruct of initializer lists:

		\code{.cpp}
		Vector<int32, 6>(Vec2i(1, 2, 3, 4), {5, 6})
		\endcode

		would result in such a vector:

		\f$
		\begin{pmatrix}
		1 \\ 2 \\ 3 \\ 4 \\ 5 \\ 6
		\end{pmatrix}
		\f$
		*/
        Vector(const Vector<T, 4> &vec, const typename VectorBase<T, N>::InitializerList &values);

		/**
		\param other The vector to add.

		\return A new vector with the added components.

		\brief Adds the components of two vectors and returns the result in a new instance.

		\details
		Adds the components of two vectors and returns the result in a new instance.

		For a vector with three components, the result would be:
		\f$
		Vec_{result} =
		\begin{pmatrix}
		this->value(0) + other.value(0) \\
		this->value(1) + other.value(1) \\
		this->value(2) + other.value(2)
		\end{pmatrix}
		\f$
		*/
        Vector add(const Vector &other) const;

		/**
		\param other The vector to add.

		\return A reference to the vector that the method was called on, with the added components.

		\brief Adds the components of two vectors and assigns the result to the vector that the method was 
		       called on.

		\details
		Adds the components of two vectors and assigns the result to the vector that the method was
		called on.

		For a vector with three components, the result would be:
		\f$
		Vec_{this} =
		\begin{pmatrix}
		this->value(0) + other.value(0) \\
		this->value(1) + other.value(1) \\
		this->value(2) + other.value(2)
		\end{pmatrix}
		\f$
		*/
        Vector& addAssign(const Vector &other);

		/**
		\param other The vector to subtract.

		\return A new vector with the subtracted components.

		\brief Subtracts the components of two vectors and returns the result in a new instance.

		\details
		Subtracts the components of two vectors and returns the result in a new instance.

		For a vector with three components, the result would be:
		\f$
		Vec_{result} =
		\begin{pmatrix}
		this->value(0) - other.value(0) \\
		this->value(1) - other.value(1) \\
		this->value(2) - other.value(2)
		\end{pmatrix}
		\f$
		*/
        Vector sub(const Vector &other) const;

		/**
		\param other The vector to subtract.

		\return A reference to the vector that the method was called on, with the subtracted components.

		\brief Subtracts the components of two vectors and assigns the result to the vector that the method 
		       was called on.

		\details
		Subtracts the components of two vectors and assigns the result to the vector that the method was 
		called on.

		For a vector with three components, the result would be:
		\f$
		Vec_{this} =
		\begin{pmatrix}
		this->value(0) - other.value(0) \\
		this->value(1) - other.value(1) \\
		this->value(2) - other.value(2)
		\end{pmatrix}
		\f$
		*/
        Vector& subAssign(const Vector &other);

		/**
		\param other The vector to multiply with.

		\return A new vector with the multiplied components.

		\brief Multiplies the components of two vectors and returns the result in a new instance.

		\details
		Multiplies the components of two vectors and returns the result in a new instance.

		For a vector with three components, the result would be:
		\f$
		Vec_{result} =
		\begin{pmatrix}
		this->value(0) * other.value(0) \\
		this->value(1) * other.value(1) \\
		this->value(2) * other.value(2)
		\end{pmatrix}
		\f$
		*/
        Vector multiplyElements(const Vector &other) const;

		/**
		\param other The vector to multiply.

		\return A reference to the vector that the method was called on, with the multiplied components.

		\brief Multiplies the components of two vectors and assigns the result to the vector that the method 
		       was called on.

		\details
		Multiplies the components of two vectors and assigns the result to the vector that the method was 
		called on.

		For a vector with three components, the result would be:
		\f$
		Vec_{this} =
		\begin{pmatrix}
		this->value(0) * other.value(0) \\
		this->value(1) * other.value(1) \\
		this->value(2) * other.value(2)
		\end{pmatrix}
		\f$
		*/
        Vector& multiplyElementsAssign(const Vector &other);

		/**
		\param other The vector to divide with.

		\return A new vector with the divided components.

		\brief Divides the components of two vectors and returns the result in a new instance.

		\details
		Divides the components of two vectors and returns the result in a new instance.

		For a vector with three components, the result would be:
		\f$
		Vec_{result} =
		\begin{pmatrix}
		this->value(0) \ other.value(0) \\
		this->value(1) \ other.value(1) \\
		this->value(2) \ other.value(2)
		\end{pmatrix}
		\f$
		*/
        Vector divideElements(const Vector &other) const;

		/**
		\param other The vector to divide with.

		\return A reference to the vector that the method was called on, with the divided components.

		\brief Divides the components of two vectors and assigns the result to the vector that the method was 
		       called on.

		\details
		Divides the components of two vectors and assigns the result to the vector that the method was called 
		on.
		
		For a vector with three components, the result would be:

		\f$
		Vec_{this} =
		\begin{pmatrix}
		this->value(0) \ other.value(0) \\
		this->value(1) \ other.value(1) \\
		this->value(2) \ other.value(2)
		\end{pmatrix}
		\f$
		*/
        Vector& divideElementsAssign(const Vector &other);

		/**
		\param scale The scalar that the vector should be scaled by.

		\return A new instance with the scaled components.

		\brief Scales all of the components in the vector and returns the result in a new instance.

		\details
		Scales all of the components in the vector and returns the result in a new instance.

		For a vector with three components, the result would be:
		\f$
		Vec_{return} =
		\begin{pmatrix}
		this->value(0) * other \\
		this->value(1) * other \\
		this->value(2) * other
		\end{pmatrix}
		\f$
		*/
        Vector scale(float64 scale) const;

		/**
		\param scale The scalar that the vector should be scaled by.

		\return The instance that the method was called on, with the scaled components.

		\brief Scales all of the components in the vector and assigns the result to the instance that the 
		       method was called on.

		\details
		Scales all of the components in the vector and assigns the result to the instance that the method was 
		called on.

		For a vector with three components, the result would be:
		\f$
		Vec_{this} =
		\begin{pmatrix}
		this->value(0) * other \\
		this->value(1) * other \\
		this->value(2) * other
		\end{pmatrix}
		\f$
		*/
        Vector& scaleAssign(float64 scale);

		/**
		\param other The vector to calculate the dot product with.

		\return The dot product of the vector that the method was called on with the passed vector.

		\brief Calculates the dot product with the passed vector.

		\details
		Calculates the dot product with the passed vector.

		For a vector with three components, the result would be:
		\f$
		ret =
		this->value(0) * other.value(0) +
		this->value(1) * other.value(1) +
		this->value(2) * other.value(2)
		\f$
		*/
        T dotProduct(const Vector &other) const;

		/**
		\return The length of the vector.

		\brief Returns the length of the vector.
		*/
        float32 length() const;

		/**
		\return An exact copy of the vector.

		\brief Returns an exact copy of the vector.
		*/
        Vector copy() const;

		/**
		\param other The vector to compare with.

		\return True, if the vectors are equal, false if not.

		\brief Compares two vectors.
		*/
        boolean equal(const Vector &other) const;

		/**
		\param other The vector to compare with.

		\return True, if the vectors are not equal, false if not.

		\brief Compares two vectors.
		*/
        boolean unequal(const Vector &other) const;

		/**
		\return Returns the instance of the vector that the method was called on.

		\brief Normalizes the vector.

		\note
		For component types that are integer types, this method is highly imprecise.
		*/
        Vector& normalize();

		/**
		\return A new instance.

		\brief Inverts all of the components in the vector using the unary "-" operator.

		\details
		Inverts all of the components in the vector using the unary "-" operator.

		For a vector with three components, the result would be:
		\f$
		Vec_{result} =
		\begin{pmatrix}
		-this->value(0) \\
		-this->value(1) \\
		-this->value(2)
		\end{pmatrix}
		\f$
		*/
        Vector invert() const;

		/**
		\return The instance that this method was called on.

		\brief Inverts all of the components in the vector using the unary "-" operator.

		\details
		Inverts all of the components in the vector using the unary "-" operator.

		For a vector with three components, the result would be:
		\f$
		Vec_{this} =
		\begin{pmatrix}
		-this->value(0) \\
		-this->value(1) \\
		-this->value(2)
		\end{pmatrix}
		\f$
		*/
        Vector& invertThis();

		/**
		\param other The vector to add with.

		\return Same as <tt>add()</tt>.

		\brief Same as <tt>add()</tt>.
		*/
        Vector operator + (const Vector &other) const;

		/**
		\param other The vector to add with.

		\return Same as <tt>addAssign()</tt>.

		\brief Same as <tt>addAssign()</tt>.
		*/
        Vector& operator += (const Vector &other);

		/**
		\param other The vector to subtract with.

		\return Same as <tt>sub()</tt>.

		\brief Same as <tt>sub()</tt>.
		*/
        Vector operator - (const Vector &other) const;

		/**
		\param other The vector to subtract with.

		\return Same as <tt>subAssign()</tt>.

		\brief Same as <tt>subAssign()</tt>.
		*/
        Vector& operator -= (const Vector &other);

		/**
		\param other The vector to calculate the dot product with.

		\return Same as <tt>dotProduct()</tt>.

		\brief Same as <tt>dotProduct()</tt>.
		*/
        T operator * (const Vector &other) const;

		/**
		\param scale The scale.

		\return Same as <tt>scale()</tt>.

		\brief Same as <tt>scale()</tt>.
		*/
        Vector operator * (NOU::float32 scale) const;

		/**
		\param scale The scale.

		\return Same as <tt>scaleAssign()</tt>.

		\brief Same as <tt>scaleAssign()</tt>.
		*/
        Vector& operator *= (NOU::float32 scale);

		/**
		\return Same as <tt>invert()</tt>.

		\brief Same as <tt>invert()</tt>.
		*/
        Vector operator - () const;

		/**
		\param other The vector to compare to.

		\return Same as <tt>equal()</tt>.

		\brief Same as <tt>equal()</tt>.
		*/
        boolean operator == (const Vector &other) const;

		/**
		\param other The vector to compare to.

		\return Same as <tt>unequal()</tt>.

		\brief Same as <tt>unequal()</tt>.
		*/
        boolean operator != (const Vector &other) const;
    };

	///\cond

	template<typename T>
	class Vector<T, 2> : public VectorBase<T, 2>
	{
	public:
		static Vector nullVector();

        Vector() = default;
        Vector(const T &x, const T &y);
        Vector(const typename VectorBase<T, 2>::InitializerList &values);

        Vector add(const Vector &other) const;
        Vector& addAssign(const Vector &other);

        Vector sub(const Vector &other) const;
        Vector& subAssign(const Vector &other);

        Vector multiplyElements(const Vector &other) const;
        Vector& multiplyElementsAssign(const Vector &other);

        Vector divideElements(const Vector &other) const;
        Vector& divideElementsAssign(const Vector &other);

        Vector scale(float64 scale) const;
        Vector& scaleAssign(float64 scale);
        T dotProduct(const Vector &other) const;

        float32 length() const;

        Vector copy() const;

        boolean equal(const Vector &other) const;

        boolean unequal(const Vector &other) const;

        Vector& normalize();

        Vector invert() const;
        Vector& invertThis();

        Vector operator + (const Vector &other) const;
        Vector& operator += (const Vector &other);

        Vector operator - (const Vector &other) const;
        Vector& operator -= (const Vector &other);

        T operator * (const Vector &other) const;
        Vector operator * (NOU::float32 scale) const;
        Vector& operator *= (NOU::float32 scale);

        Vector operator - () const;

        boolean operator == (const Vector &other) const;
        boolean operator != (const Vector &other) const;
    };

	template<typename T>
	class Vector<T, 3> : public VectorBase<T, 3>
	{
	public:
		static Vector nullVector();

        Vector() = default;
        Vector(const T &x, const T &y, const T &z);
        Vector(const Vector<T, 2> &vec, const T &z);
        Vector(const typename VectorBase<T, 3>::InitializerList &values);
        Vector(const Vector<T, 2> &vec, const typename VectorBase<T, 3>::InitializerList &values);

        Vector add(const Vector &other) const;
        Vector& addAssign(const Vector &other);

        Vector sub(const Vector &other) const;
        Vector& subAssign(const Vector &other);

        Vector multiplyElements(const Vector &other) const;
        Vector& multiplyElementsAssign(const Vector &other);

        Vector divideElements(const Vector &other) const;
        Vector& divideElementsAssign(const Vector &other);

        Vector scale(float64 scale) const;
        Vector& scaleAssign(float64 scale);

        T dotProduct(const Vector &other) const;
        Vector crossProduct(const Vector &other) const;

        float32 length() const;

        Vector copy() const;

        boolean equal(const Vector &other) const;

        boolean unequal(const Vector &other) const;

        Vector& normalize();

        Vector invert() const;
        Vector& invertThis();

        Vector operator + (const Vector &other) const;
        Vector& operator += (const Vector &other);

        Vector operator - (const Vector &other) const;
        Vector& operator -= (const Vector &other);

        T operator * (const Vector &other) const;
        Vector operator * (NOU::float32 scale) const;
        Vector& operator *= (NOU::float32 scale);

        Vector operator - () const;

        boolean operator == (const Vector &other) const;
        boolean operator != (const Vector &other) const;
    };

	template<typename T>
	class Vector<T, 4> : public VectorBase<T, 4>
	{
	private:
		/*
		/Vector Quaternion components.
		\x, y, w, z
		*/
		T x;
		T y;
		T z;
		T w;
	public:
		static Vector nullVector();

        Vector() = default;

        Vector(const T &x, const T &y, const T &z, const T &w);

        Vector(const Vector<T, 2> &vec, const T &z, const T &w);
        Vector(const Vector<T, 3> &vec, const T &w);
        Vector(const typename VectorBase<T, 4>::InitializerList &values);
        Vector(const Vector<T, 2> &vec, const typename VectorBase<T, 4>::InitializerList &values);
        Vector(const Vector<T, 3> &vec, const typename VectorBase<T, 4>::InitializerList &values);

        Vector add(const Vector &other) const;
        Vector& addAssign(const Vector &other);

        Vector sub(const Vector &other) const;
        Vector& subAssign(const Vector &other);

        Vector multiplyElements(const Vector &other) const;
        Vector& multiplyElementsAssign(const Vector &other);

        Vector divideElements(const Vector &other) const;
        Vector& divideElementsAssign(const Vector &other);

        Vector scale(float64 scale) const;
        Vector& scaleAssign(float64 scale);

        T dotProduct(const Vector &other) const;

        float32 length() const;

        Vector copy() const;

        boolean equal(const Vector &other) const;

        boolean unequal(const Vector &other) const;

        Vector& normalize();

        Vector invert() const;
        Vector& invertThis();

        Vector operator + (const Vector &other) const;
        Vector& operator += (const Vector &other);

        Vector operator - (const Vector &other) const;
        Vector& operator -= (const Vector &other);

        T operator * (const Vector &other) const;
        Vector operator * (NOU::float32 scale) const;
        Vector& operator *= (NOU::float32 scale);

        Vector operator - () const;

        boolean operator == (const Vector &other) const;
        boolean operator != (const Vector &other) const;
/*
		T getX();
		T getY();
		T getZ();
		T getW();
		Vector(Vector axis, T angle);

		Vector<T, 4> nLerp(Vector<T, 4> dest, T lerpFactor, bool shortest);

		Matrix<T, 4, 4> toRotationMatrix();

		Vector getForward();
		Vector getUp();
		Vector getBack();
		Vector getDown();
		Vector getLeft();
		Vector getRight();
*/
    };

	///endcond

/*
	template<typename T>
	Vector<T, 4>::Vector<T, 4> (T x, T y, T z, T w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	template<typename T>
	Vector<T, 4> Vector<T, 4>::nLerp(Vector<T, 4> dest, T lerpFactor, bool shortest)
	{
		Vector<T, 4> correctedDest = dest;

		if (shortest && dot(dest) < 0)
			correctedDest = Vector<T, 4>(-dest.getX(), -det.getY(), -det.getZ(); -det.getW());

		return correctedDest.sub().multiplyElements(lerpFactor).add().normalize();
	}

	template<typename T>
	Matrix<T, 4, 4> Vector<T, 4>::toRotationMatrix()
	{
		Vector<T, 4> forward = Vector<T, 4>(2.0f *((x * z) - (w * y)), 2.0f * ((y * z) + (w * x)), 1.0f - 2.0f *((x * x) + (y * y));
		Vector<T, 4> up = Vector<T, 4>(2.0f *((x * y) + (w * z)), 1.0f -2.0f * ((x * x) + (z * z)), 2.0f *((y * z) - (w * x));
		Vector<T, 4> right = Vector<T, 4>(1.0f - 2.0f *((y * y) + (z * z)), 2.0f * ((x * y) - (w * z)), 2.0f *((x * z) + (w * y));

		//return Matrix<T, 4, 4>.u
	}

	template<typename T>
	Vector<T, 4>::Vector(Vector<T, 4> axis, T angle)
	{
		T sinHalfAngle = sin(angle / 2);
		T cosHalfAngle = cos(angle / 2);

		x = axis.getX() * sinHalfAngle;
		y = axis.getY() * sinHalfAngle;
		z = axis.getZ() * sinHalfAngle;
		w = cosHalfAngle;
	}

	template<typename T>
	Vector<T, 3> Vector<T, 3>::getForward()
	{
		return Vector<T, 3>(0, 0, 1).rotate(this);
	}

	template<typename T>
	Vector<T, 3> Vector<T, 3>::getBack()
	{
		return Vector<T, 3>(0, 0, -1).rotate(this);
	}

	template<typename T>
	Vector<T, 3> Vector<T, 3>::getUp()
	{
		return Vector<T, 3>(0, 1, 0).rotate(this);
	}

	template<typename T>
	Vector<T, 3> Vector<T, 3>::getDown()
	{
		return Vector<T, 3>(0, -1, 0).rotate(this);
	}

	template<typename T>
	Vector<T, 3> Vector<T, 3>::getRight()
	{
		return Vector<T, 3>(1, 0, 0).rotate(this);
	}

	template<typename T>
	Vector<T, 3> Vector<T, 3>::getLeft()
	{
		return Vector<T, 3>(-1, 0, 0).rotate(this);
	}

	template<typename T>
	Vector<T, 4>::getX()
	{
		return x;
	}

	template<typename T>
	Vector<T, 4>::getY()
	{
		return y;
	}

	template<typename T>
	Vector<T, 4>::getZ()
	{
		return z;
	}

	template<typename T>
	Vector<T, 4>::getW()
	{
		return w;
	}
	*/
	
	

	/**
	\tparam N The amount of components in the vector.

	\brief A vector that uses NOU::float32 as its component type and the passed size. 
	*/
    template<sizeType N>
    using Vecf = Vector<float32, N>;

	/**
	\tparam N The amount of components in the vector.

	\brief A vector that uses NOU::int32 as its component type and the passed size.
	*/
    template<sizeType N>
    using Veci = Vector<int32, N>;

	/**
	\brief A vector that uses NOU::float32 as its component type and has a size of 2.
	*/
    using Vec2 = Vecf<2>;

	/**
	\brief A vector that uses NOU::float32 as its component type and has a size of 3.
	*/
    using Vec3 = Vecf<3>;

	/**
	\brief A vector that uses NOU::float32 as its component type and has a size of 4.
	*/
    using Vec4 = Vecf<4>;

	/**
	\brief A vector that uses NOU::int32 as its component type and has a size of 2.
	*/
    using Vec2i = Veci<2>;

	/**
	\brief A vector that uses NOU::int32 as its component type and has a size of 3.
	*/
    using Vec3i = Veci<3>;

	/**
	\brief A vector that uses NOU::int32 as its component type and has a size of 4.
	*/
    using Vec4i = Veci<4>;

	///cond

    template<typename T, sizeType N>
    VectorBase<T, N>::VectorBase(const InitializerList &values)
    {
        NOU_ASSERT(values.size() == size());

        sizeType index = 0;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            m_data[index] = *i;
            index++;
        }
    }

    template<typename T, sizeType N>
    const T& VectorBase<T, N>::value(sizeType index) const
    {
        NOU_ASSERT(index < size());

        return m_data[index];
    }

    template<typename T, sizeType N>
    T& VectorBase<T, N>::value(sizeType index)
    {
        NOU_ASSERT(index < size());

        return m_data[index];
    }

    template<typename T, sizeType N>
    sizeType  VectorBase<T, N>::size() const
    {
        return N;
    }

    template<typename T, sizeType N>
    const T* VectorBase<T, N>::data() const
    {
        return m_data;
    }

    template<typename T, sizeType N>
    T* VectorBase<T, N>::data()
    {
        return m_data;
    }

	template<typename T, sizeType N>
	const T& VectorBase<T, N>::operator[](sizeType index) const
	{
		return value(index);
	}

	template<typename T, sizeType N>
	T& VectorBase<T, N>::operator[](sizeType index)
	{
		return value(index);
	}



    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::nullVector()
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < N; i++)
        {
            ret.value(i) = 0;
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>::Vector(const typename VectorBase<T, N>::InitializerList &values) :
        VectorBase<T, N>(values)
    {}

    template<typename T, sizeType N>
    Vector<T, N>::Vector(const Vector<T, 2> &vec, const typename VectorBase<T, N>::InitializerList &values)
    {
        NOU_ASSERT(values.size() == VectorBase<T, N>::size() - 2);

        VectorBase<T, N>::value(0) = vec.value(0);
        VectorBase<T, N>::value(1) = vec.value(1);

        sizeType index = 2;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            VectorBase<T, N>::value(index++) = *i;
        }
    }

    template<typename T, sizeType N>
    Vector<T, N>::Vector(const Vector<T, 3> &vec, const typename VectorBase<T, N>::InitializerList &values)
    {
        NOU_ASSERT(values.size() == this->size() - 3); //this-> is required here

        VectorBase<T, N>::value(0) = vec.value(0);
        VectorBase<T, N>::value(1) = vec.value(1);
        VectorBase<T, N>::value(2) = vec.value(2);

        sizeType index = 3;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            VectorBase<T, N>::value(index++) = *i;
        }
    }

    template<typename T, sizeType N>
    Vector<T, N>::Vector(const Vector<T, 4> &vec, const typename VectorBase<T, N>::InitializerList &values)
    {
        NOU_ASSERT(values.size() == this->size() - 4); //this-> is required here

        VectorBase<T, N>::value(0) = vec.value(0);
        VectorBase<T, N>::value(1) = vec.value(1);
        VectorBase<T, N>::value(2) = vec.value(2);
        VectorBase<T, N>::value(3) = vec.value(3);

        sizeType index = 4;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            VectorBase<T, N>::value(index++) = *i;
        }
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::add(const Vector<T, N> &other) const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            ret.value(i) = VectorBase<T, N>::value(i) + other.value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::addAssign(const Vector<T, N> &other)
    {
        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            VectorBase<T, N>::value(i) += other.value(i);
        }

        return *this;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::sub(const Vector<T, N> &other) const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            ret.value(i) = VectorBase<T, N>::value(i) - other.value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::subAssign(const Vector<T, N> &other)
    {
        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            VectorBase<T, N>::value(i) -= other.value(i);
        }

        return *this;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::multiplyElements(const Vector<T, N> &other) const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            ret.value(i) = VectorBase<T, N>::value(i) * other.value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::multiplyElementsAssign(const Vector<T, N> &other)
    {
        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            VectorBase<T, N>::value(i) *= other.value(i);
        }

        return *this;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::divideElements(const Vector<T, N> &other) const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            NOU_ASSERT(other.value(i) != 0);

            ret.value(i) = VectorBase<T, N>::value(i) / other.value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::divideElementsAssign(const Vector<T, N> &other)
    {
        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            NOU_ASSERT(other.value(i) != 0);

            VectorBase<T, N>::value(i) /= other.value(i);
        }

        return *this;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::scale(float64 scale) const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            ret.value(i) = static_cast<T>(VectorBase<T, N>::value(i) * scale);
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::scaleAssign(float64 scale)
    {
        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            VectorBase<T, N>::value(i) = static_cast<T>(VectorBase<T, N>::value(i) * scale);
        }

        return *this;
    }

    template<typename T, sizeType N>
    T Vector<T, N>::dotProduct(const Vector<T, N> &other) const
    {
        //do this outside the loop to avoid having to initialize ret with 0 
        //(which might not work for any type)
        T ret = VectorBase<T, N>::value(0) * other.value(0); 

        for (sizeType i = 1; i < VectorBase<T, N>::size(); i++)
        {
            ret += VectorBase<T, N>::value(i) * other.value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    float32 Vector<T, N>::length() const
    {
        return NOU_MATH::sqrt<float32>(static_cast<float32>(*this * *this));
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::copy() const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            ret.value(i) = VectorBase<T, N>::value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    boolean Vector<T, N>::equal(const Vector<T, N> &other) const
    {
        if (VectorBase<T, N>::data() == other.VectorBase<T, N>::data())
            return true;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            if (VectorBase<T, N>::value(i) != other.value(i))
                return false;
        }

        return true;
    }

    template<typename T, sizeType N>
    boolean Vector<T, N>::unequal(const Vector<T, N> &other) const
    {
        return !equal(other);
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::normalize()
    {
        *this *= 1 / length();

        return *this;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::invert() const
    {
        Vector<T, N> ret;

        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            ret.value(i) = -VectorBase<T, N>::value(i);
        }

        return ret;
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::invertThis()
    {
        for (sizeType i = 0; i < VectorBase<T, N>::size(); i++)
        {
            VectorBase<T, N>::value(i) = -VectorBase<T, N>::value(i);
        }

        return *this;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::operator + (const Vector<T, N> &other) const
    {
        return add(other);
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::operator += (const Vector<T, N> &other)
    {
        return addAssign(other);;
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::operator - (const Vector<T, N> &other) const
    {
        return sub(other);
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::operator -= (const Vector<T, N> &other)
    {
        return subAssign(other);
    }

    template<typename T, sizeType N>
    T Vector<T, N>::operator * (const Vector<T, N> &other) const
    {
        return dotProduct(other);
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::operator * (NOU::float32 scale) const
    {
        return this->scale(scale);
    }

    template<typename T, sizeType N>
    Vector<T, N>& Vector<T, N>::operator *= (NOU::float32 scale)
    {
        return scaleAssign(scale);
    }

    template<typename T, sizeType N>
    Vector<T, N> Vector<T, N>::operator - () const
    {
        return invert();
    }

    template<typename T, sizeType N>
    boolean Vector<T, N>::operator == (const Vector<T, N> &other) const
    {
        return equal(other);
    }

    template<typename T, sizeType N>
    boolean Vector<T, N>::operator != (const Vector<T, N> &other) const
    {
        return unequal(other);
    }





    template<typename T>
    Vector<T, 2> Vector<T, 2>::nullVector()
    {
        return Vector<T, 2>(0, 0);
    }

    template<typename T>
    Vector<T, 2>::Vector(const T &x, const T &y)
    {
        VectorBase<T, 2>::value(0) = x;
        VectorBase<T, 2>::value(1) = y;
    }

    template<typename T>
    Vector<T, 2>::Vector(const typename VectorBase<T, 2>::InitializerList &values) :
        VectorBase<T, 2>(values)
    {}

    template<typename T>
    Vector<T, 2> Vector<T, 2>::add(const Vector<T, 2> &other) const
    {
        return Vector<T, 2>(VectorBase<T, 2>::value(0) + other.value(0), VectorBase<T, 2>::value(1) + other.value(1));
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::addAssign(const Vector<T, 2> &other)
    {
        VectorBase<T, 2>::value(0) += other.value(0);
        VectorBase<T, 2>::value(1) += other.value(1);

        return *this;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::sub(const Vector<T, 2> &other) const
    {
        return Vector<T, 2>(VectorBase<T, 2>::value(0) - other.value(0), VectorBase<T, 2>::value(1) - other.value(1));
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::subAssign(const Vector<T, 2> &other)
    {
        VectorBase<T, 2>::value(0) -= other.value(0);
        VectorBase<T, 2>::value(1) -= other.value(1);

        return *this;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::multiplyElements(const Vector<T, 2> &other) const
    {
        return Vector<T, 2>(VectorBase<T, 2>::value(0) * other.value(0), VectorBase<T, 2>::value(1) * other.value(1));
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::multiplyElementsAssign(const Vector<T, 2> &other)
    {
        VectorBase<T, 2>::value(0) *= other.value(0);
        VectorBase<T, 2>::value(1) *= other.value(1);

        return *this;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::divideElements(const Vector<T, 2> &other) const
    {
        NOU_ASSERT(other.value(0) != 0);
        NOU_ASSERT(other.value(1) != 0);

        return Vector<T, 2>(VectorBase<T, 2>::value(0) / other.value(0), VectorBase<T, 2>::value(1) / other.value(1));
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::divideElementsAssign(const Vector<T, 2> &other)
    {
        NOU_ASSERT(other.value(0) != 0);
        NOU_ASSERT(other.value(1) != 0);

        VectorBase<T, 2>::value(0) /= other.value(0);
        VectorBase<T, 2>::value(1) /= other.value(1);

        return *this;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::scale(float64 scale) const
    {
        return Vector<T, 2>(static_cast<T>(VectorBase<T, 2>::value(0) * scale), 
			static_cast<T>(VectorBase<T, 2>::value(1) * scale));
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::scaleAssign(float64 scale)
    {
        VectorBase<T, 2>::value(0) = static_cast<T>(VectorBase<T, 2>::value(0) * scale);
		VectorBase<T, 2>::value(1) = static_cast<T>(VectorBase<T, 2>::value(1) * scale);

        return *this;
    }

    template<typename T>
    T Vector<T, 2>::dotProduct(const Vector<T, 2> &other) const
    {
        return VectorBase<T, 2>::value(0) * other.value(0) + VectorBase<T, 2>::value(1) * other.value(1);
    }

    template<typename T>
    float32 Vector<T, 2>::length() const
    {
        return NOU_MATH::sqrt<float32>(float32(*this * *this));
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::copy() const
    {
        return Vector<T, 2>(VectorBase<T, 2>::value(0), VectorBase<T, 2>::value(1));
    }

    template<typename T>
    boolean Vector<T, 2>::equal(const Vector<T, 2> &other) const
    {
        return VectorBase<T, 2>::data() == other.VectorBase<T, 2>::data() || (VectorBase<T, 2>::value(0) == other.value(0) && VectorBase<T, 2>::value(1) == other.value(1));
    }

    template<typename T>
    boolean Vector<T, 2>::unequal(const Vector<T, 2> &other) const
    {
        return !equal(other);
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::normalize()
    {
        *this *= 1.0f / length();

        return *this;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::invert() const
    {
        Vector<T, 2> ret;

        ret.value(0) = -VectorBase<T, 2>::value(0);
        ret.value(1) = -VectorBase<T, 2>::value(1);

        return ret;
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::invertThis()
    {
        VectorBase<T, 2>::value(0) = -VectorBase<T, 2>::value(0);
        VectorBase<T, 2>::value(1) = -VectorBase<T, 2>::value(1);

        return *this;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::operator + (const Vector<T, 2> &other) const
    {
        return add(other);
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::operator += (const Vector<T, 2> &other)
    {
        return addAssign(other);;
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::operator - (const Vector<T, 2> &other) const
    {
        return sub(other);
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::operator -= (const Vector<T, 2> &other)
    {
        return subAssign(other);
    }

    template<typename T>
    T Vector<T, 2>::operator * (const Vector<T, 2> &other) const
    {
        return dotProduct(other);
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::operator * (NOU::float32 scale) const
    {
        return this->scale(scale);
    }

    template<typename T>
    Vector<T, 2>& Vector<T, 2>::operator *= (NOU::float32 scale)
    {
        return scaleAssign(scale);
    }

    template<typename T>
    Vector<T, 2> Vector<T, 2>::operator - () const
    {
        return invert();
    }

    template<typename T>
    boolean Vector<T, 2>::operator == (const Vector<T, 2> &other) const
    {
        return equal(other);
    }

    template<typename T>
    boolean Vector<T, 2>::operator != (const Vector<T, 2> &other) const
    {
        return unequal(other);
    }





    template<typename T>
    Vector<T, 3> Vector<T, 3>::nullVector()
    {
        return Vector<T, 3>(0, 0, 0);
    }

    template<typename T>
    Vector<T, 3>::Vector(const T &x, const T &y, const T &z)
    {
        VectorBase<T, 3>::value(0) = x;
        VectorBase<T, 3>::value(1) = y;
        VectorBase<T, 3>::value(2) = z;
    }

    template<typename T>
    Vector<T, 3>::Vector(const Vector<T, 2> &vec, const T &z) :
        Vector<T, 3>(vec.value(0), vec.value(1), z)
    {}

    template<typename T>
    Vector<T, 3>::Vector(const typename VectorBase<T, 3>::InitializerList &values) :
        VectorBase<T, 3>(values)
    {}

    template<typename T>
    Vector<T, 3>::Vector(const Vector<T, 2> &vec, const typename VectorBase<T, 3>::InitializerList &values)
    {
        NOU_ASSERT(values.size() == 1);

        VectorBase<T, 3>::value(0) = vec.value(0);
        VectorBase<T, 3>::value(1) = vec.value(1);

        sizeType index = 2;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            VectorBase<T, 3>::value(index++) = *i;
        }
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::add(const Vector<T, 3> &other) const
    {
        return Vector<T, 3>(VectorBase<T, 3>::value(0) + other.value(0), VectorBase<T, 3>::value(1) + other.value(1), VectorBase<T, 3>::value(2) + other.value(2));
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::addAssign(const Vector<T, 3> &other)
    {
         VectorBase<T, 3>::value(0) += other.value(0);
         VectorBase<T, 3>::value(1) += other.value(1);
         VectorBase<T, 3>::value(2) += other.value(2);

        return *this;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::sub(const Vector<T, 3> &other) const
    {
        return Vector<T, 3>(VectorBase<T, 3>::value(0) - other.value(0), VectorBase<T, 3>::value(1) - other.value(1), VectorBase<T, 3>::value(2) - other.value(2));
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::subAssign(const Vector<T, 3> &other)
    {
        VectorBase<T, 3>::value(0) -= other.value(0);
        VectorBase<T, 3>::value(1) -= other.value(1);
        VectorBase<T, 3>::value(2) -= other.value(2);

        return *this;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::multiplyElements(const Vector<T, 3> &other) const
    {
        return Vector<T, 3>(VectorBase<T, 3>::value(0) * other.value(0), VectorBase<T, 3>::value(1) * other.value(1), VectorBase<T, 3>::value(2) * other.value(2));
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::multiplyElementsAssign(const Vector<T, 3> &other)
    {
        VectorBase<T, 3>::value(0) *= other.value(0);
        VectorBase<T, 3>::value(1) *= other.value(1);
        VectorBase<T, 3>::value(2) *= other.value(2);

        return *this;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::divideElements(const Vector<T, 3> &other) const
    {
        NOU_ASSERT(other.value(0) != 0);
        NOU_ASSERT(other.value(1) != 0);
        NOU_ASSERT(other.value(2) != 0);

        return Vector<T, 3>(VectorBase<T, 3>::value(0) / other.value(0), VectorBase<T, 3>::value(1) / other.value(1), VectorBase<T, 3>::value(2) / other.value(2));
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::divideElementsAssign(const Vector<T, 3> &other)
    {
        NOU_ASSERT(other.value(0) != 0);
        NOU_ASSERT(other.value(1) != 0);
        NOU_ASSERT(other.value(2) != 0);

        VectorBase<T, 3>::value(0) /= other.value(0);
        VectorBase<T, 3>::value(1) /= other.value(1);
        VectorBase<T, 3>::value(2) /= other.value(2);

        return *this;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::scale(float64 scale) const
    {
        return Vector<T, 3>(static_cast<T>(VectorBase<T, 3>::value(0) * scale), 
			static_cast<T>(VectorBase<T, 3>::value(1) * scale), 
			static_cast<T>(VectorBase<T, 3>::value(2) * scale));
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::scaleAssign(float64 scale)
    {
        VectorBase<T, 3>::value(0) = static_cast<T>(VectorBase<T, 3>::value(0) * scale);
		VectorBase<T, 3>::value(1) = static_cast<T>(VectorBase<T, 3>::value(1) * scale);
		VectorBase<T, 3>::value(2) = static_cast<T>(VectorBase<T, 3>::value(2) * scale);

        return *this;
    }

    template<typename T>
    T Vector<T, 3>::dotProduct(const Vector<T, 3> &other) const
    {
        return VectorBase<T, 3>::value(0) * other.value(0) + VectorBase<T, 3>::value(1) * other.value(1) + VectorBase<T, 3>::value(2) * other.value(2);
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::crossProduct(const Vector<T, 3> &other) const
    {
        return Vector<T, 3>(
                VectorBase<T, 3>::value(1) * other.value(2) - VectorBase<T, 3>::value(2) * other.value(1),
                VectorBase<T, 3>::value(2) * other.value(0) - VectorBase<T, 3>::value(0) * other.value(2),
                VectorBase<T, 3>::value(0) * other.value(1) - VectorBase<T, 3>::value(1) * other.value(0));
    }

    template<typename T>
    float32 Vector<T, 3>::length() const
    {
        return NOU_MATH::sqrt<float32>(float32(*this * *this));
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::copy() const
    {
        return Vector<T, 3>(VectorBase<T, 3>::value(0), VectorBase<T, 3>::value(1), VectorBase<T, 3>::value(2));
    }

    template<typename T>
    boolean Vector<T, 3>::equal(const Vector<T, 3> &other) const
    {
        return VectorBase<T, 3>::data() == other.VectorBase<T, 3>::data() || (VectorBase<T, 3>::value(0) == other.value(0) && VectorBase<T, 3>::value(1) == other.value(1) 
            && VectorBase<T, 3>::value(2) == other.value(2));
    }

    template<typename T>
    boolean Vector<T, 3>::unequal(const Vector<T, 3> &other) const
    {
        return !equal(other);
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::normalize()
    {
        *this *= 1 / length();

        return *this;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::invert() const
    {
        Vector<T, 3> ret;

        ret.value(0) = -VectorBase<T, 3>::value(0);
        ret.value(1) = -VectorBase<T, 3>::value(1);
        ret.value(2) = -VectorBase<T, 3>::value(2);

        return ret;
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::invertThis()
    {
        VectorBase<T, 3>::value(0) = -VectorBase<T, 3>::value(0);
        VectorBase<T, 3>::value(1) = -VectorBase<T, 3>::value(1);
        VectorBase<T, 3>::value(2) = -VectorBase<T, 3>::value(2);

        return *this;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::operator + (const Vector<T, 3> &other) const
    {
        return add(other);
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::operator += (const Vector<T, 3> &other)
    {
        return addAssign(other);;
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::operator - (const Vector<T, 3> &other) const
    {
        return sub(other);
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::operator -= (const Vector<T, 3> &other)
    {
        return subAssign(other);
    }

    template<typename T>
    T Vector<T, 3>::operator * (const Vector<T, 3> &other) const
    {
        return dotProduct(other);
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::operator * (NOU::float32 scale) const
    {
        return this->scale(scale);
    }

    template<typename T>
    Vector<T, 3>& Vector<T, 3>::operator *= (NOU::float32 scale)
    {
        return scaleAssign(scale);
    }

    template<typename T>
    Vector<T, 3> Vector<T, 3>::operator - () const
    {
        return invert();
    }

    template<typename T>
    boolean Vector<T, 3>::operator == (const Vector<T, 3> &other) const
    {
        return equal(other);
    }

    template<typename T>
    boolean Vector<T, 3>::operator != (const Vector<T, 3> &other) const
    {
        return unequal(other);
    }





    template<typename T>
    Vector<T, 4> Vector<T, 4>::nullVector()
    {
        return Vector<T, 4>(0, 0, 0, 0);
    }

    template<typename T>
    Vector<T, 4>::Vector(const T &x, const T &y, const T &z, const T &w)
    {
        VectorBase<T, 4>::value(0) = x;
        VectorBase<T, 4>::value(1) = y;
        VectorBase<T, 4>::value(2) = z;
        VectorBase<T, 4>::value(3) = w;
    }

    template<typename T>
    Vector<T, 4>::Vector(const Vector<T, 2> &vec, const T &z, const T &w)
    {
        VectorBase<T, 4>::value(0) = vec.value(0);
        VectorBase<T, 4>::value(1) = vec.value(1);
        VectorBase<T, 4>::value(2) = z;
        VectorBase<T, 4>::value(3) = w;
    }

    template<typename T>
    Vector<T, 4>::Vector(const Vector<T, 3> &vec, const T &w)
    {
        VectorBase<T, 4>::value(0) = vec.value(0);
        VectorBase<T, 4>::value(1) = vec.value(1);
        VectorBase<T, 4>::value(2) = vec.value(2);
        VectorBase<T, 4>::value(3) = w;
    }

    template<typename T>
    Vector<T, 4>::Vector(const typename VectorBase<T, 4>::InitializerList &values) :
        VectorBase<T, 4>(values)
    {}

    template<typename T>
    Vector<T, 4>::Vector(const Vector<T, 2> &vec, const typename VectorBase<T, 4>::InitializerList &values)
    {
        NOU_ASSERT(values.size() == 2);

        VectorBase<T, 4>::value(0) = vec.value(0);
        VectorBase<T, 4>::value(1) = vec.value(1);

        sizeType index = 2;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            VectorBase<T, 4>::value(index++) = *i;
        }
    }

    template<typename T>
    Vector<T, 4>::Vector(const Vector<T, 3> &vec, const typename VectorBase<T, 4>::InitializerList &values)
    {
        NOU_ASSERT(values.size() == 1);

        VectorBase<T, 4>::value(0) = vec.value(0);
        VectorBase<T, 4>::value(1) = vec.value(1);
        VectorBase<T, 4>::value(2) = vec.value(2);

        sizeType index = 3;

        for (auto i = values.begin(); i != values.end(); i++)
        {
            VectorBase<T, 4>::value(index++) = *i;
        }
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::add(const Vector<T, 4> &other) const
    {
        return Vector<T, 4>(VectorBase<T, 4>::value(0) + other.value(0), VectorBase<T, 4>::value(1) + other.value(1), VectorBase<T, 4>::value(2) + other.value(2), 
            VectorBase<T, 4>::value(3) + other.value(3));
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::addAssign(const Vector<T, 4> &other)
    {
        VectorBase<T, 4>::value(0) += other.value(0);
        VectorBase<T, 4>::value(1) += other.value(1);
        VectorBase<T, 4>::value(2) += other.value(2);
        VectorBase<T, 4>::value(3) += other.value(3);

        return *this;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::sub(const Vector<T, 4> &other) const
    {
        return Vector<T, 4>(VectorBase<T, 4>::value(0) - other.value(0), VectorBase<T, 4>::value(1) - other.value(1), VectorBase<T, 4>::value(2) - other.value(2), 
            VectorBase<T, 4>::value(3) - other.value(3));
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::subAssign(const Vector<T, 4> &other)
    {
        VectorBase<T, 4>::value(0) -= other.value(0);
        VectorBase<T, 4>::value(1) -= other.value(1);
        VectorBase<T, 4>::value(2) -= other.value(2);
        VectorBase<T, 4>::value(3) -= other.value(3);

        return *this;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::multiplyElements(const Vector<T, 4> &other) const
    {
        return Vector<T, 4>(VectorBase<T, 4>::value(0) * other.value(0), VectorBase<T, 4>::value(1) * other.value(1), VectorBase<T, 4>::value(2) * other.value(2), 
            VectorBase<T, 4>::value(3) * other.value(3));
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::multiplyElementsAssign(const Vector<T, 4> &other)
    {
        VectorBase<T, 4>::value(0) *= other.value(0);
        VectorBase<T, 4>::value(1) *= other.value(1);
        VectorBase<T, 4>::value(2) *= other.value(2);
        VectorBase<T, 4>::value(3) *= other.value(3);

        return *this;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::divideElements(const Vector<T, 4> &other) const
    {
        NOU_ASSERT(other.value(0) != 0);
        NOU_ASSERT(other.value(1) != 0);
        NOU_ASSERT(other.value(2) != 0);
        NOU_ASSERT(other.value(3) != 0);

        return Vector<T, 4>(VectorBase<T, 4>::value(0) / other.value(0), VectorBase<T, 4>::value(1) / other.value(1), VectorBase<T, 4>::value(2) / other.value(2), 
            VectorBase<T, 4>::value(3) / other.value(3));
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::divideElementsAssign(const Vector<T, 4> &other)
    {
        NOU_ASSERT(other.value(0) != 0);
        NOU_ASSERT(other.value(1) != 0);
        NOU_ASSERT(other.value(2) != 0);
        NOU_ASSERT(other.value(3) != 0);

        VectorBase<T, 4>::value(0) /= other.value(0);
        VectorBase<T, 4>::value(1) /= other.value(1);
        VectorBase<T, 4>::value(2) /= other.value(2);
        VectorBase<T, 4>::value(3) /= other.value(3);

        return *this;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::scale(float64 scale) const
    {
        return Vector<T, 4>(static_cast<T>(VectorBase<T, 4>::value(0) * scale), 
			static_cast<T>(VectorBase<T, 4>::value(1) * scale), 
			static_cast<T>(VectorBase<T, 4>::value(2) * scale), 
			static_cast<T>(VectorBase<T, 4>::value(3) * scale));
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::scaleAssign(float64 scale)
    {
        VectorBase<T, 4>::value(0) = static_cast<T>(VectorBase<T, 4>::value(0) * scale);
		VectorBase<T, 4>::value(1) = static_cast<T>(VectorBase<T, 4>::value(1) * scale);
		VectorBase<T, 4>::value(2) = static_cast<T>(VectorBase<T, 4>::value(2) * scale);
		VectorBase<T, 4>::value(3) = static_cast<T>(VectorBase<T, 4>::value(3) * scale);

        return *this;
    }

    template<typename T>
    T Vector<T, 4>::dotProduct(const Vector<T, 4> &other) const
    {
        return VectorBase<T, 4>::value(0) * other.value(0) + VectorBase<T, 4>::value(1) * other.value(1) + VectorBase<T, 4>::value(2) * other.value(2)
            + VectorBase<T, 4>::value(3) * other.value(3);
    }

    template<typename T>
    float32 Vector<T, 4>::length() const
    {
        return NOU_MATH::sqrt<float32>(float32(*this * *this));
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::copy() const
    {
        return Vector<T, 4>(VectorBase<T, 4>::value(0), VectorBase<T, 4>::value(1), VectorBase<T, 4>::value(2), VectorBase<T, 4>::value(3));
    }

    template<typename T>
    boolean Vector<T, 4>::equal(const Vector<T, 4> &other) const
    {
        return VectorBase<T, 4>::data() == other.data() || (VectorBase<T, 4>::value(0) == other.value(0) && VectorBase<T, 4>::value(1) == other.value(1) && 
            VectorBase<T, 4>::value(2) == other.value(2) && VectorBase<T, 4>::value(3) == other.value(3));
    }

    template<typename T>
    boolean Vector<T, 4>::unequal(const Vector<T, 4> &other) const
    {
        return !equal(other);
    } 

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::normalize()
    {
        *this *= 1 / length();

        return *this;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::invert() const
    {
        Vector<T, 4> ret;

        ret.value(0) = -VectorBase<T, 4>::value(0);
        ret.value(1) = -VectorBase<T, 4>::value(1);
        ret.value(2) = -VectorBase<T, 4>::value(2);
        ret.value(3) = -VectorBase<T, 4>::value(3);

        return ret;
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::invertThis()
    {
        VectorBase<T, 4>::value(0) = -VectorBase<T, 4>::value(0);
        VectorBase<T, 4>::value(1) = -VectorBase<T, 4>::value(1);
        VectorBase<T, 4>::value(2) = -VectorBase<T, 4>::value(2);
        VectorBase<T, 4>::value(3) = -VectorBase<T, 4>::value(3);

        return *this;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::operator + (const Vector<T, 4> &other) const
    {
        return add(other);
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::operator += (const Vector<T, 4> &other)
    {
        return addAssign(other);;
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::operator - (const Vector<T, 4> &other) const
    {
        return sub(other);
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::operator -= (const Vector<T, 4> &other)
    {
        return subAssign(other);
    }

    template<typename T>
    T Vector<T, 4>::operator * (const Vector<T, 4> &other) const
    {
        return dotProduct(other);
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::operator * (NOU::float32 scale) const
    {
        return this->scale(scale);
    }

    template<typename T>
    Vector<T, 4>& Vector<T, 4>::operator *= (NOU::float32 scale)
    {
        return scaleAssign(scale);
    }

    template<typename T>
    Vector<T, 4> Vector<T, 4>::operator - () const
    {
        return invert();
    }

    template<typename T>
    boolean Vector<T, 4>::operator == (const Vector<T, 4> &other) const
    {
        return equal(other);
    }

    template<typename T>
    boolean Vector<T, 4>::operator != (const Vector<T, 4> &other) const
    {
        return unequal(other);
    }

	

	///\endcond

}

#endif