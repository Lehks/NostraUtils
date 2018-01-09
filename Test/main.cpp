#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"

#include <iostream>


int main()
{

	NOU::NOU_DAT_ALG::String<NOU::char8> str("Hallo");

	str.append(" was GEhT");
	str.append('a');


	std::cout << str.rawStr() << std::endl;
	std::cout << str.at(0) << std::endl;
	std::cout << str[1] << std::endl;

	str.toLowerCase();
	std::cout << str.rawStr() << std::endl;

	str.toUpperCase();
	std::cout << str.rawStr() << std::endl;

	str.trim();
	std::cout << str.rawStr() << std::endl;

	str.appendIf(false, "Hau ab");
	str.appendIf(true, "c++ is einfach.");
	std::cout << str.rawStr() << std::endl;

	str.append(12);
	std::cout << str.rawStr() << std::endl;

	system("pause");
	//Do testing here
}