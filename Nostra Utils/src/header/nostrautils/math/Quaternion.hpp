  #ifndef NOU_MATH_QUATERNION
#define NOU_MATH_QUATERNION

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/Assertions.hpp"
#include "nostrautils/math/Utils.hpp"
//#include "nostrautils/math/Vector.hpp"
//#include "nostrautils/math/Matrix.hpp"

/**
\file math/Quaternion.hpp
\author	 Gaetan Tayou
/Quaternion 
/ Represents a vector that is used to encode three-dimensional physical rotations. 
\since   1.0.0
\version 1.0.0
**/

namespace NOU::NOU_MATH
{
	template<typename T>
	class Quaternion : public Vector<T, 4>
	{
	public:

		Quaternion rotate(Vector axis, T angle) const;
		Quaternion nLerp(Vector dest, T lerpFactor, bool shortest) const;
		Quaternion getForward();
		Quaternion getUp();
		Quaternion getBack();
		Quaternion getDown();
		Quaternion getLeft();
		Quaternion getRight();
	};

	template<typename T>
	Quaternion &Quaternion::rotate(Vector<T, 4> axis, T angle) const
	{
		T sinHalfAngle = sin(angle / 2);
		T cosHalfAngle = cos(angle / 2);

		T VectorBase<T, 4>::value(0) = axis.vec.value(0) * sinHalfAngle;
		T VectorBase<T, 4>::value(1) = axis.vec.value(1) * sinHalfAngle;
		T VectorBase<T, 4>::value(2) = axis.vec.value(2) * sinHalfAngle;
		T VectorBase<T, 4>::value(3) = cosHalfAngle;

		Quaternion* rotation = new Quaternion(VectorBase<T, 4>::value(0), VectorBase<T, 4>::value(1), VectorBase<T, 4>::value(2), VectorBase<T, 4>::value(3));
		Quaternion conjugate = rotation.conjugate();

		Quaternion w = rotation.mul(*this).mul(conjugate);

		VectorBase<T, 4>::value(0) = w.vec.value(0);
		VectorBase<T, 4>::value(1) = w.vec.value(1);
		VectorBase<T, 4>::value(2) = w.vec.value(2);

		return *this;


	}
	
	template<typename T>
	Quaternion Quaternion::nLerp(Vector<T, 4> dest, T lerpFactor, bool shortest) const
	{
		Vector<T, 4> correctedDest = dest;

		if (shortest && dot(dest) < 0)
			correctedDest = Vector<T, 4>(-dest.vec.value(0), -det.vec.value(1), -det.vec.value(2); -det.vec.value(3));

		return correctedDest.sub().multiplyElements(lerpFactor).add().normalize();
	}

	template<typename T>
	Quaternion Quaternion::getForward()
	{
		return Quaternion(0, 0, 1).rotate(this);
	}

	template<typename T>
	Quaternion Quaternion::getDown()
	{
		return Quaternion(0, -1, 0).rotate(this);
	}

	template<typename T>
	Quaternion Quaternion::getUp()
	{
		return Quaternion(0, 1, 0).rotate(this);
	}

	template<typename T>
	Quaternion Quaternion::getBack()
	{
		return Quaternion(0, 0, -1).rotate(this);
	}

	template<typename T>
	Quaternion Quaternion::getRight()
	{
		return Quaternion(1, 0, 0).rotate(this);
	}

	template<typename T>
	Quaternion Quaternion::getLeft()
	{
		return Quaternion(-1, 0, 0).rotate(this);
	}

}


#endif
