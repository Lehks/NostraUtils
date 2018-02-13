#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\math\Vec.hpp"
#include <iostream>
#include <initializer_list>

void test()
{
	//	std::initializer_list<float> il = { 0.1f, 0.2f };
	NOU::NOU_MATH::Vecf vec = { 1.0f, 0.5f, 0.25f };
	NOU::NOU_MATH::Vecf vec1 = { 1.0f, 0.5f, 0.25f };
	NOU::NOU_MATH::Veci vec0 = { 1, 0, 0 };

	auto vec2 = vec + vec1;
}


int main()
{
	test();


}