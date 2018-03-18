#include "nostrautils\file_mngt\INIFile.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include <string>
#include <fstream>
#include <iostream>


namespace NOU::NOU_FILE_MNGT
{
	using NouString = NOU::NOU_DAT_ALG::String<char8>;

	INIFile::INIFile(const NouString & filename)
	{
		m_filename.insert(0, filename);
		m_data_sections.insert(std::make_pair(INI_DEFAULT_SECTION, 0));
	}


	void INIFile::incSection(const NouString & section)
	{
		if (m_data_sections.count(section) == 0) {
			m_data_sections.insert(std::make_pair(section, 1));
			return;
		}

		std::unordered_map<NouString, int32>::const_iterator i = m_data_sections.find(section);
		int32 value = i->second + 1;

		m_data_sections.erase(section);
		m_data_sections.insert(std::make_pair(section, value));
	}


	void INIFile::decSection(const NouString & section)
	{
		if (m_data_sections.count(section) == 0) {
			return;
		}

		std::unordered_map<NouString, int32>::const_iterator i = m_data_sections.find(section);
		int32 value = i->second - 1;

		m_data_sections.erase(section);
		m_data_sections.insert(std::make_pair(section, value));
	}


	NouString INIFile::parseKey(NouString &line) const
	{
		return line.trim();
	}


	NouString INIFile::parseStringValue(NouString & line, const int32 quote_type)
	{
		int32 pos_quote_first;
		int32 pos_quote_last;
		char quote;

		// Clean line
		NouString value = line.trim();

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

		pos_quote_first = line.firstIndexOf(quote) + 1;
		pos_quote_last = line.lastIndexOf(quote);

		value.clear().append(line.substring(pos_quote_first, pos_quote_last - pos_quote_first));

		return value;
	}


	int32 INIFile::parseIntValue(const NouString &line)
	{
		return line.stringToInt32(line);
	}


	float32 INIFile::parseFloatValue(const NouString &line)
	{
		return line.stringToFloat32(line);
	}


	int32 INIFile::parseValueQuote(const NouString & line) const
	{
		int32 pos_quote_dbl = line.firstIndexOf('"');
		int32 pos_quote_sin = line.firstIndexOf('\'');

		// Return INI_QUOTE_NONE if no quotes
		if (pos_quote_dbl == pos_quote_sin) {
			return INI_QUOTE_NONE;
		}

		// Return INI_QUOTE_DOUBLE for double quoation marks
		if (pos_quote_sin == NouString::NULL_INDEX) {
			return INI_QUOTE_DOUBLE;
		}

		// Return INI_QUOTE_SINGLE for single quotation marks
		return INI_QUOTE_SINGLE;
	}


