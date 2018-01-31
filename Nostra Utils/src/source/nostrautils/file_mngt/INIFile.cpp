#include "nostrautils\file_mngt\INIFile.hpp"
#include <string>
#include <fstream>
#include <iostream>

namespace NOU::NOU_FILE_MNGT
{
	INIFile::INIFile(const std::string & filename)
	{
		m_filename = filename;
		m_data_sections.insert(std::make_pair(INI_DEFAULT_SECTION, 0));
	}


	void INIFile::incSection(const std::string & section)
	{
		if (m_data_sections.count(section) == 0) {
			m_data_sections.insert(std::make_pair(section, 1));
			return;
		}

		std::unordered_map<std::string, int32>::const_iterator i = m_data_sections.find(section);
		int32 value = i->second + 1;

		m_data_sections.erase(section);
		m_data_sections.insert(std::make_pair(section, value));
	}


	void INIFile::decSection(const std::string & section)
	{
		if (m_data_sections.count(section) == 0) {
			return;
		}

		std::unordered_map<std::string, int32>::const_iterator i = m_data_sections.find(section);
		int32 value = i->second - 1;

		m_data_sections.erase(section);
		m_data_sections.insert(std::make_pair(section, value));
	}


	std::string INIFile::parseKey(const std::string &line) const
	{
		return this->parseCleanString(line);
	}


	std::string INIFile::parseStringValue(const std::string & line, const int32 quote_type)
	{
		int32 pos_quote_first;
		int32 pos_quote_last;
		char quote;

		// Clean line
		std::string value = this->parseCleanString(line);

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
		int32 quote_type;

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

		quote_type = this->parseValueQuote(line_rgt);

		if (quote_type == INI_QUOTE_NONE) {
			if (line_rgt.find_first_of('.') == std::string::npos) {
				// Add int
				this->setInt(this->parseKey(line_lft), this->parseIntValue(line_rgt), section);
			}

			// Add float
			this->setFloat(this->parseKey(line_lft), this->parseFloatValue(line_rgt), section);
			return;
		}

		// Add string
		this->setString(this->parseKey(line_lft), this->parseStringValue(line_rgt, quote_type), section);
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


	boolean INIFile::write(const std::string & filename)
	{
		std::unordered_map<std::string, std::string>::const_iterator istr;
		std::unordered_map<std::string, int32>::const_iterator iint;
		std::unordered_map<std::string, float32>::const_iterator ifloat;
		std::ofstream inifile;
		std::string key_section;
		int32 pos_dot;
		int32 pos_sec;
		
		// Open file stream
		if (!filename.empty()) {
			inifile.open(filename);
		}
		else {
			inifile.open(this->m_filename);
		}
		
		if (!inifile) {
			return false;
		}

		// Loop through all the sections
		for (auto isec = m_data_sections.begin(); isec != m_data_sections.end(); ++isec)
		{
			// Write section
			if (isec->first != INI_DEFAULT_SECTION && isec->second > 0) {
				inifile << "[" << isec->first << "]" << std::endl;
			}

			// Save string size for later
			pos_sec = isec->first.length();

			// Write string data
			for (istr = m_data_string.begin(); istr != m_data_string.end(); ++istr)
			{
				pos_dot = istr->first.find_first_of('.');
				if (pos_dot == std::string::npos) continue;

				key_section = istr->first.substr(0, pos_dot);
				if (key_section != isec->first) continue;

				inifile << istr->first.substr(pos_sec + 1) << " = ";
				inifile << "\"" << istr->second << "\"" << std::endl;
			}

			// Write int data
			for (iint = m_data_integer.begin(); iint != m_data_integer.end(); ++iint)
			{
				pos_dot = iint->first.find_first_of('.');
				if (pos_dot == std::string::npos) continue;

				key_section = iint->first.substr(0, pos_dot);
				if (key_section != isec->first) continue;

				inifile << iint->first.substr(pos_sec + 1) << " = ";
				inifile << iint->second << std::endl;
			}

			// Write float data
			for (ifloat = m_data_float.begin(); ifloat != m_data_float.end(); ++ifloat)
			{
				pos_dot = ifloat->first.find_first_of('.');
				if (pos_dot == std::string::npos) continue;

				key_section = ifloat->first.substr(0, pos_dot);
				if (key_section != isec->first) continue;

				inifile << ifloat->first.substr(pos_sec + 1) << " = ";
				inifile << ifloat->second << std::endl;
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

		this->decSection(section);
	}


	void INIFile::setString(const std::string & key, const std::string & value, const std::string & section)
	{
		this->remove(key, section);
		this->incSection(section);
		
		m_data_string.insert(std::make_pair(section + "." + key, value));
	}


	void INIFile::setInt(const std::string & key, const int32 value, const std::string & section)
	{
		this->remove(key, section);
		this->incSection(section);

		m_data_integer.insert(std::make_pair(section + "." + key, value));
	}


	void INIFile::setFloat(const std::string & key, const float32 value, const std::string & section)
	{
		this->remove(key, section);
		this->incSection(section);

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

		// Search in integer map and cast to float if found
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