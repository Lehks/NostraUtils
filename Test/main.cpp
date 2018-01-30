#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"

#include <iostream>

using namespace NOU;
using namespace NOU_DAT_ALG;

int main()
{
	class A
	{
	public:
		A() = default;
		A(const A&) = delete;
		A(A&&) = default;
	};

	A a;

	Vector<A> v;
}