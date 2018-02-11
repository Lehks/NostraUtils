#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\math\Vec3.hpp"
#include <iostream>
#include <initializer_list>

int main()
{
//	std::initializer_list<float> il = { 0.1f, 0.2f };
	NOU::NOU_MATH::Vec3f vec = { 1.0f, 0.5f, 0.25f };
	NOU::NOU_MATH::Vec3f vec1 = { 1.0f, 0.5f, 0.25f };
	NOU::NOU_MATH::Vec3i vec0 = { 1, 0, 0 };

	auto vec2 = vec + vec1;
}