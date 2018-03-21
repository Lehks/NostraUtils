#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include "nostrautils\thread\AsyncTaskResult.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\thread\Threads.hpp"
#include <iostream>

using namespace NOU;
using namespace NOU_CORE;
using namespace NOU_DAT_ALG;
using namespace NOU_THREAD;
using namespace NOU_MEM_MNGT;

void callback(const ErrorLocation& el)
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

	int get() const { return i; }

	A add(A&& a)
	{
		return A(i + a.i);
	}

	A operator + (const A& a)
	{
		return A(i + a.i);
	}
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

int func2(int i)
{
	std::cout << "Func2 " << i << " " << std::this_thread::get_id() << std::endl;

	//for (int i = 0; i < 1'000'000'0; i++)
	//{
	//	i++;
	//	i--;
	//}

	return i;
}

void func3(int i)
{
	std::cout << "Func3 " << i << " " << std::this_thread::get_id() << std::endl;

	//for (int i = 0; i < 1'000'000'0; i++)
	//{
	//	i++;
	//	i--;
	//}
}

void func4(int i)
{
	std::cout << "Func4 " << i << " " << std::this_thread::get_id() << std::endl;

	//for (int i = 0; i < 1'000'000'0; i++)
	//{
	//	i++;
	//	i--;
	//}
}

void doStuff()
{
	std::cout << "Do stuff. " << std::this_thread::get_id() << std::endl;
}

void testFunc()
{
	AsyncTaskResult<void, decltype(&doStuff)> asyncTaskResult(&doStuff);

	std::cout << "testFunc " << std::this_thread::get_id() << std::endl;

	for (int i = 0; i < 10000; i++)
	{
		i++;
		i--;
	}

	asyncTaskResult.getResult();
}

int main()
{
	AsyncTaskResult<void, decltype(&doStuff)> asyncTaskResult(&testFunc);

	std::cout << "main " << std::this_thread::get_id() << std::endl;

	std::cin.get();
}

//&(this->m_handlers.m_ptr->m_data.m_data->m_data.m_errors.m_ptr->m_allocator)