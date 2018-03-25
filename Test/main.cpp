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

int main()
{
	//NOU::NOU_CORE::ErrorHandler::setCallback(callback);

	using HandleType = NOU::NOU_MEM_MNGT::GeneralPurposeAllocator::GeneralPurposeAllocatorPointer<Person>;

	NOU::NOU_MEM_MNGT::GeneralPurposeAllocator gpa;
	NOU::NOU_DAT_ALG::Vector<HandleType> test;

	test.push(gpa.allocateObjects<Person>(1, 40, "Mike", "Braun"));
	test.at(0).getRaw()->print();

	gpa.deallocateObjects(test.at(0));
	test.pop();
	gpa.deallocateObjects(test.at(0));

	test.push(gpa.allocateObjects<Person>(1, 22, "Laura", "Meier"));
	test.push(gpa.allocateObjects<Person>(1, 40, "Petra", "Braun"));
	test.push(gpa.allocateObjects<Person>(1, 22, "Laura", "Meier"));
	test.push(gpa.allocateObjects<Person>(1, 22, "Laura", "Meier"));
	for (int i = 0; i < test.size(); i++)
	{
		test.at(i).getRaw()->print();
	}
	for (int i = 0; i < test.size(); i++)
	{
		gpa.deallocateObjects(test.at(i));
	}

	system("pause");
}