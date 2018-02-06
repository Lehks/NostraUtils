#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include <iostream>


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