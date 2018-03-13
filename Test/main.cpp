#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include "nostrautils\thread\ThreadManager.hpp"
#include "nostrautils\thread\AsyncTaskResult.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include <iostream>

using namespace NOU;
using namespace NOU_CORE;
using namespace NOU_DAT_ALG;
using namespace NOU_THREAD;
using namespace NOU_MEM_MNGT;

void callback(const ErrorLocation& el)
{
//	__debugbreak();
}

class A
{
private:
	int i;
public:
	A() = default;
	A(int i) : i(i) {}

	int get() const { return i; }
};

NOU_DEFINE_PAIR(P, A, a, A, b)

void func()
{
	std::cout << "Func" << std::endl;
}

uint8 values[100] = {0};

Mutex m;

void func1(int32 i)
{
	values[i]++;

	{
		Lock l(m);
		std::cout << "Func #" << i << std::endl;
	}

	for (uint64 i = 0; i < 100'000'000; i++)
	{
		i++;
		i--;
	}

	{
		Lock l(m);
		std::cout << "Func #" << i << " Done." << std::endl;
	}

	values[i]++;
}

int func2()
{
	std::cout << "Func2" << std::endl;

	return 1;
}

template boolean Task<void, void(*)()>::execute();

int main()
{
#if 1
	NOU_CORE::ErrorHandler::setCallback(callback);
	
	ThreadManager& tm = ThreadManager::getInstance();

#if 0

	auto task1  = makeTask(&func1, 1);
	auto task2  = makeTask(&func1, 2);
	auto task3  = makeTask(&func1, 3);
	auto task4  = makeTask(&func1, 4);
	auto task5  = makeTask(&func1, 5);
	auto task6  = makeTask(&func1, 6);
	auto task7  = makeTask(&func1, 7);
	auto task8  = makeTask(&func1, 8);
	auto task9  = makeTask(&func1, 9);
	auto task10 = makeTask(&func1, 10);
	auto task11 = makeTask(&func1, 11);
	auto task12 = makeTask(&func1, 12);
	auto task13 = makeTask(&func1, 13);
	auto task14 = makeTask(&func1, 14);
	auto task15 = makeTask(&func1, 15);
	auto task16 = makeTask(&func1, 16);
	auto task17 = makeTask(&func1, 17);
	auto task18 = makeTask(&func1, 18);
	auto task19 = makeTask(&func1, 19);
	auto task20 = makeTask(&func1, 20);
	auto task21 = makeTask(&func1, 21);
	auto task22 = makeTask(&func1, 22);
	auto task23 = makeTask(&func1, 23);
	auto task24 = makeTask(&func1, 24);
	auto task25 = makeTask(&func1, 25);
	auto task26 = makeTask(&func1, 26);
	auto task27 = makeTask(&func1, 27);
	auto task28 = makeTask(&func1, 28);
	auto task29 = makeTask(&func1, 29);
	auto task30 = makeTask(&func1, 30);
	auto task31 = makeTask(&func1, 31);
	auto task32 = makeTask(&func1, 32);
	auto task33 = makeTask(&func1, 33);
	auto task34 = makeTask(&func1, 34);
	auto task35 = makeTask(&func1, 35);
	auto task36 = makeTask(&func1, 36);
	auto task37 = makeTask(&func1, 37);
	auto task38 = makeTask(&func1, 38);
	auto task39 = makeTask(&func1, 39);
	auto task40 = makeTask(&func1, 40);

	tm.pushTask(&task1, 0);
	tm.pushTask(&task2, 0);
	tm.pushTask(&task3, 0);
	tm.pushTask(&task4, 0);
	tm.pushTask(&task5, 0);
	tm.pushTask(&task6, 0);
	tm.pushTask(&task7, 0);
	tm.pushTask(&task8, 0);
	tm.pushTask(&task9, 0);
	tm.pushTask(&task10, 0);
	tm.pushTask(&task11, 0);
	tm.pushTask(&task12, 0);
	tm.pushTask(&task13, 0);
	tm.pushTask(&task14, 0);
	tm.pushTask(&task15, 0);
	tm.pushTask(&task16, 0);
	tm.pushTask(&task17, 0);
	tm.pushTask(&task18, 0);
	tm.pushTask(&task19, 0);
	tm.pushTask(&task20, 0);
	tm.pushTask(&task21, 0);
	tm.pushTask(&task22, 0);
	tm.pushTask(&task23, 0);
	tm.pushTask(&task24, 0);
	tm.pushTask(&task25, 0);
	tm.pushTask(&task26, 0);
	tm.pushTask(&task27, 0);
	tm.pushTask(&task28, 0);
	tm.pushTask(&task29, 0);
	tm.pushTask(&task30, 0);
	tm.pushTask(&task31, 0);
	tm.pushTask(&task32, 0);
	tm.pushTask(&task33, 0);
	tm.pushTask(&task34, 0);
	tm.pushTask(&task35, 0);
	tm.pushTask(&task36, 0);
	tm.pushTask(&task37, 0);
	tm.pushTask(&task38, 0);
	tm.pushTask(&task39, 0);
	tm.pushTask(&task40, 0);


//	std::cout << tm.m_threads->size() << std::endl;

	for (uint64 i = 0; i < 1'000'000'000; i++)
	{
		i--;
		i++;
	}

	for (int i = 0; i < sizeof(values) / sizeof(decltype(values[0])); i++)
	{
		if (values[i] == 1)
			std::cout << "Not finished: " << i << std::endl;
	}

	std::cout << "Done" << std::endl;

#endif

#define PRINT(var) NOU_STRINGIFY(var) << ": " << var

	std::cout << PRINT(tm.currentlyPreparedThreads()) << std::endl;

	sizeType createdThreads = tm.prepareThread(4);

	std::cout << PRINT(createdThreads) << std::endl;
	std::cout << PRINT(tm.currentlyPreparedThreads()) << std::endl;

	auto task0 = makeTask(&func2);
	auto task1 = makeTask(&func);

	AsyncTaskResult<int, decltype(&func2)> result0(move(task0));
	AsyncTaskResult<void, decltype(&func)> result1(move(task1));

	typename AsyncTaskResult<int, decltype(&func2)>::State s = result0.getState();

	while (NOU_CORE::getErrorHandler().getErrorCount() != 0)
		std::cout << std::this_thread::get_id() << " " << NOU_CORE::getErrorHandler().popError().getName() << std::endl;
	std::cin.get();
#endif
}

//&(this->m_handlers.m_ptr->m_data.m_data->m_data.m_errors.m_ptr->m_allocator)