#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\Utils.hpp"
#include "nostrautils\dat_alg\BinaryHeap.hpp"
#include "nostrautils\dat_alg\ObjectPool.hpp"
#include "nostrautils\thread\ThreadManager.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

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
	A(const A&) = delete;
	A(A&&) = default;

	int get() const { return i; }
};

NOU_DEFINE_PAIR(P, A, a, A, b)

void func()
{
	std::cout << "Func" << std::endl;
}

void func1(int32 i)
{
	std::cout << "Func #" << i << std::endl;
}

struct Print
{
	std::string m_str;
	Print(std::string str) { m_str = str; }

	~Print() { std::cout << m_str.c_str() << std::endl; }
};

struct Test
{
	Print p1;
	Print p2;
	Print p3;

	Test() :
		p1("p1"),
		p2("p2"),
		p3("p3")
	{

	}
};

class Dummy
{
public:
	static Dummy& get()
	{
		static Dummy i;
		return i;
	}

	GenericAllocationCallback<NOU_DAT_ALG::internal::ObjectPoolChunk<NOU_CORE::ErrorHandler>> c;
	UniquePtr<ObjectPool<ErrorHandler>> p;

	Dummy() :
		p(new ObjectPool<ErrorHandler>(5, c), defaultDeleter)
	{

	}
};

int main()
{

#if 1
	std::cout << "Main thread: " << std::this_thread::get_id() << std::endl;

	NOU_CORE::ErrorHandler::setCallback(callback);
	
	ThreadManager& tm = ThreadManager::getInstance();

	//for (uint32 i = 0; i < 10; i++)
	//{
	//	auto task = makeTask(&func1, i);
	//
	//	tm.pushTask(&task, 0);
	//
	//	for (uint64 i = 0; i < 100'000'000; i++)
	//	{
	//		i++;
	//		i--;
	//	}
	//}
	
	auto task1 = makeTask(&func);
	auto task2 = makeTask(&func);
	auto task3 = makeTask(&func);
	auto task4 = makeTask(&func);

	tm.pushTask(&task1, 0);
	tm.pushTask(&task2, 0);
	tm.pushTask(&task3, 0);
	tm.pushTask(&task4, 0);

	while (NOU_CORE::getErrorHandler().getErrorCount() != 0)
		std::cout << NOU_CORE::getErrorHandler().popError().getName() << std::endl;
	std::cin.get();
#endif
}

//&(this->m_handlers.m_ptr->m_data.m_data->m_data.m_errors.m_ptr->m_allocator)