#ifndef NOU_MATH_QUATERNION_HPP
#define NOU_MATH_QUATERNION_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/math/Vector.hpp"
#include "nostrautils/math/Matrix.hpp"
#include "nostrautils/math/Utils.hpp"

/** \file math/Quaternion.hpp
\author	 Lukas Reichmann
\since   1.0.2
\version 1.0.2
\brief   This file provides functionality to work with vectors.
*/

namespace NOU::NOU_MATH
{
	template<typename T>
	class Quaternion : public VectorBase<T, 4>
	{
	public:
		/**
		\brief The base type of this class.
		*/
		using Base = VectorBase<T, 4>;

		/**
		\param x The rotation around the x-axis.
		\param y The rotation around the y-axis.
		\param z The rotation around the z-axis.

		\return The passed Euler angles as quaternion.

		\brief Converts Euler angles into a quaternion.
		*/
		static Quaternion fromEuler(const T &x, const T &y, const T &z);

		/**
		\brief Constructs a new instance without initializing any of its components.
		*/
		Quaternion() = default;

		/**
		\param x The x component.
		\param y The y component.
		\param z The z component.
		\param w The w component.

		\brief Constructs a new quaternion with the passed components.
		*/
		Quaternion(const T &x, const T &y, const T &z, const T &w);

		/**
		\param vec The first two components.
		\param z The z component.
		\param w The w component.

		\brief Constructs a new quaternion with the passed components.
		*/
		Quaternion(const Vector<T, 2> &vec, const T &z, const T &w);

		/**
		\param vec The first three components.
		\param w The w component.

		\brief Constructs a new quaternion with the passed components.
		*/
		Quaternion(const Vector<T, 3> &vec, const T &w);

		/**
		\param values The four components. Must hold exactly four values.

		\brief Constructs a new quaternion with the passed components.
		*/
		Quaternion(const typename Base::InitializerList &values);

		/**
		\param vec    The first two components.
		\param values The remaining components. Must hold exactly two values.

		\brief Constructs a new quaternion with the passed components.
		*/
		Quaternion(const Vector<T, 2> &vec, const typename Base::InitializerList &values);

		/**
		\param vec    The first three components.
		\param values The remaining components. Must hold exactly one value.

		\brief Constructs a new quaternion with the passed components.
		*/
		Quaternion(const Vector<T, 3> &vec, const typename Base::InitializerList &values);


		/**
		\param vec The vector to construct the instance from.

		\brief Constructs a new quaternion from the passed vector.
		*/
		Quaternion(const Vector<T, 4> &vec);

		Matrix<T, 3, 3> toRotationMatrix() const;

		/**
		\param other The quaternion to add.

		\return A new quaternion with the added components.

		\brief Adds the components of two quaternion and returns the result in a new instance.

		\details
		Adds the components of two quaternions and returns the result in a new instance.
		*/
		Quaternion add(const Quaternion &other) const;

		/**
		\param other The vector to add.

		\return A new vector with the added components.

		\brief Adds the components of two vector and returns the result in a new instance.

		\details
		Adds the components of two vectors and returns the result in a new instance.
		*/
		Quaternion add(const Vector<T, 4> &other) const;

		/**
		\param other The quaternion to add.

		\return A reference to the quaternion that the method was called on, with the added components.

		\brief Adds the components of two quaternions and assigns the result to the quaternion that the 
		method was called on.

		\details
		Adds the components of two quaternions and assigns the result to the quaternion that the method was
		called on.
		*/
		Quaternion& addAssign(const Quaternion &other);

		/**
		\param other The vector to add.

		\return A reference to the vector that the method was called on, with the added components.

		\brief Adds the components of two vector and assigns the result to the vector that the
		method was called on.

		\details
		Adds the components of two vectors and assigns the result to the vector that the method was
		called on.
		*/
		Quaternion& addAssign(const Vector<T, 4> &other);

		/**
		\param other The quaternion to subtract.

		\return A new quaternion with the subtracted components.

		\brief Subtracts the components of two quaternions and returns the result in a new instance.

		\details
		Subtracts the components of two quaternions and returns the result in a new instance.
		*/
		Quaternion sub(const Quaternion &other) const;

		/**
		\param other The vector to subtract.

		\return A new vector with the subtracted components.

		\brief Subtracts the components of two vectors and returns the result in a new instance.

		\details
		Subtracts the components of two vectors and returns the result in a new instance.
		*/
		Quaternion sub(const Vector<T, 4> &other) const;

		/**
		\param other The quaternion to subtract.

		\return A reference to the quaternion that the method was called on, with the subtracted components.

		\brief Subtracts the components of two quaternions and assigns the result to the quaternion that the
		method was called on.

		\details
		Subtracts the components of two quaternions and assigns the result to the quaternion that the method 
		was called on.
		*/
		Quaternion& subAssign(const Quaternion &other);

