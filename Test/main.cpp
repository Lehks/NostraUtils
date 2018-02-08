#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\thread\ThreadManager.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace NOU;
using namespace NOU_CORE;
using namespace NOU_DAT_ALG;
using namespace NOU_THREAD;

void callback(const ErrorLocation&)
{
	__debugbreak();
}

class A
{
private:
	int i;
public:
	A() = default;
	A(int i) : i(i) {}
	A(const A&) = delete;
	A(A&&) = default;

	int get() const { return i; }
};

int main()
{
	ThreadManager& tm = ThreadManager::getInstance();


	std::cin.get();
}