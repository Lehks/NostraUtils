#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\file_mngt\IniParser.hpp"
#include <iostream>


namespace NOU::NOU_FILE_MNGT
{
	void test()
	{
		std::string test_string;
		int32 test_int;
		float32 test_float;

		IniParser p("C:\\Git\\NostraUtils\\Test\\Test.ini");
		p.parse();

		test_string = p.getString("STRING_A", "general");
		std::cout << "STRING_A = " << test_string << std::endl;

		test_string = p.getString("STRING_B");
		std::cout << "STRING_B = " << test_string << std::endl;

		test_int = p.getInt("INT_A");
		std::cout << "INT_A = " << test_int << std::endl;

		test_float = p.getFloat("FLOAT_A");
		std::cout << "FLOAT_A = " << test_float << std::endl;
	}
}

int main()
{
	NOU::NOU_FILE_MNGT::test();

	system("pause");
	return 0;
}