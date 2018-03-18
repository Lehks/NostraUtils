#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\math\Vec.hpp"
#include "nostrautils\math\Utils.hpp"
#include <iostream>
#include <initializer_list>

void test()
{
	auto res = NOU::NOU_MATH::pow(3.0, 2.0);

	std::cout << res << std::endl;

	

	//	std::initializer_list<float> il = { 0.1f, 0.2f };
	NOU::NOU_MATH::Vecf vec = { 1.0f, 0.5f, 0.25f };
	NOU::NOU_MATH::Vecf vec1 = { 1.0f, 0.5f, 0.25f };
	NOU::NOU_MATH::Veci vec0 = { 1, 0, 0 };

	auto vec2 = vec + vec1;

	std::cin.get();
}


int main()
{
	test();


}