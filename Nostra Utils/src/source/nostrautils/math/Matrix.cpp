#include "nostrauils/math/Matrix.cpp"
#include "nostrauils/math/Utils.cpp"

namespace NOU::NOU_MATH
{
	namespace Matrices
	{
		Mat4 scale(float32 x, float32 y, float32 z)
		{
			return Mat4(
				   x, 0.0f, 0.0f, 0.0f,
				0.0f,    y, 0.0f, 0.0f,
				0.0f, 0.0f,    z, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}

		Mat4 translate(float32 x, float32 y, float32 z)
		{
			return Mat4(
				1.0f, 0.0f, 0.0f, x,
				0.0f, 1.0f, 0.0f, y,
				0.0f, 0.0f, 1.0f, z,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}
			
		Mat4 rotate(float32 angle, float32 x, float32 y, float32 z)
		{
			float32 sinA = sin(angle);
			float32 cosA = cos(angle);

			return Mat4(
				(x * x) * (1 - cosA) + (    cosA), (x * y) * (1 - cosA) - (z * sinA), (x * z) * (1 - cosA) + (y * sinA), 0.0f,
				(y * x) * (1 - cosA) + (z * sinA), (y * y) * (1 - cosA) + (    cosA), (y * z) * (1 - cosA) - (x * sinA), 0.0f,
				(z * x) * (1 - cosA) - (y * sinA), (z * y) * (1 - cosA) + (x * sinA), (z * z) * (1 - cosA) + (    cosA), 0.0f,
				                             0.0f,                              0.0f,                              0.0f, 1.0f
			);
		}

		Mat4 ortho();
		Mat4 perspective();
		Mat4 lookAt();
	}
}