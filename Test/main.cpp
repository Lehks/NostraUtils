#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\file_mngt\IniParser.hpp"
#include <iostream>


int main()
{
	NOU::NOU_FILE_MNGT::IniParser p("C:\\Git\\NostraUtils\\Test\\Test.ini");

	p.parse();
	std::string value = p.getValue("TOKEN_A");

	std::cout << value << std::endl;

	system("pause");
	return 0;
}
