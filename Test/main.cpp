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
	//ErrorHandler::setCallback(callback);

	NOU::NOU_DAT_ALG::BinaryHeap<A> binH(true);

	binH.enqueue(A(5), 5);
	binH.enqueue(A(1), 1);
	binH.enqueue(A(3), 3);
	binH.enqueue(A(6), 6);

	while (getErrorHandler().getErrorCount() != 0)
		std::cout << "->" << getErrorHandler().popError().getName() << std::endl;

	while (binH.size() != 0)
	{
		std::cout << binH.get().get() << std::endl;
		binH.dequeue();
	}

	while (getErrorHandler().getErrorCount() != 0)
		std::cout << "=>" << getErrorHandler().popError().getName() << std::endl;

	std::cout << "\n" << std::endl;

	auto priority5 = binH.enqueue(A(5), 5);
	auto priority1 = binH.enqueue(A(1), 1);
	auto priority3 = binH.enqueue(A(3), 3);
	auto priority6 = binH.enqueue(A(6), 6);


	binH.decreaseKey(priority3, 0);

	sizeType i = 0;

	while (binH.size() != 0)
	{
		std::cout << binH.get().get();
		std::cout << " " << binH.priorityNAt(i) << std::endl;
		binH.dequeue();
	}

	while (getErrorHandler().getErrorCount() != 0)
		std::cout << getErrorHandler().popError().getName() << std::endl;

	std::cin.get();
}