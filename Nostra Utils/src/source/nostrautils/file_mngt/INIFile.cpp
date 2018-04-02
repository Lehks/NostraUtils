#include "nostrautils\file_mngt\INIFile.hpp"
#include "nostrautils\dat_alg\String.hpp"
#include "nostrautils\dat_alg\Vector.hpp"
#include <string>
#include <fstream>
#include <iostream>


namespace NOU::NOU_FILE_MNGT
{
	using NouString = NOU::NOU_DAT_ALG::String<char8>;

	INIFile::INIFile(const NouString & filename)
	{
		m_filename.insert(0, filename);
		m_data_sections.map(INI_DEFAULT_SECTION, 0);
	}


	void INIFile::incSection(const NouString & section)
	{
		if (!m_data_sections.containsKey(section)) {
			m_data_sections.map(section, 1);
			return;
		}

		int32 value = m_data_sections.get(section) + 1;

		m_data_sections.remove(section);
		m_data_sections.map(section, value);
	}


	void INIFile::decSection(const NouString & section)
	{
		int32 value = m_data_sections.get(section) - 1;

		if (value < 0) {
			return;
		}

		m_data_sections.remove(section);
		m_data_sections.map(section, value);
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
		std::string ln;
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
		while (std::getline(inifile, ln))
		{
			line.clear().append(NouString(ln.c_str()).trim());

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
		NOU::NOU_DAT_ALG::Vector<NouString> section_keys = m_data_sections.keySet();
		NOU::NOU_DAT_ALG::Vector<int32> section_values = m_data_sections.entrySet();
		NOU::NOU_DAT_ALG::Vector<NouString> string_keys = m_data_string.keySet();
		NOU::NOU_DAT_ALG::Vector<NouString> string_values = m_data_string.entrySet();
		NOU::NOU_DAT_ALG::Vector<NouString> integer_keys = m_data_integer.keySet();
		NOU::NOU_DAT_ALG::Vector<int32> integer_values = m_data_integer.entrySet();
		NOU::NOU_DAT_ALG::Vector<NouString> float_keys = m_data_float.keySet();
		NOU::NOU_DAT_ALG::Vector<float32> float_values = m_data_float.entrySet();

		std::ofstream inifile;
		NouString key_section;
		int32 pos_dot;
		int32 pos_sec;
		
		// Open file stream
		if (!filename.size()) {
			inifile.open(filename.rawStr());
		}
		else {
			inifile.open(this->m_filename.rawStr());
		}
		
		if (!inifile) {
			return false;
		}

		// Loop through all the sections
		for (auto isec = 0; isec < section_keys.size(); isec++)
		{
			// Write section
			if (section_keys.at(isec) != INI_DEFAULT_SECTION && section_values.at(isec) > 0) {
				inifile << "[" << section_keys.at(isec).rawStr() << "]" << std::endl;
			}

			// Save string size for later
			pos_sec = section_keys.at(isec).size();

			// Write string data
			for (auto istr = 0; istr < string_keys.size(); istr++)
			{
				pos_dot = string_keys.at(istr).firstIndexOf('.');
				if (pos_dot == NouString::NULL_INDEX) continue;

				key_section.clear().append(string_keys.at(istr).substring(0, pos_dot));
				if (key_section != string_keys.at(istr)) continue;

				inifile << string_keys.at(istr).substring(pos_sec + 1).rawStr() << " = ";
				inifile << "\"" << string_values.at(istr).rawStr() << "\"" << std::endl;
			}

			// Write int data
			for (auto iint = 0; iint < integer_keys.size(); iint++)
			{
				pos_dot = integer_keys.at(iint).firstIndexOf('.');
				if (pos_dot == NouString::NULL_INDEX) continue;

				key_section.clear().append(integer_keys.at(iint).substring(0, pos_dot));
				if (key_section != integer_keys.at(iint)) continue;

				inifile << integer_keys.at(iint).substring(pos_sec + 1).rawStr() << " = ";
				inifile << integer_values.at(iint) << std::endl;
			}

			// Write float data
			for (auto ifloat = 0; ifloat < float_keys.size(); ifloat++)
			{
				pos_dot = float_keys.at(ifloat).firstIndexOf('.');
				if (pos_dot == NouString::NULL_INDEX) continue;

				key_section.clear().append(float_keys.at(ifloat).substring(0, pos_dot));
				if (key_section != float_keys.at(ifloat)) continue;

				inifile << float_keys.at(ifloat).substring(pos_sec + 1).rawStr() << " = ";
				inifile << float_values.at(ifloat) << std::endl;
			}
		}

		inifile.close();

		return true;
	}


	void INIFile::remove(const NouString & key, const NouString & section)
	{
		NouString search = section + "." + key;

		if (m_data_string.containsKey(search)) {
			m_data_string.remove(search);
		}
		else if (m_data_integer.containsKey(search)) {
			m_data_integer.remove(search);
		}
		else if (m_data_float.containsKey(search)) {
			m_data_float.remove(search);
		}

		this->decSection(section);
	}


	void INIFile::setString(const NouString & key, const NouString & value, const NouString & section)
	{
		this->remove(key, section);
		this->incSection(section);
		
		m_data_string.map(section + "." + key, value);
	}


	void INIFile::setInt(const NouString & key, const int32 value, const NouString & section)
	{
		this->remove(key, section);
		this->incSection(section);

		m_data_integer.map(section + "." + key, value);
	}


	void INIFile::setFloat(const NouString & key, const float32 value, const NouString & section)
	{
		this->remove(key, section);
		this->incSection(section);

		m_data_float.map(section + "." + key, value);
	}


	NouString INIFile::getString(const NouString & key, const NouString & section)
	{
		NouString search = section + "." + key;

		if (m_data_string.containsKey(search)) {
			return m_data_string.get(search);
		}

		// Search in integer map and cast to string if found
		if (m_data_integer.containsKey(search)) {
			return NouString(this->getInt(key, section));
		}

		// Search in float map and cast to string if found
		if (m_data_float.containsKey(search)) {
			return NouString(this->getFloat(key, section));
		}

		return NouString();
	}


	int32 INIFile::getInt(const NouString & key, const NouString & section)
	{
		NouString search = section + "." + key;

		if (m_data_integer.containsKey(search)) {
			return m_data_integer.get(search);
		}

		// Search in string map and cast to int if found
		if (m_data_string.containsKey(search)) {
			return key.stringToInt32(this->getString(key, section));
		}

		// Search in float map and cast to int if found
		if (m_data_float.containsKey(search)) {
			return static_cast<int32>(this->getFloat(key, section));
		}

		return 0;
	}


	float32 INIFile::getFloat(const NouString & key, const NouString & section)
	{
		NouString search = section + "." + key;

		if (m_data_float.containsKey(search)) {
			return m_data_float.get(search);
		}

		// Search in string map and cast to float if found
		if (m_data_string.containsKey(search)) {
			return key.stringToFloat32(this->getString(key, section));
		}

		// Search in integer map and cast to float if found
		if (m_data_integer.containsKey(search)) {
			return static_cast<float32>(this->getInt(key, section));
		}
		
		return 0.0;
	}


	boolean INIFile::keyExists(const NouString & key, const NouString & section)
	{
		NouString search = section + "." + key;

		return (m_data_string.containsKey(search) || m_data_integer.containsKey(search) || m_data_float.containsKey(search));
	}
}