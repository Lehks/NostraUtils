#include "nostrautils\file_mngt\INIFile.hpp"
#include <string>
#include <fstream>

namespace NOU::NOU_FILE_MNGT
{
	INIFile::INIFile(const std::string filename) :
		m_filename(filename)
	{}


	std::string IniParser::parseKey(const std::string &line)
	{
		// Clean line
		std::string key = this->cleanString(line);

		return key;
	}


	std::string INIFile::parseStringValue(const std::string &line)
	{
		int32 pos_quote_first;
		int32 pos_quote_last;
		int32 quote_type;
		char quote;

		// Clean line
		std::string value = this->cleanString(line);

		// Get the quotation type
		quote_type = this->getValueQuotationType(line);

		// If there are no quotes, we are done here.
		if (quote_type == INI_QUOTE_NONE) {
			return value;
		}

		if (quote_type == INI_QUOTE_DOUBLE) {
			quote = '"';
		}
		else {
			quote = '\'';
		}

		pos_quote_first = line.find_first_of(quote) + 1;
		pos_quote_last = line.find_last_of(quote);

		value = line.substr(pos_quote_first, pos_quote_last - pos_quote_first);

		return value;
	}


	int32 INIFile::parseIntValue(const std::string &line)
	{
		return std::atoi(line.c_str());
	}


	float32 INIFile::parseFloatValue(const std::string &line)
	{
		return std::stof(line);
	}


	std::string INIFile::parseCleanString(std::string string) const
	{
		int32 pos_ltrim = 0;
		int32 pos_rtrim = 0;

		// Left trim
		for (pos_ltrim = 0; pos_ltrim < string.length(); pos_ltrim++)
		{
			if (string[pos_ltrim] > 32) {
				break;
			}
		}

		// Right trim
		for (pos_rtrim = string.length() - 1; pos_rtrim > 0; pos_rtrim--)
		{
			if (string[pos_rtrim] > 32) {
				break;
			}
		}

		// Get substring
		if (pos_ltrim > 0) {
			string.erase(0, pos_ltrim);
		}

		if (pos_rtrim < string.length() - 1) {
			string.erase(pos_rtrim + 1);
		}

		return string;
	}


	int32 INIFile::parseValueQuote(const std::string & line) const
	{
		int32 pos_quote_dbl = line.find_first_of('"');
		int32 pos_quote_sin = line.find_first_of('\'');

		// Return INI_QUOTE_NONE if no quotes
		if (pos_quote_dbl == pos_quote_sin) {
			return INI_QUOTE_NONE;
		}

		// Return INI_QUOTE_DOUBLE for double quoation marks
		if (pos_quote_sin == std::string::npos) {
			return INI_QUOTE_DOUBLE;
		}

		// Return INI_QUOTE_SINGLE for single quotation marks
		return INI_QUOTE_SINGLE;
	}


	void INIFile::parseLine(const std::string & line, const std::string & section)
	{
		std::string line_lft;
		std::string line_rgt;
		int32 pos_eq;

		// Get position of the first equal symbol
		pos_eq = line.find_first_of("=");

		// Check if we have an equal symbol
		if (pos_eq == std::string::npos) {
			return;
		}

		// Check if first char indicates comment
		if (line[0] == ';') {
			return;
		}

		// Split the string into a left and right part
		line_lft = line.substr(0, pos_eq);
		line_rgt = line.substr(pos_eq + 1);

		if (this->parseValueQuote(line_rgt) == INI_QUOTE_NONE) {
			if (line_rgt.find_first_of('.') == std::string::npos) {
				// Add int
				this->setInt(this->parseKey(line_lft), this->parseIntValue(line_rgt), section);
			}

			// Add float
			this->setFloat(this->parseKey(line_lft), this->parseFloatValue(line_rgt), section);
			return;
		}

		// Add string
		this->setString(this->parseKey(line_lft), this->parseStringValue(line_rgt), section);
	}


	boolean INIFile::read()
	{
		std::ifstream inifile;
		std::string line;
		std::string section;

		// Open file stream
		inifile.open(this->m_filename);

		if (!inifile) {
			return false;
		}

		// Set the default section
		section = INI_DEFAULT_SECTION;

		// Parse file content line by line
		while (std::getline(inifile, line))
		{
			line = this->parseCleanString(line);

			// Check if we have a section
			if (line[0] == '[' && line[(line.length() - 1)] == ']') {
				section = line.substr(1, line.length() - 2);
			}
			else {
				this->parseLine(line, section);
			}
		}

		inifile.close();

		return true;
	}

	void INIFile::remove(const std::string & key, const std::string & section)
	{
		std::string search = section + "." + key;

		if (m_data_string.count(search) > 0) {
			m_data_string.erase(search);
		}
		else if (m_data_integer.count(search) > 0) {
			m_data_integer.erase(search);
		}
		else if (m_data_float.count(search) > 0) {
			m_data_float.erase(search);
		}
	}


	void INIFile::setString(const std::string & key, const std::string & value, const std::string & section)
	{
		this->remove(key, section);

		m_data_string.insert(std::make_pair(section + "." + key, value));
	}


	void INIFile::setInt(const std::string & key, const int32 value, const std::string & section)
	{
		this->remove(key, section);

		m_data_integer.insert(std::make_pair(section + "." + key, value));
	}


	void INIFile::setFloat(const std::string & key, const float32 value, const std::string & section)
	{
		this->remove(key, section);

		m_data_float.insert(std::make_pair(section + "." + key, value));
	}


	std::string INIFile::getString(const std::string & key, const std::string & section) const
	{
		std::string search = section + "." + key;
		std::unordered_map<std::string, std::string>::const_iterator i = m_data_string.find(search);
		
		if (i != m_data_string.end()) {
			return i->second;
		}

		// Search in integer map and cast to string if found
		if (m_data_integer.count(search) > 0) {
			return std::to_string(this->getInt(key, section));
		}

		// Search in float map and cast to string if found
		if (m_data_float.count(search) > 0) {
			return std::to_string(this->getFloat(key, section));
		}

		return std::string();
	}


	int32 INIFile::getInt(const std::string & key, const std::string & section) const
	{
		std::string search = section + "." + key;
		std::unordered_map<std::string, int32>::const_iterator i = m_data_integer.find(search);

		if (i != m_data_integer.end()) {
			return i->second;
		}

		// Search in string map and cast to int if found
		if (m_data_string.count(search) > 0) {
			return std::stoi(this->getString(key, section));
		}

		// Search in float map and cast to int if found
		if (m_data_float.count(search) > 0) {
			return static_cast<int32>(this->getFloat(key, section));
		}

		return 0;
	}


	float32 INIFile::getFloat(const std::string & key, const std::string & section) const
	{
		std::string search = section + "." + key;
		std::unordered_map<std::string, float32>::const_iterator i = m_data_float.find(search);

		if (i != m_data_float.end()) {
			return i->second;
		}

		// Search in string map and cast to float if found
		if (m_data_string.count(search) > 0) {
			return std::stof(this->getString(key, section));
		}

		// Search in integer map and cast to string if found
		if (m_data_integer.count(search) > 0) {
			return static_cast<float32>(this->getInt(key, section));
		}
		
		return 0.0;
	}


	boolean INIFile::keyExists(const std::string & key, const std::string & section) const
	{
		std::string search = section + "." + key;

		return (m_data_string.count(search) > 0 || m_data_integer.count(search) > 0 || m_data_float.count(search) > 0);
	}
}