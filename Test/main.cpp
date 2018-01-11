#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\thread\Task.hpp"
#include <string>
#include <iostream>

class B
{
public:
	B()
	{
		std::cout << "Const B" << std::endl;
	}

	B(const B&)
	{
		std::cout << "Copy B" << std::endl;
	}

	B(B&&)
	{
		std::cout << "Move B" << std::endl;
	}

	B& operator = (const B&)
	{
		std::cout << "Copy Assign B" << std::endl;

		return *this;
	}

	B& operator = (B&&)
	{
		std::cout << "Move Assign B" << std::endl;

		return *this;
	}
};

class A
{
public:

	A()
	{
		std::cout << "Const A" << std::endl;
	}

	A(const A&)
	{
		std::cout << "Copy A" << std::endl;
	}

	A(A&&)
	{
		std::cout << "Move A" << std::endl;
	}

	~A()
	{
		std::cout << "Dest A" << std::endl;
	}

	A& operator = (const A&)
	{
		std::cout << "Copy Assign A" << std::endl;

		return *this;
	}

	A& operator = (A&&)
	{
		std::cout << "Move Assign A" << std::endl;

		return *this;
	}

	int exec(int i, int j, const B&) const
	{
		std::cout << ":= " << j << " " << std::endl;
		return i + j;
	}
};

template<typename T, typename F, typename... ARGS>
int func(T* t, F&& func, ARGS&&... args)
{
	return (t->*func)(args...);
}

int func2(const A* a, decltype(&A::exec) func_, int a_, int b, const B& b_)
{
	return func(a, func_, a_, b, b_);
}

int main()
{
	const A a;
	//NOU::NOU_THREAD::Task task = NOU::NOU_THREAD::makeTaskFromMemberFunction(&a, &A::exec, 5, 6, B());
	//std::cout << typeid(NOU::NOU_THREAD::MemberFunctionTask<const A*, decltype(&A::exec), int, int, const B&>::ReturnType).name() << std::endl;
	
	NOU::NOU_THREAD::MemberFunPtrWrapper<const A*, decltype(&A::exec), int, int, const B&> mfpw(&a, &A::exec);

	auto tuple = std::make_tuple(&a, &A::exec, 5, 6, B());

	//int i = std::apply(mfpw, tuple);
	//int i = std::invoke(mfpw, 5, 6, B());

	//func(&a, &A::exec, 5, 6, B());

	//std::apply(func<A, decltype(&A::exec), int, int, B>, tuple);

	using T = decltype(func<A, decltype(&A::exec), int, int, B>);

	std::cout << typeid(T).name() << std::endl;

	//func2(&a, &A::exec, 5, 6, B());

	//std::invoke(func2, &a, &A::exec, 5, 6, B());

	std::apply(func2, tuple);

	//std::invoke(func<A, decltype(&A::exec), int, int, B>, &a, &A::exec, 5, 5, B());

	//std::cout << i << std::endl;

	//task->execute();
	
	//std::cout << *((int*)task->getResult()) << std::endl;

	//using Type = NOU::NOU_CORE::InvokeResult_t<decltype(&A::exec), A, int, int, B&>;

	//std::cout << typeid(Type).name() << std::endl;

	std::cin.get();
}