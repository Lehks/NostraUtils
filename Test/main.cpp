#define NOU_DEBUG

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\mem_mngt\PoolAllocator.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\mem_mngt\GeneralPurposeAllocator.hpp"
#include "nostrautils/thread/Threads.hpp"

#include <iostream>
#include <string>
#include <type_traits>

void callback(const NOU::NOU_CORE::ErrorLocation &loc)
{
	__debugbreak();
}

class Person
{
public:
	size_t m_age;
	std::string m_name;
	std::string m_haircolor;

	Person(size_t age, std::string name, std::string haircolor) :
		m_age(age),
		m_name(name),
		m_haircolor(haircolor)
	{
		std::cout << "Konstruktor" << std::endl;
	}

	~Person()
	{
		std::cout << "Destruktor" << std::endl;
	}

	void print()
	{
		std::cout << m_name << " " << m_age << " " << m_haircolor << std::endl;
	}
};

long func(int i)
{
	std::cout << "Func! " << i << " "  << std::this_thread::get_id() << std::endl;
	return i + 5;
}

long func2(int i)
{
	std::cout << "Func2! " << i << " " << std::this_thread::get_id() << std::endl;
	return i + 6;
}

class A
{

};

int funcA(const A)
{
	return 1;
}

int main()
{
	using namespace NOU::NOU_THREAD;
	
	const A a;

	auto task = makeTask(&funcA, a);

	std::cout << "Main: " << std::this_thread::get_id() << std::endl;


	TaskQueue<long, decltype(&func), TaskQueueAccumulators::FunctionPtr<long>, int> tq(&TaskQueueAccumulators::forward<long>);

	tq.pushTask(makeTask(&func, 1));
	tq.pushTask(makeTask(&func, 2));
	tq.pushTask(makeTask(&func, 3));
	tq.pushTask(makeTask(&func2, 4));
	tq.pushTask(makeTask(&func2, 5));
	tq.pushTask(makeTask(&func2, 6));

	tq.close();
	long res = tq.getResult();

	using namespace std::chrono_literals;
	std::this_thread::sleep_for(1s);

	std::cin.get();
}