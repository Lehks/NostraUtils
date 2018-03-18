#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\math\Vec3.hpp"
#include <iostream>

using myInt = int;

int main()
{
	NOU::NOU_MATH::Vec3f vec0 = { 1.0f, 2.0f, 3.0f };
	NOU::NOU_MATH::Vec3f vec1 = { 2.0f, 3.0f, 4.0f };

	vec0 += vec1;

	std::cout << "(" << vec0.get(0) << ", " << vec0.get(1) << ", " << vec0.get(2) << ")" << std::endl;

	std::cin.get();
}