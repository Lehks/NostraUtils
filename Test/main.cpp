#define NOU_DEBUG

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\mem_mngt\PoolAllocator.hpp"
#include "nostrautils\core\ErrorHandler.hpp"

#include <iostream>
#include <string>

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
	}

	~Person()
	{
	}

	void print()
	{
		std::cout << m_name << " " << m_age << " " << m_haircolor << std::endl;
	}
};

int main()
{
	int alloc = 0;
	{
		NOU::NOU_MEM_MNGT::PoolAllocator<Person> personenAllocator;

		personenAllocator.deallocate(((Person*)nullptr) + 15);

		std::cout << NOU::NOU_CORE::getErrorHandler().peekError().getName() << std::endl;
	}
	NOU::NOU_MEM_MNGT::PoolAllocator<Person> personenAllocator;

	NOU::NOU_DAT_ALG::Vector<Person*> test;

	test.push(personenAllocator.allocate(12, "Hans", "Blond"));

	test.at(0)->print();

	personenAllocator.deallocate(test.pop());
	 
	system("pause");
}