		/**
		\param other The vector to subtract.

		\return A reference to the vector that the method was called on, with the subtracted components.

		\brief Subtracts the components of two vectors and assigns the result to the vector that the
		method was called on.

		\details
		Subtracts the components of two vectors and assigns the result to the vector that the method
		was called on.
		*/
		Quaternion& subAssign(const Vector<T, 4> &other);

		/**
		\param other The quaternion to multiply with.

		\return A new quaternion with the multiplied components.

		\brief Multiplies the components of two quaternions and returns the result in a new instance.

		\details
		Multiplies the components of two quaternions and returns the result in a new instance.
		*/
		Quaternion multiplyElements(const Quaternion &other) const;

		/**
		\param other The vector to multiply with.

		\return A new vector with the multiplied components.

		\brief Multiplies the components of two vectors and returns the result in a new instance.

		\details
		Multiplies the components of two vectors and returns the result in a new instance.
		*/
		Quaternion multiplyElements(const Vector<T, 4> &other) const;

		/**
		\param other The quaternion to multiply.

		\return A reference to the quaternion that the method was called on, with the multiplied components.

		\brief Multiplies the components of two quaternions and assigns the result to the quaternion that the
		method was called on.

		\details
		Multiplies the components of two quaternions and assigns the result to the quaternion that the method 
		was called on.
		*/
		Quaternion& multiplyElementsAssign(const Quaternion &other);

		/**
		\param other The vector to multiply.

		\return A reference to the vector that the method was called on, with the multiplied components.

		\brief Multiplies the components of two vectors and assigns the result to the vector that the
		method was called on.

		\details
		Multiplies the components of two vectors and assigns the result to the quaternion that the method
		was called on.
		*/
		Quaternion& multiplyElementsAssign(const Vector<T, 4> &other);

		/**
		\param other The quaternion to divide with.

		\return A new quaternion with the divided components.

		\brief Divides the components of two quaternions and returns the result in a new instance.

		\details
		Divides the components of two quaternions and returns the result in a new instance.
		*/
		Quaternion divideElements(const Quaternion &other) const;

		/**
		\param other The vector to divide with.

		\return A new vector with the divided components.

		\brief Divides the components of two vectors and returns the result in a new instance.

		\details
		Divides the components of two vectors and returns the result in a new instance.
		*/
		Quaternion divideElements(const Vector<T, 4> &other) const;

		/**
		\param other The quaternion to divide with.

		\return A reference to the quaternion that the method was called on, with the divided components.

		\brief Divides the components of two quaternions and assigns the result to the quaternion that the
		method was called on.

		\details
		Divides the components of two quaternions and assigns the result to the quaternion that the method
		was called on.
		*/
		Quaternion& divideElementsAssign(const Quaternion &other);

		/**
		\param other The vector to divide with.

		\return A reference to the vector that the method was called on, with the divided components.

		\brief Divides the components of two vector and assigns the result to the vector that the
		method was called on.

		\details
		Divides the components of two vectors and assigns the result to the vector that the method
		was called on.
		*/
		Quaternion& divideElementsAssign(const Vector<T, 4> &other);

		/**
		\param scale The scalar that the quaternion should be scaled by.

		\return A new instance with the scaled components.

		\brief Scales all of the components in the quaternion and returns the result in a new instance.

		\details
		Scales all of the components in the quaternion and returns the result in a new instance.
		*/
		Quaternion scale(float64 scale) const;

		/**
		\param scale The scalar that the quaternion should be scaled by.

		\return The instance that the method was called on, with the scaled components.

		\brief Scales all of the components in the quaternion and assigns the result to the instance that the
		method was called on.

		\details
		Scales all of the components in the quaternion and assigns the result to the instance that the method 
		was called on.
		*/
		Quaternion& scaleAssign(float64 scale);

		/**
		\param other The quaternion to calculate the dot product with.

		\return The dot product of the quaternion that the method was called on with the passed quaternion.

		\brief Calculates the dot product with the passed quaternion.

		\details
		Calculates the dot product with the passed quaternion.
		*/
		T dotProduct(const Quaternion &other) const;

		/**
		\param other The vector to calculate the dot product with.

		\return The dot product of the vector that the method was called on with the passed quaternion.

		\brief Calculates the dot product with the passed vector.

		\details
		Calculates the dot product with the passed vector.
		*/
		T dotProduct(const Vector<T, 4> &other) const;

		/**
		\return The length of the quaternion.

		\brief Returns the length of the quaternion.
		*/
		float32 length() const;

		/**
		\return An exact copy of the quaternion.

		\brief Returns an exact copy of the quaternion.
		*/
		Quaternion copy() const;

