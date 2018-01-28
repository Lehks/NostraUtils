#ifndef NOU_DAT_MATH_VEC3_HPP
#define NOU_DAT_MATH_VEC3_HPP

#include "nostrautils\core\StdIncludes.hpp"

namespace NOU::NOU_MATH
{
	class NOU_CLASS Vec3 
	{
		public:
			float32 m_data[3];

		public:
			Vec3(float32 x, float32 y, float32 z);
			Vec3 add(const Vec3 & vec);
			Vec3 sub(const Vec3 & vec);
			Vec3 mult(const Vec3 & vec);
		    Vec3 div(const Vec3 & vec);

			Vec3 operator + (const Vec3 & vec);
	};
}

#endif
