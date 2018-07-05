  #ifndef NOU_MATH_QUATERNION
#define NOU_MATH_QUATERNION

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Assertions.hpp"
#include "nostrautils/math/Utils.hpp"
#include "nostrautils/math/Vector.hpp"
#include "nostrautils/math/Matrix.hpp"

/** \file math/Quaternion.hpp
\author	 Gaetan Tayou
/Quaternion 
/ Represents a vector that is used to encode three-dimensional physical rotations. 
\since   1.0.0
\version 1.0.0

*/


namespace NOU::NOU_MATH
{




	template<typename T, sizeType N, sizeType R, sizeType C>
	class Quaternion : public Vector<T, N> {
	public:
		//Constructs a quaternion from the specified components
		Quaternion(T &x, T &y, T &z, T &w); 

		// Creates a quaternion from the specified vector and rotation parts
		//Quaternion(Vector<T, N> &axis, T &angle); 

		Quaternion normalized();

		//Returns the conjugate of a specified quaternion
		Quaternion conjugate();

		Quaternion mul(const T &r);

		//Returns the quaternion that results from scaling all the components of a specified quaternion by a scalar factor. 
		Quaternion mul(const Quaternion &r);

		Quaternion mul(const Vector<T, 4> &r);

		Quaternion sub(const Quaternion &r);

		//Adds each element in one quaternion with its corresponding element in a second quaternion.
		//Quaternion add(const Quaternion &r);

		template<sizeType R, sizeType C>
		Matrix<T, R, C> toRotationMatrix();

		//Calculates the dot product of two quaternions
		T dot(const Quaternion &r);
		Quaternion nLerp(Quaternion dest, T lerpFactor, T shortest);
		Quaternion(Matrix<T, R, C> rot);
		Vector<T, 4> getForward();
		Vector<T, 4> getUp();
		Vector<T, 4> getBack();
		Vector<T, 4> getDown();
		Vector<T, 4> getLeft();
		Vector<T, 4> getRight();
		T Length();
		T getM_x();
		T getM_y();
		T getM_z();
		T getM_w();
	};


	/*
	\Initializes a new instance of the Quaternion class.
	*/
	template<typename T>
	Quaternion::Quaternion(T &x, T &y, T &z, T &w) {
		m_x = x; // Initialisierung der X Axe
		m_y = y; // Initialisierung der Y Axe
		m_z = z; // Initialisierung der Z Axe
		m_w = w;  // Initialisierung der W Axe
	}

	template<typename T, sizeType N>
	Quaternion::Quaternion(Vector<T, N> &axis, T &angle)
	{
		T sinHalfAngle = sin(angle / 2);
		T cosHalfAngle = cos(angle / 2);

		m_x = axis.getX() * sinHalfAngle;
		m_y = axis.getY() * sinHalfAngle;
		m_z = axis.getZ() * sinHalfAngle;
		m_w = cosHalfAngle;
	}

	/*
	\Returns the length of a quaternion;
	*/
	template<typename T>
	T Quaternion::Length()
	{
		return sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
	}

	/*
	\Returns the normal of a quaternion.
	*/
	template<typename T>
	Quaternion Quaternion::normalized()
	{
		T length = Length();
		return  Quaternion(m_x / length, m_y / length, m_z / length, m_w / length);
	}
	/*
	\Returns the conjugate of a quaternion.
	/
	\Given a quaternion (x, y, z, w),
	/the Conjugate method returns the quaternion (-x, -y, -z, w).
	*/
	template<typename T>
	Quaternion Quaternion::conjugate()
	{
		return  Quaternion(-m_x, -m_y, -m_z, m_w);
	}

	template<typename T>
	Quaternion Quaternion::mul(const T &r)
	{
		return Quaternion(m_x * r, m_y * r, m_z * r, m_w * r);
	}

	/*
	\Product of two quaternions
	/
	\The result represents the rotation m1 followed by the rotation m2 (return value = m1 * m2).
	This is done so that Multiply maintains the same semantics as Matrix,
	because unit quaternions can be considered as another way of representing rotation matrices.
	*/

	template<typename T>
	Quaternion Quaternion::mul(const Quaternion &r)
	{
		T W = m_w * r.getM_w() - m_x * r.getM_x() - m_y * r.getM_y() - m_z * r.getM_z();
		T X = m_x * r.getM_w() + m_w * r.getM_x() + m_y * r.getM_z() - m_z * r.getM_y();
		T Y = m_y * r.getM_w() + m_w * r.getM_y() + m_z * r.getM_x() - m_x * r.getM_z();
		T Z = m_z * r.getM_w() + m_w * r.getM_z() + m_x * r.getM_y() - m_y * r.getM_x();

		return Quaternion(X, Y, Z, W);
	}

	template<typename T, sizeType N>
	Quaternion Quaternion::mul(const vector<T, N> &r)
	{
		T W = -m_x * r.getM_x() - m_y * r.getM_y() - m_z * r.getM_z();
		T X = m_w * r.getM_x() + m_y * r.getM_z() - m_z * r.getM_y();
		T Y = m_w * r.getM_y() + m_z * r.getM_x() - m_x * r.getM_z();
		T Z = m_w * r.getM_z() + m_x * r.getM_y() - m_y * r.getM_x();

		return  Quaternion(X, Y, Z, W);
	}

	/*
	\Subtracts two quaternion instances.
	*/
	Quaternion Quaternion::sub(const Quaternion &r)
	{
		return Quaternion(m_x - r.getM_x(), m_y - r.getM_y(), m_z - r.getM_z(), m_w - r.getM_w());
	}