		/**
		\return The quaternion as a vector.

		\brief Converts the quaternion into a vector.
		*/
		Vector<T, 4> toVector() const;

		/**
		\param other The quaternion to compare with.

		\return True, if the quaternions are equal, false if not.

		\brief Compares two quaternions.
		*/
		boolean equal(const Quaternion &other) const;

		/**
		\param other The vector to compare with.

		\return True, if the vector are equal, false if not.

		\brief Compares two vector.
		*/
		boolean equal(const Vector<T, 4> &other) const;

		/**
		\param other The quaternion to compare with.

		\return True, if the quaternions are not equal, false if not.

		\brief Compares two quaternions.
		*/
		boolean unequal(const Quaternion &other) const;

		/**
		\param other The vector to compare with.

		\return True, if the vector are not equal, false if not.

		\brief Compares two vector.
		*/
		boolean unequal(const Vector<T, 4> &other) const;

		/**
		\return Returns the instance of the quaternion that the method was called on.

		\brief Normalizes the quaternion.

		\note
		For component types that are integer types, this method is highly imprecise.
		*/
		Quaternion& normalize();

		/**
		\return A new instance.

		\brief Inverts all of the components in the quaternion using the unary "-" operator.

		\details
		Inverts all of the components in the quaternion using the unary "-" operator.

		For a quaternion with three components, the result would be:
		\f$
		Vec_{result} =
		\begin{pmatrix}
		-this->value(0) \\
		-this->value(1) \\
		-this->value(2)
		\end{pmatrix}
		\f$
		*/
		Quaternion invert() const;

		/**
		\return The instance that this method was called on.

		\brief Inverts all of the components in the quaternion using the unary "-" operator.

		\details
		Inverts all of the components in the quaternion using the unary "-" operator.

		For a quaternion with three components, the result would be:
		\f$
		Vec_{this} =
		\begin{pmatrix}
		-this->value(0) \\
		-this->value(1) \\
		-this->value(2)
		\end{pmatrix}
		\f$
		*/
		Quaternion& invertThis();

		/**
		\return The X component.

		\brief Returns the X component.
		*/
		const T& getX() const;

		/**
		\return The X component.

		\brief Returns the X component.
		*/
		T& getX();

		/**
		\return The Y component.

		\brief Returns the Y component.
		*/
		const T& getY() const;

		/**
		\return The Y component.

		\brief Returns the Y component.
		*/
		T& getY();

		/**
		\return The Z component.

		\brief Returns the Z component.
		*/
		const T& getZ() const;

		/**
		\return The Z component.

		\brief Returns the Z component.
		*/
		T& getZ();

		/**
		\return The W component.

		\brief Returns the W component.
		*/
		const T& getW() const;

		/**
		\return The W component.

		\brief Returns the W component.
		*/
		T& getW();

		/**
		\param other The quaternion to add with.

		\return Same as <tt>add(const Quaternion &)</tt>.

		\brief Same as <tt>add(const Quaternion &)</tt>.
		*/
		Quaternion operator + (const Quaternion &other) const;

		/**
		\param other The vector to add with.

		\return Same as <tt>add(const Vector<T, 4> &)</tt>.

		\brief Same as <tt>add(const Vector<T, 4> &)</tt>.
		*/
		Quaternion operator + (const Vector<T, 4> &other) const;

		/**
		\param other The quaternion to add with.

		\return Same as <tt>addAssign(const Quaternion &)</tt>.

		\brief Same as <tt>addAssign(const Quaternion &)</tt>.
		*/
		Quaternion& operator += (const Quaternion &other);

		/**
		\param other The vector to add with.

		\return Same as <tt>addAssign(const Vector<T, 4> &)</tt>.

		\brief Same as <tt>addAssign(const Vector<T, 4> &)</tt>.
		*/
		Quaternion& operator += (const Vector<T, 4> &other);

		/**
		\param other The quaternion to subtract with.

		\return Same as <tt>sub(const Quaternion &)</tt>.

		\brief Same as <tt>sub(const Quaternion &)</tt>.
		*/
		Quaternion operator - (const Quaternion &other) const;

		/**
		\param other The vector to subtract with.

		\return Same as <tt>sub(const Vector<T, 4> &)</tt>.

		\brief Same as <tt>sub(const Vector<T, 4> &)</tt>.
		*/
		Quaternion operator - (const Vector<T, 4> &other) const;

		/**
		\param other The quaternion to subtract with.

		\return Same as <tt>subAssign(const Quaternion &)</tt>.

		\brief Same as <tt>subAssign(const Quaternion &)</tt>.
		*/
		Quaternion& operator -= (const Quaternion &other);

		/**
		\param other The vector to subtract with.

		\return Same as <tt>subAssign(const Vector<T, 4> &)</tt>.

		\brief Same as <tt>subAssign(const Vector<T, 4> &)</tt>.
		*/
		Quaternion& operator -= (const Vector<T, 4> &other);

