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

void func1()
{
	std::cout << "Func1" << std::endl;
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

	auto task = makeTask(&func);
	auto task1 = makeTask(&func1);

	tm.pushTask(&task, 0);
//	tm.pushTask(&task1, 0);

	while (NOU_CORE::getErrorHandler().getErrorCount() != 0)
		std::cout << NOU_CORE::getErrorHandler().popError().getName() << std::endl;
	std::cin.get();
#endif
}

//&(this->m_handlers.m_ptr->m_data.m_data->m_data.m_errors.m_ptr->m_allocator)