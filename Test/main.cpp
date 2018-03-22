#define NOU_DEBUG

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include "nostrautils\mem_mngt\PoolAllocator.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include "nostrautils\mem_mngt\GeneralPurposeAllocator.hpp"

#include <iostream>
#include <string>
#include <type_traits>

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
	std::cout << "Multiple: " << NOU::NOU_MEM_MNGT::internal::nextMultiple(10, 32) << std::endl;
	using HandleType = NOU::NOU_MEM_MNGT::GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<Person>;

	NOU::NOU_MEM_MNGT::GeneralPurposeAllocator gpa;
	NOU::NOU_DAT_ALG::Vector<HandleType> test;
	

	test.push(gpa.allocateObjects<Person>(1, 40, "Petra", "Braun"));

	

	for (HandleType &pers : test)
	{
		pers[0].print();
		//pers[1].print();
		//pers[2].print();
		//pers[3].print();
		//pers[4].print();
		//pers[5].print();
		//pers[6].print();
		//pers[7].print();
		//pers[8].print();
		//pers[9].print();
		//pers[10].print();
		//pers[11].print();
		//pers[12].print();
		//gpa.deallocateObjects(pers);
	}
	
	

	system("pause");
}