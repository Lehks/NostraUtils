#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\file_mngt\INIFile.hpp"
#include <iostream>


namespace NOU::NOU_FILE_MNGT
{
	void test()
	{
		std::string test_string;
		int32 test_int;
		float32 test_float;

		INIFile p("C:\\Git\\NostraUtils\\Test\\Test.ini");

		if (!p.read()) {
			std::cout << "Failed to read file.";
			return;
		}
		else {
			std::cout << "File read successfully." << std::endl;
		}

		// Get values
		test_string = p.getString("STRING_A", "general");
		std::cout << "general::STRING_A = " << test_string.c_str() << std::endl;

		test_int = p.getInt("INT_A", "general");
		std::cout << "general::INT_A = " << test_int << std::endl;

		test_float = p.getFloat("FLOAT_A", "general");
		std::cout << "general::FLOAT_A = " << test_float << std::endl;

		// Cast to string
		test_string = p.getString("INT_A", "general");
		std::cout << "Get int as string = " << test_string.c_str() << std::endl;

		test_string = p.getString("FLOAT_A", "general");
		std::cout << "Get float as string = " << test_string.c_str() << std::endl;

		// Cast to int
		/**
		// This will throw an exception
		test_int = p.getInt("STRING_A", "general");
		std::cout << "Get string as int = " << test_int << std::endl;
		*/
		
		test_int = p.getInt("FLOAT_A", "general");
		std::cout << "Get float as int = " << test_int << std::endl;

		// Cast to float
		/**
		// This will throw an exception
		test_float = p.getFloat("STRING_A", "general");
		std::cout << "Get string as float = " << test_float << std::endl;
		*/
		
		test_float = p.getFloat("INT_A", "general");
		std::cout << "Get int as float = " << test_float << std::endl;

		// Override values
		p.setString("STRING_A", "New string", "general");
		test_string = p.getString("STRING_A", "general");
		std::cout << "String override = " << test_string.c_str() << std::endl;

		p.setInt("INT_A", 100, "general");
		test_int = p.getInt("INT_A", "general");
		std::cout << "Int override = " << test_int << std::endl;

		p.setFloat("FLOAT_A", 10.1, "general");
		test_float = p.getFloat("FLOAT_A", "general");
		std::cout << "Float override = " << test_float << std::endl;

		// Add values
		p.setString("STRING_X", "Hello World");
		test_string = p.getString("STRING_X");
		std::cout << "New String = " << test_string.c_str() << std::endl;

		p.setInt("INT_X", 99);
		test_int = p.getInt("INT_X");
		std::cout << "New Int = " << test_int << std::endl;

		p.setFloat("FLOAT_X", 99.3);
		test_float = p.getFloat("FLOAT_X");
		std::cout << "New Float = " << test_float << std::endl;

		p.write("C:\\Git\\NostraUtils\\Test\\Test2.ini");
	}
}

int main()
{
	NOU::NOU_FILE_MNGT::test();

	system("pause");
	return 0;
}