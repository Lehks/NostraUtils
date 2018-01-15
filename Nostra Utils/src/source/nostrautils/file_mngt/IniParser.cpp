#include "nostrautils\file_mngt\IniParser.hpp"
#include <fstream>

namespace NOU::NOU_FILE_MNGT
{
	IniParser::IniParser(const char filename[]) :
		m_filename(filename)
	{}


	int IniParser::getValueQuotationType(std::string line)
	{
		int pos_quote_dbl = line.find_first_of('"');
		int pos_quote_sin = line.find_first_of('\'');

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


	void IniParser::addString(const std::string &key, const std::string &value)
	{
		m_string_data.insert(std::make_pair(key, value));
	}


	void IniParser::addInt(const std::string &key, const int32 &value)
	{
		m_int_data.insert(std::make_pair(key, value));
	}


	void IniParser::addFloat(const std::string &key, const float32 &value)
	{
		m_float_data.insert(std::make_pair(key, value));
	}


	std::string IniParser::cleanString(std::string string)
	{
		int pos_ltrim = 0;
		int pos_rtrim = 0;

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


	std::string IniParser::parseKey(std::string line)
	{
		// Clean line
		std::string key = this->cleanString(line);

		return key;
	}


	std::string IniParser::parseValue(std::string line)
	{
		int pos_quote_first;
		int pos_quote_last;
		int quote_type;
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


	void IniParser::parseLine(std::string line)
	{
		std::string key;
		std::string value;
		int pos_eq;

		// Clean string
		line = this->cleanString(line);

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

		// Get the key
		key = this->parseKey(line.substr(0, pos_eq));

		// Get the value
		value = this->parseValue(line.substr(pos_eq + 1));

		// Add pair
		this->addString(key, value);
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

		// Parse file content line by line
		while (std::getline(inifile, line))
		{
			this->parseLine(line);
		}

		inifile.close();
		
		return true;
	}


	std::string IniParser::getString(const char *key) const
	{
		std::unordered_map<std::string, std::string>::const_iterator i = m_string_data.find(key);

		if (i == m_string_data.end()) {
			return std::string();
		}

		return i->second;
	}


	int32 IniParser::getInt(const char *key) const
	{
		std::unordered_map<std::string, int32>::const_iterator i = m_int_data.find(key);

		if (i == m_int_data.end()) {
			return 0;
		}

		return i->second;
	}


	float32 IniParser::getFloat(const char *key) const
	{
		std::unordered_map<std::string, float32>::const_iterator i = m_float_data.find(key);

		if (i == m_float_data.end()) {
			return 0.0;
		}

		return i->second;
	}


	boolean IniParser::keyExists(const char * key) const
	{
		return (this->keyExistsString(key) || this->keyExistsInt(key) || this->keyExistsFloat(key));
	}


	boolean IniParser::keyExistsString(const char * key) const
	{
		return (m_string_data.count(key) > 0);
	}


	boolean IniParser::keyExistsInt(const char * key) const
	{
		return (m_int_data.count(key) > 0);
	}


	boolean IniParser::keyExistsFloat(const char * key) const
	{
		return (m_float_data.count(key) > 0);
	}
}