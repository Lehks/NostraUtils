#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace NOU;
using namespace NOU_CORE;
using namespace NOU_DAT_ALG;

class A
{
public:
	A() = default;
	A(const A&) = delete;
	A(A&&) = default;
};

int main()
{
	NOU::NOU_DAT_ALG::BinaryHeap<A> binH;

	binH.enqueue(A(), 5);
}