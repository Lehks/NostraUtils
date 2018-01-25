#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\AllocationCallback.hpp"
#include "nostrautils\dat_alg\Vector.hpp"

#include <iostream>


int main()
{

	NOU::NOU_DAT_ALG::String<NOU::char8> str;

	str.append(5123.01);

	std::cout << str.rawStr() << std::endl;

	str.replace('1' , 'B', 0, str.size());

	std::cout << str.rawStr() << std::endl;

	str.clear();

	str.append("Hallo Mein Name ist Dennis             ");

	str.trim();

	str.append(" was geht.");

	std::cout << str.rawStr() << std::endl;

	system("pause");
}