	/*
	/Adds each element in one quaternion with its corresponding element in a second quaternion.
	\
	*/
	  

	template<typename T, sizeType N>
	Matrix4f Quaternion::toRotationMatrix()
	{
		Vector<T,N> forward = Vector<T, N>(2.0f * (m_x * m_z - m_w * m_y), 2.0f * (m_y * m_z + m_w * m_x), 1.0f - 2.0f * (m_x * m_x + m_y * m_y));
		Vector<T,N> up = Vector<T, N>(2.0f * (m_x * m_y + m_w * m_z), 1.0f - 2.0f * (m_x * m_x + m_z * m_z), 2.0f * (m_y * m_z - m_w * m_x));
		Vector<T,N> right = Vector<T, N>(1.0f - 2.0f * (m_y * m_y + m_z * m_z), 2.0f * (m_x * m_y - m_w * m_z), 2.0f * (m_x * m_z + m_w * m_y));

		return  Matrix4f().InitRotation(forward, up, right);
	}

	/*
	\Returns the dot product of two quaternions.
	*/
	template<typename T>
	T Quaternion::dot(const Quaternion &r)
	{
		return m_x * r.getM_x() + m_y * r.getM_y() + m_z * r.getM_z() + m_w * r.getM_w();
	}
	/*
	\Interpolates between two quaternions, using spherical linear interpolation.

	*/
	template<typename T>
	Quaternion Quaternion::nLerp(Quaternion dest, T lerpFactor, T shortest)
	{
		Quaternion correctedDest = dest;

		if (shortest && dot(dest) < 0)
			correctedDest = Quaternion(-dest.getM_x(), -dest.getM_y(), -dest.getM_z(), -dest.getM_w());

		return correctedDest.sub().mul(lerpFactor).add().Normalized();
	}

	/*
	\Builds a quaternion with the given yaw, pitch, and roll.
	
	*/
	template<typename T, sizeType R, sizeType C>
	Quaternion::Quaternion(Matrix<T, R, C> rot)
	{
		T trace = rot.get(0, 0) + rot.get(1, 1) + rot.get(2, 2);

		if (trace > 0)
		{
			T s = 0.5f / sqrt(trace + 1.0f);
			m_w = 0.25f / s;
			m_x = (rot.get(1, 2) - rot.get(2, 1)) * s;
			m_y = (rot.get(2, 0) - rot.get(0, 2)) * s;
			m_z = (rot.get(0, 1) - rot.get(1, 0)) * s;
		}
		else
		{
			if (rot.get(0, 0) > rot.get(1, 1) && rot.get(0, 0) > rot.get(2, 2))
			{
				T s = 2.0f * sqrt(1.0f + rot.get(0, 0) - rot.get(1, 1) - rot.get(2, 2));
				m_w = (rot.get(1, 2) - rot.get(2, 1)) / s;
				m_x = 0.25f * s;
				m_y = (rot.get(1, 0) + rot.get(0, 1)) / s;
				m_z = (rot.get(2, 0) + rot.get(0, 2)) / s;
			}
			else if (rot.get(1, 1) > rot.get(2, 2))
			{
				T s = 2.0f * sqrt(1.0f + rot.get(1, 1) - rot.get(0, 0) - rot.get(2, 2));
				m_w = (rot.get(2, 0) - rot.get(0, 2)) / s;
				m_x = (rot.get(1, 0) + rot.get(0, 1)) / s;
				m_y = 0.25f * s;
				m_z = (rot.get(2, 1) + rot.get(1, 2)) / s;
			}
			else
			{
				T s = 2.0f * sqrt(1.0f + rot.get(2, 2) - rot.get(0, 0) - rot.get(1, 1));
				m_w = (rot.get(0, 1) - rot.get(1, 0)) / s;
				m_x = (rot.get(2, 0) + rot.get(0, 2)) / s;
				m_y = (rot.get(1, 2) + rot.get(2, 1)) / s;
				m_z = 0.25f * s;
			}
		}

		T length = sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
		m_x /= length;
		m_y /= length;
		m_z /= length;
		m_w /= length;
	}

	template<typename T, sizeType N>
	Vector<T, N> Quaternion::getForward()
	{
		return Vector<T, N>(0, 0, 1).rotate();
	}
	template<typename T, sizeType N>
	Vector<T, N> Quaternion::getUp()
	{
		return Vector<T, N>(0, 1, 0).rotate();
	}

	template<typename T, sizeType N>
	Vector<T, N> Quaternion::getBack()
	{
		return Vector<T, N>(0, 0, -1).rotate();
	}

	template<typename T, sizeType N>
	Vector<T, N> Quaternion::getDown()
	{
		return Vector<T, N>(0, -1, 0).rotate();
	}

	template<typename T, sizeType N>
	Vector<T, N> Quaternion::getLeft()
	{
		return Vector<T, N>(-1, 0, 0).rotate();
	}

	template<typename T, sizeType N>
	Vector<T, N> Quaternion::getRight()
	{
		return Vector<T, N>(1, 0, 0).rotate();
	}
	template<typename T>
	T Quaternion::getM_x()
	{
		return m_x;
	}

	template<typename T>
	T Quaternion::getM_y()
	{
		return m_y;
	}

	template<typename T>
	T Quaternion::getM_z()
	{
		return m_z;
	}

	template<typename T>
	T Quaternion::getM_w()
	{
		return m_w;
	}




}

#endif