		/**
		\param other The quaternion to calculate the dot product with.

		\return Same as <tt>dotProduct(const Quaternion &)</tt>.

		\brief Same as <tt>dotProduct(const Quaternion &)</tt>.
		*/
		T operator * (const Quaternion &other) const;

		/**
		\param other The vector to calculate the dot product with.

		\return Same as <tt>dotProduct(const Vector<T, 4> &)</tt>.

		\brief Same as <tt>dotProduct(const Vector<T, 4> &)</tt>.
		*/
		T operator * (const Vector<T, 4> &other) const;

		/**
		\param scale The scale.

		\return Same as <tt>scale(float32)</tt>.

		\brief Same as <tt>scale(float32)</tt>.
		*/
		Quaternion operator * (NOU::float32 scale) const;

		/**
		\param scale The scale.

		\return Same as <tt>scaleAssign(float32)</tt>.

		\brief Same as <tt>scaleAssign(float32)</tt>.
		*/
		Quaternion& operator *= (NOU::float32 scale);

		/**
		\return Same as <tt>invert()</tt>.

		\brief Same as <tt>invert()</tt>.
		*/
		Quaternion operator - () const;

		/**
		\param other The quaternion to compare to.

		\return Same as <tt>equal(const Quaternion &)</tt>.

		\brief Same as <tt>equal(const Quaternion &)</tt>.
		*/
		boolean operator == (const Quaternion &other) const;

		/**
		\param other The vector to compare to.

		\return Same as <tt>equal(const Vector<T, 4> &)</tt>.

		\brief Same as <tt>equal(const Vector<T, 4> &)</tt>.
		*/
		boolean operator == (const Vector<T, 4> &other) const;

		/**
		\param other The quaternion to compare to.

		\return Same as <tt>unequal(const Quaternion &)</tt>.

		\brief Same as <tt>unequal(const Quaternion &)</tt>.
		*/
		boolean operator != (const Quaternion &other) const;

		/**
		\param other The vector to compare to.

		\return Same as <tt>unequal(const Vector<T, 4> &)</tt>.

		\brief Same as <tt>unequal(const Vector<T, 4> &)</tt>.
		*/
		boolean operator != (const Vector<T, 4> &other) const;

		/**
		\return Same as <tt>toVector()</tt>.

		\brief Same as <tt>toVector()</tt>.
		*/
		operator Vector<T, 4>() const;
	};

	/**
	\tparam T The type of the components of the vector and quaternion.

	\param vec  The vector to add.
	\param quat The quaternion to add.

	\return A new vector with the added values.

	\brief Adds a quaternion to a vector and returns the result as a new instance.

	\details
	Adds a quaternion to a vector and returns the result as a new instance.

	This operator exists purely to allow for symmetric usage. It behaves in the same way that

	\code{.cpp}
	vec + quat.toVec()
	\endcode

	would behave, but it avoids the construction of a new instance that would be caused by <tt>toVec()</tt>.
	*/
	template<typename T>
	Vector<T, 4> operator + (const Vector<T, 4> &vec, const Quaternion<T> &quat);

	/**
	\tparam T The type of the components of the vector and quaternion.

	\param vec  The vector to add.
	\param quat The quaternion to add.

	\return A reference to the passed vector.

	\brief Adds a quaternion to a vector.

	\details
	Adds a quaternion to a vector.

	This operator exists purely to allow for symmetric usage. It behaves in the same way that

	\code{.cpp}
	vec += quat.toVec()
	\endcode

	would behave, but it avoids the construction of a new instance that would be caused by <tt>toVec()</tt>.
	*/
	template<typename T>
	Vector<T, 4>& operator += (const Vector<T, 4> &vec, const Quaternion<T> &quat);

	/**
	\tparam T The type of the components of the vector and quaternion.

	\param vec  The vector to subtract.
	\param quat The quaternion to subtract.

	\return A new vector with the subtracted values.

	\brief Subtracts a quaternion from a vector and returns the result as a new instance.

	\details
	Subtracts a quaternion from a vector and returns the result as a new instance.

	This operator exists purely to allow for symmetric usage. It behaves in the same way that

	\code{.cpp}
	vec - quat.toVec()
	\endcode

	would behave, but it avoids the construction of a new instance that would be caused by <tt>toVec()</tt>.
	*/
	template<typename T>
	Vector<T, 4> operator - (const Vector<T, 4> &vec, const Quaternion<T> &quat);

