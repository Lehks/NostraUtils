#include "nostrautils\file_mngt\IniParser.hpp"
#include <fstream>


namespace NOU::NOU_FILE_MNGT
{
	IniParser::IniParser(const char filename[]) :
		m_filename(filename)
	{}

	void IniParser::setCurrentSection(const std::string & section)
	{
		this->current_section = section;
	}


	int32 IniParser::getValueQuotationType(std::string line)
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


	int32 IniParser::getValueDataType(const std::string &line)
	{
		// If the value is in quotes, we assume a string
		if (this->getValueQuotationType(line) != INI_QUOTE_NONE) {
			return INI_TYPE_STRING;
		}

		// If we dont find a ".", we assume an integer
		if (line.find_first_of('.') == std::string::npos) {
			return INI_TYPE_INT;
		}

		return INI_TYPE_FLOAT;
	}


	void IniParser::addString(const std::string &key, const std::string &value, const std::string & section)
	{
		m_string_data.insert(std::make_pair(section + "." + key, value));
	}


	void IniParser::addInt(const std::string &key, const int32 &value, const std::string & section)
	{
		m_int_data.insert(std::make_pair(section + "." + key, value));
	}


	void IniParser::addFloat(const std::string &key, const float32 &value, const std::string & section)
	{
		m_float_data.insert(std::make_pair(section + "." + key, value));
	}


	void IniParser::setString(const std::string &key, const std::string &value, const std::string & section)
	{
		if (!this->keyExistsString(key.c_str(), section)) {
			this->addString(key, value, section);
		}

		m_string_data.erase(key);
		this->addString(key, value, section);
	}


	void IniParser::setInt(const std::string &key, const int32 &value, const std::string & section)
	{
		if (!this->keyExistsInt(key.c_str(), section)) {
			this->addInt(key, value, section);
		}

		m_int_data.erase(key);
		this->addInt(key, value, section);
	}


	void IniParser::setFloat(const std::string &key, const float32 &value, const std::string & section)
	{
		if (!this->keyExistsFloat(key.c_str(), section)) {
			this->addFloat(key, value, section);
		}

		m_float_data.erase(key);
		this->addFloat(key, value, section);
	}


	std::string IniParser::cleanString(std::string string)
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


	std::string IniParser::parseKey(const std::string &line)
	{
		// Clean line
		std::string key = this->cleanString(line);

		return key;
	}


	std::string IniParser::parseStringValue(const std::string &line)
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


	int32 IniParser::parseIntValue(const std::string &line)
	{
		return std::atoi(line.c_str());
	}


	float32 IniParser::parseFloatValue(const std::string &line)
	{
		return std::stof(line);
	}


	void IniParser::parseLine(std::string line)
	{
		std::string line_lft;
		std::string line_rgt;
		std::string key;
		int32 pos_eq;

		
		// Clean string
		line = this->cleanString(line);

		// Check if we have a section
		if (line[0] == '[' && line[(line.length() - 1)] == ']') {
			this->setCurrentSection(line.substr(1, line.length() - 2));
			return;
		}

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

		// Add key-value pair
		switch (this->getValueDataType(line_rgt))
		{
			case INI_TYPE_INT:
				this->addInt(this->parseKey(line_lft), this->parseIntValue(line_rgt), current_section);
			break;

			case INI_TYPE_FLOAT:
				this->addFloat(this->parseKey(line_lft), this->parseFloatValue(line_rgt), current_section);
				break;

			default:
				this->addString(this->parseKey(line_lft), this->parseStringValue(line_rgt), current_section);
				break;
		}
	}


	boolean IniParser::parse()
	{
		std::ifstream inifile;
		std::string line;

		// Open file stream
		inifile.open(this->m_filename);

		if (!inifile) {
			// Todo: Error handling
			return false;
		}

		// Set the current section as default
		this->setCurrentSection(INI_DEFAULT_SECTION);

		// Parse file content line by line
		while (std::getline(inifile, line))
		{
			this->parseLine(line);
		}

		inifile.close();
		
		return true;
	}


	std::string IniParser::getString(const char *key, const std::string & section) const
	{
		std::unordered_map<std::string, std::string>::const_iterator i = m_string_data.find(section + "." + key);

		if (i == m_string_data.end()) {
			return std::string();
		}

		return i->second;
	}


	int32 IniParser::getInt(const char *key, const std::string & section) const
	{
		std::unordered_map<std::string, int32>::const_iterator i = m_int_data.find(section + "." + key);

		if (i == m_int_data.end()) {
			return 0;
		}

		return i->second;
	}


	float32 IniParser::getFloat(const char *key, const std::string & section) const
	{
		std::unordered_map<std::string, float32>::const_iterator i = m_float_data.find(section + "." + key);

		if (i == m_float_data.end()) {
			return 0.0;
		}

		return i->second;
	}


	boolean IniParser::keyExists(const char * key, const std::string & section) const
	{
		return (this->keyExistsString(key, section) || this->keyExistsInt(key, section) || this->keyExistsFloat(key, section));
	}


	boolean IniParser::keyExistsString(const char * key, const std::string & section) const
	{
		return (m_string_data.count(section + "." + key) > 0);
	}


	boolean IniParser::keyExistsInt(const char * key, const std::string & section) const
	{
		return (m_int_data.count(section + "." + key) > 0);
	}


	boolean IniParser::keyExistsFloat(const char * key, const std::string & section) const
	{
		return (m_float_data.count(section + "." + key) > 0);
	}
}