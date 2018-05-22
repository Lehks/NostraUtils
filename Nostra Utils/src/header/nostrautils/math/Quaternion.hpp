#ifndef NOU_MATH_QUATERNION
#define NOU_MATH_QUATERNION

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Assertions.hpp"
#include "nostrautils/math/Utils.hpp"
#include "nostrautils/math/Vector.hpp"
#include "nostrautils/math/Matrix.hpp"

/** \file math/Quaternion.hpp
\author	 Gaetan Tayou
\since   1.0.0
\version 1.0.0

*/


namespace NOU::NOU_MATH
{




	template<typename T, sizeType N, sizeType R, sizeType C>
	class Quaternion {
	private:
		T m_x;
		T m_y;
		T m_z;
		T m_w;

	public:
		Quaternion(T x, T y, T z, T w);
		Quaternion(Vector<T, N> axis, T angle);
		Quaternion Normalized();
		Quaternion Conjugate();
		Quaternion mul(T r);
		Quaternion mul(Quaternion r);
		Quaternion mul(Vector<T, N> r);
		Quaternion sub(Quaternion r);
		Quaternion add(Quaternion r);
		Matrix<T, R, C> ToRotationMatrix();
		T dot(Quaternion r);
		Quaternion NLerp(Quaternion dest, T lerpFactor, T shortest);
		Quaternion(Matrix<T, R, C> rot);
		Vector<T, N> getForward();
		Vector<T, N> getUp();
		Vector<T, N> getBack();
		Vector<T, N> getDown();
		Vector<T, N> getLeft();
		Vector<T, N> getRight();
		T Length();
		T getM_x();
		T getM_y();
		T getM_z();
		T getM_w();
	};



	template<typename T>
	Quaternion::Quaternion(T x, T y, T z, T w) {
		m_x = x; // Initialisierung der X Axe
		m_y = y; // Initialisierung der Y Axe
		m_z = z; // Initialisierung der Z Axe
		m_w = w;  // Initialisierung der W Axe
	}

	template<typename T, sizeType N>
	Quaternion::Quaternion(Vector<T, N> axis, T angle)
	{
		T sinHalfAngle = sin(angle / 2);
		T cosHalfAngle = cos(angle / 2);

		m_x = axis.getX() * sinHalfAngle;
		m_y = axis.getY() * sinHalfAngle;
		m_z = axis.getZ() * sinHalfAngle;
		m_w = cosHalfAngle;
	};

	template<typename T>
	T Quaternion::Length()
	{
		return sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
	}

	template<typename T>
	Quaternion Quaternion::Normalized()
	{
		T length = Length();
		return  Quaternion(m_x / length, m_y / length, m_z / length, m_w / length);
	}

	template<typename T>
	Quaternion Quaternion::Conjugate()
	{
		return  Quaternion(-m_x, -m_y, -m_z, m_w);
	}

	template<typename T>
	Quaternion Quaternion::mul(T r)
	{
		return Quaternion(m_x * r, m_y * r, m_z * r, m_w * r);
	}

	template<typename T>
	Quaternion Quaternion::mul(Quaternion r)
	{
		T W = m_w * r.getM_w() - m_x * r.getM_x() - m_y * r.getM_y() - m_z * r.getM_z();
		T X = m_x * r.getM_w() + m_w * r.getM_x() + m_y * r.getM_z() - m_z * r.getM_y();
		T Y = m_y * r.getM_w() + m_w * r.getM_y() + m_z * r.getM_x() - m_x * r.getM_z();
		T Z = m_z * r.getM_w() + m_w * r.getM_z() + m_x * r.getM_y() - m_y * r.getM_x();

		return Quaternion(X, Y, Z, W);
	}

	template<typename T, sizeType N>
	Quaternion Quaternion::mul(vector<T, N> r)
	{
		T W = -m_x * r.getM_x() - m_y * r.getM_y() - m_z * r.getM_z();
		T X = m_w * r.getM_x() + m_y * r.getM_z() - m_z * r.getM_y();
		T Y = m_w * r.getM_y() + m_z * r.getM_x() - m_x * r.getM_z();
		T Z = m_w * r.getM_z() + m_x * r.getM_y() - m_y * r.getM_x();

		return  Quaternion(X, Y, Z, W);
	}


	Quaternion Quaternion::sub(Quaternion r)
	{
		return Quaternion(m_x - r.getM_x(), m_y - r.getM_y(), m_z - r.getM_z(), m_w - r.getM_w());
	}


	Quaternion Quaternion::add(Quaternion r)
	{
		return Quaternion(m_x + r.getM_x(), m_y + r.getM_y(), m_z + r.getM_z(), m_w + r.getM_w());
	}

	template<typename T, sizeType N>
	Matrix4f Quaternion::ToRotationMatrix()
	{
		Vector<T,N> forward = Vector<T, N>(2.0f * (m_x * m_z - m_w * m_y), 2.0f * (m_y * m_z + m_w * m_x), 1.0f - 2.0f * (m_x * m_x + m_y * m_y));
		Vector<T,N> up = Vector<T, N>(2.0f * (m_x * m_y + m_w * m_z), 1.0f - 2.0f * (m_x * m_x + m_z * m_z), 2.0f * (m_y * m_z - m_w * m_x));
		Vector<T,N> right = Vector<T, N>(1.0f - 2.0f * (m_y * m_y + m_z * m_z), 2.0f * (m_x * m_y - m_w * m_z), 2.0f * (m_x * m_z + m_w * m_y));

		return  Matrix4f().InitRotation(forward, up, right);
	}

	template<typename T>
	T Quaternion::dot(Quaternion r)
	{
		return m_x * r.getM_x() + m_y * r.getM_y() + m_z * r.getM_z() + m_w * r.getM_w();
	}

	template<typename T>
	Quaternion Quaternion::NLerp(Quaternion dest, T lerpFactor, T shortest)
	{
		Quaternion correctedDest = dest;

		if (shortest && dot(dest) < 0)
			correctedDest = Quaternion(-dest.getM_x(), -dest.getM_y(), -dest.getM_z(), -dest.getM_w());

		return correctedDest.sub().mul(lerpFactor).add().Normalized();
	}


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