	/**
	\tparam T The type of the components of the vector and quaternion.

	\param vec  The vector to subtract.
	\param quat The quaternion to subtract.

	\brief Subtracts a quaternion from a vector.

	\return A reference to the passed vector.

	\details
	Subtracts a quaternion from a vector.

	This operator exists purely to allow for symmetric usage. It behaves in the same way that

	\code{.cpp}
	vec -= quat.toVec()
	\endcode

	would behave, but it avoids the construction of a new instance that would be caused by <tt>toVec()</tt>.
	*/
	template<typename T>
	Vector<T, 4>& operator -= (const Vector<T, 4> &vec, const Quaternion<T> &quat);

	/**
	\tparam T The type of the components of the vector and quaternion.

	\param vec  The vector.
	\param quat The quaternion.

	\return The cross product of the passed vector and quaternion.

	\brief Calculates the cross product of a vector and a quaternion.

	\details
	Calculates the cross product of a vector and a quaternion.

	This operator exists purely to allow for symmetric usage. It behaves in the same way that

	\code{.cpp}
	vec * quat.toVec()
	\endcode

	would behave, but it avoids the construction of a new instance that would be caused by <tt>toVec()</tt>.
	*/
	template<typename T>
	T operator * (const Vector<T, 4> &vec, const Quaternion<T> &quat);

	/**
	\tparam T The type of the components of the vector and quaternion.

	\param vec  The vector to subtract.
	\param quat The quaternion to subtract.

	\return True, if the components of the vector and quaternion are equal, false if they are not.

	\brief Subtracts a quaternion from a vector.

	\details
	Subtracts a quaternion from a vector.

	This operator exists purely to allow for symmetric usage. It behaves in the same way that

	\code{.cpp}
	vec == quat.toVec()
	\endcode

	would behave, but it avoids the construction of a new instance that would be caused by <tt>toVec()</tt>.
	*/
	template<typename T>
	boolean operator == (const Vector<T, 4> &vec, const Quaternion<T> &quat);

	/**
	\tparam T The type of the components of the vector and quaternion.

	\param vec  The vector to compare.
	\param quat The quaternion to compare.

	\return False, if the components of the vector and quaternion are equal, true if they are not.

	\brief Compares a quaternion with a vector.

	\details
	Compares a quaternion with a vector.

	This operator exists purely to allow for symmetric usage. It behaves in the same way that

	\code{.cpp}
	vec != quat.toVec()
	\endcode

	would behave, but it avoids the construction of a new instance that would be caused by <tt>toVec()</tt>.
	*/
	template<typename T>
	boolean operator != (const Vector<T, 4> &vec, const Quaternion<T> &quat);

	/**
	\brief A quaternion that uses float32 as its component type.
	*/
	using Quaternionf = Quaternion<float32>;

	/**
	\brief A quaternion that uses int32 as its component type.
	*/
	using Quaternioni = Quaternion<int32>;



	template<typename T>
	Quaternion<T> Quaternion<T>::fromEuler(const T &x, const T &y, const T &z)
	{
		T halfX = x / 2;
		T halfY = y / 2;
		T halfZ = z / 2;

		T c1 = NOU_MATH::cos(halfX);
		T c2 = NOU_MATH::cos(halfY);
		T c3 = NOU_MATH::cos(halfZ);

		T s1 = NOU_MATH::sin(halfX);
		T s2 = NOU_MATH::sin(halfY);
		T s3 = NOU_MATH::sin(halfZ);

		return Quaternion<T>(c1 * c2 * c3 - s1 * s2 * s3,
			                 s1 * s2 * c3 - c1 * c2 * s3,
			                 s1 * c2 * c3 - c1 * s2 * s3,
			                 c1 * s2 * c3 - s1 * c2 * s3);
	}

	template<typename T>
	Quaternion<T>::Quaternion(const T &x, const T &y, const T &z, const T &w)
	{
		getX() = x;
		getY() = y;
		getZ() = z;
		getW() = w;
	}

	template<typename T>
	Quaternion<T>::Quaternion(const Vector<T, 2> &vec, const T &z, const T &w)
	{
		getX() = vec.value(0);
		getY() = vec.value(1);
		getZ() = z;
		getW() = w;
	}

	template<typename T>
	Quaternion<T>::Quaternion(const Vector<T, 3> &vec, const T &w)
	{
		getX() = vec.value(0);
		getY() = vec.value(1);
		getZ() = vec.value(2);
		getW() = w;
	}

	template<typename T>
	Quaternion<T>::Quaternion(const typename Base::InitializerList &values)
	{
		NOU_ASSERT(values.size() == 4);

		getX() = values[0];
		getY() = values[1];
		getZ() = values[2];
		getW() = values[3];
	}

	template<typename T>
	Quaternion<T>::Quaternion(const Vector<T, 2> &vec, const typename Base::InitializerList &values)
	{
		NOU_ASSERT(values.size() == 2);

		getX() = vec.value(0);
		getY() = vec.value(1);
		getZ() = values[2];
		getW() = values[3];
	}

