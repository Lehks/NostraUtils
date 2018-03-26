#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\file_mngt\INIFile.hpp"
#include <iostream>


namespace NOU::NOU_FILE_MNGT
{
	void test()
	{
		NouString test_string;
		int32 test_int;
		float32 test_float;

		INIFile p(NouString("C:\\Git\\NostraUtils\\Test\\Test.ini"));

		if (!p.read()) {
			std::cout << "Failed to read file.";
			return;
		}
		else {
			std::cout << "File read successfully." << std::endl;
		}

		// Get values
		test_string.clear().append(p.getString(NouString("STRING_A"), NouString("general")));
		std::cout << "general::STRING_A = " << test_string.rawStr() << std::endl;

		test_int = p.getInt(NouString("INT_A"), NouString("general"));
		std::cout << "general::INT_A = " << test_int << std::endl;

		test_float = p.getFloat(NouString("FLOAT_A"), NouString("general"));
		std::cout << "general::FLOAT_A = " << test_float << std::endl;

		// Cast to string
		test_string.clear().append(p.getString(NouString("INT_A"), NouString("general")));
		std::cout << "Get int as string = " << test_string.rawStr() << std::endl;

		test_string.clear().append(p.getString(NouString("FLOAT_A"), NouString("general")));
		std::cout << "Get float as string = " << test_string.rawStr() << std::endl;

		// Cast to int
		/**
		// This will throw an exception
		test_int = p.getInt("STRING_A", "general");
		std::cout << "Get string as int = " << test_int << std::endl;
		*/
		
		test_int = p.getInt(NouString("FLOAT_A"), NouString("general"));
		std::cout << "Get float as int = " << test_int << std::endl;

		// Cast to float
		/**
		// This will throw an exception
		test_float = p.getFloat("STRING_A", "general");
		std::cout << "Get string as float = " << test_float << std::endl;
		*/
		
		test_float = p.getFloat(NouString("INT_A"), NouString("general"));
		std::cout << "Get int as float = " << test_float << std::endl;

		// Override values
		p.setString(NouString("STRING_A"), NouString("New string"), NouString("general"));
		test_string.clear().append(p.getString(NouString("STRING_A"), NouString("general")));
		std::cout << "String override = " << test_string.rawStr() << std::endl;

		p.setInt(NouString("INT_A"), 100, NouString("general"));
		test_int = p.getInt(NouString("INT_A"), NouString("general"));
		std::cout << "Int override = " << test_int << std::endl;

		p.setFloat(NouString("FLOAT_A"), 10.1, NouString("general"));
		test_float = p.getFloat(NouString("FLOAT_A"), NouString("general"));
		std::cout << "Float override = " << test_float << std::endl;

		// Add values
		p.setString(NouString("STRING_X"), NouString("Hello World"));
		test_string.clear().append(p.getString(NouString("STRING_X")));
		std::cout << "New String = " << test_string.rawStr() << std::endl;

		p.setInt(NouString("INT_X"), 99);
		test_int = p.getInt(NouString("INT_X"));
		std::cout << "New Int = " << test_int << std::endl;

		p.setFloat(NouString("FLOAT_X"), 99.3);
		test_float = p.getFloat(NouString("FLOAT_X"));
		std::cout << "New Float = " << test_float << std::endl;

		p.write(NouString("C:\\Git\\NostraUtils\\Test\\Test2.ini"));
	}
}

int main()
{
	NOU::NOU_FILE_MNGT::test();

	system("pause");
	return 0;
}