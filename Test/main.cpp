#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include <iostream>


struct Foo {

	int m_i;
	bool m_b;
	float m_f;

	Foo() = default;
	Foo(int i, bool b, float f) :
		m_i(i),
		m_b(b),
		m_f(f)
	{}

	Foo(Foo&&)
	{

	}
};

int main()
{

	NOU::NOU_DAT_ALG::Vector<Foo> v1;
	{
		Foo f1(1, true, 2.1f);
		v1.emplace_back(1,true,2.1f);

		std::cout << v1.at(0).m_f << std::endl;
	}

	system("pause");
}