#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\mem_mngt\PoolAllocator.hpp"

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
	{
		NOU::NOU_MEM_MNGT::PoolAllocator<Person> personenAllocator;

		Person* p1 = personenAllocator.allocate(18, "Peter", "Braun");
		Person* p2 = personenAllocator.allocate(20, "Karl", "Blond");
		Person* p3 = personenAllocator.allocate(22, "Gustav", "Rot");
		p3->print();
		personenAllocator.deallocate(p3);
		Person* p4 = personenAllocator.allocate(44, "Jan", "Rot");
		Person* p5 = personenAllocator.allocate(32, "Sabine", "Braun");
		Person* p6 = personenAllocator.allocate(79, "Karl-Heinz", "Grau");

		p1->print();
		p2->print();
		p4->print();
		p5->print();
		p6->print();


		personenAllocator.deallocate(p1);
		personenAllocator.deallocate(p2);
		personenAllocator.deallocate(p4);
		personenAllocator.deallocate(p5);
		personenAllocator.deallocate(p6);
	}
	system("pause");
}