	void INIFile::parseLine(NouString & line, const NouString & section)
	{
		NouString line_lft;
		NouString line_rgt;
		int32 pos_eq;
		int32 quote_type;

		// Get position of the first equal symbol
		pos_eq = line.firstIndexOf('=');

		// Check if we have an equal symbol
		if (pos_eq == NouString::NULL_INDEX) {
			return;
		}

		// Check if first char indicates comment
		if (line.at(0) == ';') {
			return;
		}

		// Split the string into a left and right part
		line_lft.clear().append(line.substring(0, pos_eq));
		line_rgt.clear().append(line.substring(pos_eq + 1));

		quote_type = this->parseValueQuote(line_rgt);

		if (quote_type == INI_QUOTE_NONE) {
			if (line_rgt.firstIndexOf('.') == NouString::NULL_INDEX) {
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
		NouString line;
		NouString section;

		// Open file stream
		inifile.open(this->m_filename.rawStr());

		if (!inifile) {
			return false;
		}

		// Set the default section
		section.append(INI_DEFAULT_SECTION);

		// Parse file content line by line
		while (std::getline(inifile, line))
		{
			line.clear().append(line.trim());

			// Check if we have a section
			if (line.at(0) == '[' && line.at((line.size() - 1)) == ']') {
				section.clear().append(line.substring(1, line.size() - 2));
			}
			else {
				this->parseLine(line, section);
			}
		}

		inifile.close();

		return true;
	}


	boolean INIFile::write(const NouString & filename)
	{
		std::unordered_map<NouString, NouString>::const_iterator istr;
		std::unordered_map<NouString, int32>::const_iterator iint;
		std::unordered_map<NouString, float32>::const_iterator ifloat;
		std::ofstream inifile;
		NouString key_section;
		int32 pos_dot;
		int32 pos_sec;
		
		// Open file stream
		if (!filename.size()) {
			inifile.open(filename);
		}
		else {
			inifile.open(this->m_filename.rawStr());
		}
		
		if (!inifile) {
			return false;
		}

		// Loop through all the sections
		for (auto isec = m_data_sections.begin(); isec != m_data_sections.end(); ++isec)
		{
			// Write section
			if (isec->first != INI_DEFAULT_SECTION && isec->second > 0) {
				inifile << "[" << isec->first.rawStr() << "]" << std::endl;
			}

			// Save string size for later
			pos_sec = isec->first.size();

			// Write string data
			for (istr = m_data_string.begin(); istr != m_data_string.end(); ++istr)
			{
				pos_dot = istr->first.firstIndexOf('.');
				if (pos_dot == NouString::NULL_INDEX) continue;

				key_section.clear().append(istr->first.substring(0, pos_dot));
				if (key_section != isec->first) continue;

				inifile << istr->first.substring(pos_sec + 1).rawStr() << " = ";
				inifile << "\"" << istr->second.rawStr() << "\"" << std::endl;
			}

			// Write int data
			for (iint = m_data_integer.begin(); iint != m_data_integer.end(); ++iint)
			{
				pos_dot = iint->first.firstIndexOf('.');
				if (pos_dot == NouString::NULL_INDEX) continue;

				key_section.clear().append(iint->first.substring(0, pos_dot));
				if (key_section != isec->first) continue;

				inifile << iint->first.substring(pos_sec + 1).rawStr() << " = ";
				inifile << iint->second << std::endl;
			}

			// Write float data
			for (ifloat = m_data_float.begin(); ifloat != m_data_float.end(); ++ifloat)
			{
				pos_dot = ifloat->first.firstIndexOf('.');
				if (pos_dot == NouString::NULL_INDEX) continue;

				key_section.clear().append(ifloat->first.substring(0, pos_dot));
				if (key_section != isec->first) continue;

				inifile << ifloat->first.substring(pos_sec + 1).rawStr() << " = ";
				inifile << ifloat->second << std::endl;
			}
		}

		inifile.close();

		return true;
	}


	void INIFile::remove(const NouString & key, const NouString & section)
	{
		NouString search = section + "." + key;

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


	void INIFile::setString(const NouString & key, const NouString & value, const NouString & section)
	{
		this->remove(key, section);
		this->incSection(section);
		
		m_data_string.insert(std::make_pair(section + "." + key, value));
	}


	void INIFile::setInt(const NouString & key, const int32 value, const NouString & section)
	{
		this->remove(key, section);
		this->incSection(section);

		m_data_integer.insert(std::make_pair(section + "." + key, value));
	}


	void INIFile::setFloat(const NouString & key, const float32 value, const NouString & section)
	{
		this->remove(key, section);
		this->incSection(section);

		m_data_float.insert(std::make_pair(section + "." + key, value));
	}


	NouString INIFile::getString(const NouString & key, const NouString & section) const
	{
		NouString search = section + "." + key;
		std::unordered_map<NouString, NouString>::const_iterator i = m_data_string.find(search);
		
		if (i != m_data_string.end()) {
			return i->second;
		}

		// Search in integer map and cast to string if found
		if (m_data_integer.count(search) > 0) {
			return NouString(this->getInt(key, section));
		}

		// Search in float map and cast to string if found
		if (m_data_float.count(search) > 0) {
			return NouString(this->getFloat(key, section));
		}

		return NouString();
	}


	int32 INIFile::getInt(const NouString & key, const NouString & section) const
	{
		NouString search = section + "." + key;
		std::unordered_map<NouString, int32>::const_iterator i = m_data_integer.find(search);

		if (i != m_data_integer.end()) {
			return i->second;
		}

		// Search in string map and cast to int if found
		if (m_data_string.count(search) > 0) {
			return key.stringToInt32(this->getString(key, section));
		}

		// Search in float map and cast to int if found
		if (m_data_float.count(search) > 0) {
			return static_cast<int32>(this->getFloat(key, section));
		}

		return 0;
	}


	float32 INIFile::getFloat(const NouString & key, const NouString & section) const
	{
		NouString search = section + "." + key;
		std::unordered_map<NouString, float32>::const_iterator i = m_data_float.find(search);

		if (i != m_data_float.end()) {
			return i->second;
		}

		// Search in string map and cast to float if found
		if (m_data_string.count(search) > 0) {
			return key.stringToFloat32(this->getString(key, section));
		}

		// Search in integer map and cast to float if found
		if (m_data_integer.count(search) > 0) {
			return static_cast<float32>(this->getInt(key, section));
		}
		
		return 0.0;
	}


	boolean INIFile::keyExists(const NouString & key, const NouString & section) const
	{
		NouString search = section + "." + key;

		return (m_data_string.count(search) > 0 || m_data_integer.count(search) > 0 || m_data_float.count(search) > 0);
	}
}