#define NOU_DEBUG

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\mem_mngt\PoolAllocator.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\mem_mngt\GeneralPurposeAllocator.hpp"

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

int main()
{
	NOU::NOU_MEM_MNGT::GeneralPurposeAllocator gpa;
	auto p1 = gpa.allocateObject<Person>(40, "Petra", "Braun");

	p1->print();
	p1->m_age = 50;
	p1->m_haircolor = "Brown";
	p1->m_name = "Peter";
	p1->print();
	gpa.deallocateObjects(p1);

	system("pause");
}