	template<typename T>
	Quaternion<T>::Quaternion(const Vector<T, 3> &vec, const typename Base::InitializerList &values)
	{
		NOU_ASSERT(values.size() == 1);

		getX() = vec.value(0);
		getY() = vec.value(1);
		getZ() = vec.value(2);
		getW() = values[3];

	}

	template<typename T>
	Quaternion<T>::Quaternion(const Vector<T, 4> &vec)
	{
		getX() = vec.value(0);
		getY() = vec.value(1);
		getZ() = vec.value(2);
		getW() = vec.value(3);
	}

	template<typename T>
	Matrix<T, 3, 3> Quaternion<T>::toRotationMatrix() const
	{
		Matrix<T, 3, 3> ret;

		ret.value(0, 0) = 1 - 2 * y * y - 2 * z * z;
		ret.value(0, 1) =     2 * x * y - 2 * z * w;
		ret.value(0, 2) =     2 * x * z + 2 * y * w;

		ret.value(1, 0) =     2 * x * y + 2 * z * w;
		ret.value(1, 1) = 1 - 2 * x * x - 2 * z * z;
		ret.value(1, 2) =     2 * y * z - 2 * x * w;

		ret.value(2, 0) =     2 * x * z - 2 * y * z;
		ret.value(2, 1) =     2 * y * z - 2 * x * w;
		ret.value(2, 2) = 1 - 2 * x * x - 2 * y * y;
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::add(const Quaternion<T> &other) const
	{
		return Vector<T, 4>(VectorBase<T, 4>::value(0) + other.value(0),
			VectorBase<T, 4>::value(1) + other.value(1),
			VectorBase<T, 4>::value(2) + other.value(2),
			VectorBase<T, 4>::value(3) + other.value(3));
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::add(const Vector<T, 4> &other) const
	{
		return Vector<T, 4>(VectorBase<T, 4>::value(0) + other.value(0), 
			VectorBase<T, 4>::value(1) + other.value(1), 
			VectorBase<T, 4>::value(2) + other.value(2),
			VectorBase<T, 4>::value(3) + other.value(3));
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::addAssign(const Quaternion<T> &other)
	{
		VectorBase<T, 4>::value(0) += other.value(0);
		VectorBase<T, 4>::value(1) += other.value(1);
		VectorBase<T, 4>::value(2) += other.value(2);
		VectorBase<T, 4>::value(3) += other.value(3);

		return *this;
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::addAssign(const Vector<T, 4> &other)
	{
		VectorBase<T, 4>::value(0) += other.value(0);
		VectorBase<T, 4>::value(1) += other.value(1);
		VectorBase<T, 4>::value(2) += other.value(2);
		VectorBase<T, 4>::value(3) += other.value(3);

		return *this;
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::sub(const Quaternion<T> &other) const
	{
		return Vector<T, 4>(VectorBase<T, 4>::value(0) - other.value(0),
			VectorBase<T, 4>::value(1) - other.value(1),
			VectorBase<T, 4>::value(2) - other.value(2),
			VectorBase<T, 4>::value(3) - other.value(3));
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::sub(const Vector<T, 4> &other) const
	{
		return Vector<T, 4>(VectorBase<T, 4>::value(0) - other.value(0), 
			VectorBase<T, 4>::value(1) - other.value(1), 
			VectorBase<T, 4>::value(2) - other.value(2),
			VectorBase<T, 4>::value(3) - other.value(3));
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::subAssign(const Quaternion<T> &other)
	{
		VectorBase<T, 4>::value(0) -= other.value(0);
		VectorBase<T, 4>::value(1) -= other.value(1);
		VectorBase<T, 4>::value(2) -= other.value(2);
		VectorBase<T, 4>::value(3) -= other.value(3);

		return *this;
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::subAssign(const Vector<T, 4> &other)
	{
		VectorBase<T, 4>::value(0) -= other.value(0);
		VectorBase<T, 4>::value(1) -= other.value(1);
		VectorBase<T, 4>::value(2) -= other.value(2);
		VectorBase<T, 4>::value(3) -= other.value(3);

		return *this;
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::multiplyElements(const Quaternion<T> &other) const
	{
		return Vector<T, 4>(VectorBase<T, 4>::value(0) * other.value(0),
			VectorBase<T, 4>::value(1) * other.value(1),
			VectorBase<T, 4>::value(2) * other.value(2),
			VectorBase<T, 4>::value(3) * other.value(3));
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::multiplyElements(const Vector<T, 4> &other) const
	{
		return Vector<T, 4>(VectorBase<T, 4>::value(0) * other.value(0), 
			VectorBase<T, 4>::value(1) * other.value(1), 
			VectorBase<T, 4>::value(2) * other.value(2),
			VectorBase<T, 4>::value(3) * other.value(3));
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::multiplyElementsAssign(const Quaternion<T> &other)
	{
		VectorBase<T, 4>::value(0) *= other.value(0);
		VectorBase<T, 4>::value(1) *= other.value(1);
		VectorBase<T, 4>::value(2) *= other.value(2);
		VectorBase<T, 4>::value(3) *= other.value(3);

		return *this;
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::multiplyElementsAssign(const Vector<T, 4> &other)
	{
		VectorBase<T, 4>::value(0) *= other.value(0);
		VectorBase<T, 4>::value(1) *= other.value(1);
		VectorBase<T, 4>::value(2) *= other.value(2);
		VectorBase<T, 4>::value(3) *= other.value(3);

		return *this;
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::divideElements(const Quaternion<T> &other) const
	{
		NOU_ASSERT(other.value(0) != 0);
		NOU_ASSERT(other.value(1) != 0);
		NOU_ASSERT(other.value(2) != 0);
		NOU_ASSERT(other.value(3) != 0);

		return Vector<T, 4>(VectorBase<T, 4>::value(0) / other.value(0), 
			VectorBase<T, 4>::value(1) / other.value(1), 
			VectorBase<T, 4>::value(2) / other.value(2),
			VectorBase<T, 4>::value(3) / other.value(3));
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::divideElements(const Vector<T, 4> &other) const
	{
		NOU_ASSERT(other.value(0) != 0);
		NOU_ASSERT(other.value(1) != 0);
		NOU_ASSERT(other.value(2) != 0);
		NOU_ASSERT(other.value(3) != 0);

		return Vector<T, 4>(VectorBase<T, 4>::value(0) / other.value(0), 
			VectorBase<T, 4>::value(1) / other.value(1), 
			VectorBase<T, 4>::value(2) / other.value(2),
			VectorBase<T, 4>::value(3) / other.value(3));
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::divideElementsAssign(const Quaternion<T> &other)
	{
		NOU_ASSERT(other.value(0) != 0);
		NOU_ASSERT(other.value(1) != 0);
		NOU_ASSERT(other.value(2) != 0);
		NOU_ASSERT(other.value(3) != 0);

		VectorBase<T, 4>::value(0) /= other.value(0);
		VectorBase<T, 4>::value(1) /= other.value(1);
		VectorBase<T, 4>::value(2) /= other.value(2);
		VectorBase<T, 4>::value(3) /= other.value(3);
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::divideElementsAssign(const Vector<T, 4> &other)
	{
		NOU_ASSERT(other.value(0) != 0);
		NOU_ASSERT(other.value(1) != 0);
		NOU_ASSERT(other.value(2) != 0);
		NOU_ASSERT(other.value(3) != 0);

		VectorBase<T, 4>::value(0) /= other.value(0);
		VectorBase<T, 4>::value(1) /= other.value(1);
		VectorBase<T, 4>::value(2) /= other.value(2);
		VectorBase<T, 4>::value(3) /= other.value(3);
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::scale(float64 scale) const
	{
		return Vector<T, 4>(static_cast<T>(VectorBase<T, 4>::value(0) * scale),
			static_cast<T>(VectorBase<T, 4>::value(1) * scale),
			static_cast<T>(VectorBase<T, 4>::value(2) * scale),
			static_cast<T>(VectorBase<T, 4>::value(3) * scale));
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::scaleAssign(float64 scale)
	{
		VectorBase<T, 4>::value(0) = static_cast<T>(VectorBase<T, 4>::value(0) * scale);
		VectorBase<T, 4>::value(1) = static_cast<T>(VectorBase<T, 4>::value(1) * scale);
		VectorBase<T, 4>::value(2) = static_cast<T>(VectorBase<T, 4>::value(2) * scale);
		VectorBase<T, 4>::value(3) = static_cast<T>(VectorBase<T, 4>::value(3) * scale);

		return *this;
	}

	template<typename T>
	T Quaternion<T>::dotProduct(const Quaternion<T> &other) const
	{
		return VectorBase<T, 4>::value(0) * other.value(0) +
			VectorBase<T, 4>::value(1) * other.value(1) +
			VectorBase<T, 4>::value(2) * other.value(2) +
			VectorBase<T, 4>::value(3) * other.value(3);
	}

	template<typename T>
	T Quaternion<T>::dotProduct(const Vector<T, 4> &other) const
	{
		return VectorBase<T, 4>::value(0) * other.value(0) + 
			VectorBase<T, 4>::value(1) * other.value(1) + 
			VectorBase<T, 4>::value(2) * other.value(2) + 
			VectorBase<T, 4>::value(3) * other.value(3);
	}

	template<typename T>
	float32 Quaternion<T>::length() const
	{
		return NOU_MATH::sqrt<float32>(float32(*this * *this));
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::copy() const
	{
		return *this;
	}

	template<typename T>
	Vector<T, 4> Quaternion<T>::toVector() const
	{
		return Vector<T, 4>(getX(), getY(), getZ(), getW());
	}

	template<typename T>
	boolean Quaternion<T>::equal(const Quaternion<T> &other) const
	{
		return VectorBase<T, 4>::data() == other.data() ||
			(VectorBase<T, 4>::value(0) == other.value(0) && VectorBase<T, 4>::value(1) == other.value(1) &&
			VectorBase<T, 4>::value(2) == other.value(2) && VectorBase<T, 4>::value(3) == other.value(3));
	}

	template<typename T>
	boolean Quaternion<T>::equal(const Vector<T, 4> &other) const
	{
		return 
			VectorBase<T, 4>::value(0) == other.value(0) && VectorBase<T, 4>::value(1) == other.value(1) &&
			VectorBase<T, 4>::value(2) == other.value(2) && VectorBase<T, 4>::value(3) == other.value(3);
	}

	template<typename T>
	boolean Quaternion<T>::unequal(const Quaternion<T> &other) const
	{
		return !equal(other);
	}

	template<typename T>
	boolean Quaternion<T>::unequal(const Vector<T, 4> &other) const
	{
		return !equal(other);
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::normalize()
	{
		*this *= 1 / length();

		return *this;
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::invert() const
	{
		Vector<T, 4> ret;

		ret.value(0) = -VectorBase<T, 4>::value(0);
		ret.value(1) = -VectorBase<T, 4>::value(1);
		ret.value(2) = -VectorBase<T, 4>::value(2);
		ret.value(3) = -VectorBase<T, 4>::value(3);

		return ret;
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::invertThis()
	{
		VectorBase<T, 4>::value(0) = -VectorBase<T, 4>::value(0);
		VectorBase<T, 4>::value(1) = -VectorBase<T, 4>::value(1);
		VectorBase<T, 4>::value(2) = -VectorBase<T, 4>::value(2);
		VectorBase<T, 4>::value(3) = -VectorBase<T, 4>::value(3);

		return *this;
	}


	template<typename T>
	const T& Quaternion<T>::getX() const
	{
		return Base::value(0);
	}

	template<typename T>
	T& Quaternion<T>::getX()
	{
		return Base::value(0);
	}

	template<typename T>
	const T& Quaternion<T>::getY() const
	{
		return Base::value(1);
	}

	template<typename T>
	T& Quaternion<T>::getY()
	{
		return Base::value(1);
	}

	template<typename T>
	const T& Quaternion<T>::getZ() const
	{
		return Base::value(2);
	}

	template<typename T>
	T& Quaternion<T>::getZ()
	{
		return Base::value(2);
	}

	template<typename T>
	const T& Quaternion<T>::getW() const
	{
		return Base::value(3);
	}

	template<typename T>
	T& Quaternion<T>::getW()
	{
		return Base::value(3);
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::operator + (const Quaternion<T> &other) const
	{
		return add(other);
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::operator + (const Vector<T, 4> &other) const
	{
		return add(other);
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::operator += (const Quaternion<T> &other)
	{
		return addAssign(other);
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::operator += (const Vector<T, 4> &other)
	{
		return addAssign(other);
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::operator - (const Quaternion<T> &other) const
	{
		return sub(other);
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::operator - (const Vector<T, 4> &other) const
	{
		return sub(other);
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::operator -= (const Quaternion<T> &other)
	{
		return subAssign(other);
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::operator -= (const Vector<T, 4> &other)
	{
		return subAssign(other);
	}

	template<typename T>
	T Quaternion<T>::operator * (const Quaternion &other) const
	{
		return dotProduct(other);
	}

	template<typename T>
	T Quaternion<T>::operator * (const Vector<T, 4> &other) const
	{
		return dotProduct(other);
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::operator * (NOU::float32 scale) const
	{
		return scale(scale);
	}

	template<typename T>
	Quaternion<T>& Quaternion<T>::operator *= (NOU::float32 scale)
	{
		return scaleAssign(scale);
	}

	template<typename T>
	Quaternion<T> Quaternion<T>::operator - () const
	{
		return invert();
	}

	template<typename T>
	boolean Quaternion<T>::operator == (const Quaternion<T> &other) const
	{
		return equal(other);
	}

	template<typename T>
	boolean Quaternion<T>::operator == (const Vector<T, 4> &other) const
	{
		return equal(other);
	}

	template<typename T>
	boolean Quaternion<T>::operator != (const Quaternion<T> &other) const
	{
		return unequal(other);
	}

	template<typename T>
	boolean Quaternion<T>::operator != (const Vector<T, 4> &other) const
	{
		return unequal(other);
	}

	template<typename T>
	Quaternion<T>::operator Vector<T, 4>() const
	{
		return toVector();
	}
}

#endif