#include "nostrautils/file_mngt/INIFile.hpp"
#include "nostrautils/dat_alg/String.hpp"
#include "nostrautils/dat_alg/Vector.hpp"
#include <string>
#include <fstream>
#include <iostream>


namespace NOU::NOU_FILE_MNGT
{
	INIFile::INIFile(const NouString & filename)
	{
		m_filename.insert(0, filename);
		m_dataSections.insert(std::make_pair(INI_DEFAULT_SECTION, 0));
	}


	void INIFile::incSection(const NouString & section)
	{
		std::unordered_map<NouString, int32>::const_iterator i = m_dataSections.find(section);
		
		if (i == m_dataSections.end()) {
			m_dataSections.insert(std::make_pair(section, 1));
			return;
		}
		
		int32 value = i->second + 1;
		
		m_dataSections.erase(section);
		m_dataSections.insert(std::make_pair(section, value));
	}
	

	void INIFile::decSection(const NouString & section)
	{
		std::unordered_map<NouString, int32>::const_iterator i = m_dataSections.find(section);

		if (i == m_dataSections.end()) {
			return;
		}

		int32 value = i->second - 1;

		m_dataSections.erase(section);

		if (value > 0) {
			m_dataSections.insert(std::make_pair(section, value));
		}
	}


	NouString INIFile::parseKey(NouString &line) const
	{
		return line.trim();
	}


	NouString INIFile::parseStringValue(NouString & line, const int32 quoteType)
	{
		int32 posQuoteFirst;
		int32 posQuoteLast;
		char quote;

		// Clean line
		NouString value = line.trim();

		// If there are no quotes, we are done here.
		if (quoteType == INI_QUOTE_NONE) {
			return value;
		}

		if (quoteType == INI_QUOTE_DOUBLE) {
			quote = '"';
		}
		else {
			quote = '\'';
		}

		posQuoteFirst = line.firstIndexOf(quote) + 1;
		posQuoteLast = line.lastIndexOf(quote);

		value = line.substring(posQuoteFirst, posQuoteLast - (posQuoteFirst - 1));

		return value;
	}


	int32 INIFile::parseIntValue(const NouString &line)
	{
		return std::stoi(line.rawStr());
	}


	float32 INIFile::parseFloatValue(const NouString &line)
	{
		return std::stof(line.rawStr());
	}


	int32 INIFile::parseValueQuote(const NouString & line) const
	{
		int32 posQuoteDbl = line.firstIndexOf('"');
		int32 posQuoteSin = line.firstIndexOf('\'');

		// Return INI_QUOTE_NONE if no quotes
		if (posQuoteDbl == posQuoteSin) {
			return INI_QUOTE_NONE;
		}

		// Return INI_QUOTE_DOUBLE for double quoation marks
		if (posQuoteSin == NouString::NULL_INDEX) {
			return INI_QUOTE_DOUBLE;
		}

		// Return INI_QUOTE_SINGLE for single quotation marks
		return INI_QUOTE_SINGLE;
	}


	void INIFile::parseLine(NouString & line, const NouString & section)
	{
		NouString lineLft;
		NouString lineRgt;
		int32 posEq;
		int32 quoteType;

		// Get position of the first equal symbol
		posEq = line.firstIndexOf('=');

		// Check if we have an equal symbol
		if (posEq == NouString::NULL_INDEX) {
			return;
		}

		// Check if first char indicates comment
		if (line.at(0) == ';') {
			return;
		}

		// Split the string into a left and right part
		lineLft   = line.substring(0, posEq);
		lineRgt   = line.substring(posEq + 1);
		quoteType = this->parseValueQuote(lineRgt);

		if (quoteType == INI_QUOTE_NONE) {
			if (lineRgt.firstIndexOf('.') == NouString::NULL_INDEX) {
				// Add int
				this->setInt(this->parseKey(lineLft), this->parseIntValue(lineRgt), section);
			}
			else {
				// Add float
				this->setFloat(this->parseKey(lineLft), this->parseFloatValue(lineRgt), section);
			}

			return;
		}

		// Add string
		this->setString(this->parseKey(lineLft), this->parseStringValue(lineRgt, quoteType), section);
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
		section = INI_DEFAULT_SECTION;

		// Parse file content line by line
		while (std::getline(inifile, ln))
		{
			line = NouString(ln.c_str()).trim();

			// Check if we have a section
			if (line.at(0) == '[' && line.at((line.size() - 1)) == ']') {
				section = line.substring(1, line.size() - 1).trim();
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
		/*
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

		return true;*/
		std::unordered_map<NouString, NouString>::const_iterator istr;
		std::unordered_map<NouString, int32>::const_iterator iint;
		std::unordered_map<NouString, float32>::const_iterator ifloat;
		std::ofstream inifile;
		NouString keySection;
		int32 posDot;
		int32 posSec;

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
		for (auto isec = m_dataSections.begin(); isec != m_dataSections.end(); ++isec)
		{
			// Write section
			if (isec->first != INI_DEFAULT_SECTION && isec->second > 0) {
				inifile << "[" << isec->first.rawStr() << "]" << std::endl;
			}

			// Save string size for later
			posSec = isec->first.size();

			// Write string data
			for (istr = m_dataString.begin(); istr != m_dataString.end(); ++istr)
			{
				posDot = istr->first.firstIndexOf('.');
				if (posDot == NouString::NULL_INDEX) continue;

				keySection = istr->first.substring(0, posDot);
				if (keySection != isec->first) continue;

				inifile << istr->first.substring(posSec + 1).rawStr() << " = ";
				inifile << "\"" << istr->second.rawStr() << "\"" << std::endl;
			}

			// Write int data
			for (iint = m_dataInteger.begin(); iint != m_dataInteger.end(); ++iint)
			{
				posDot = iint->first.firstIndexOf('.');
				if (posDot == NouString::NULL_INDEX) continue;

				keySection = iint->first.substring(0, posDot);
				if (keySection != isec->first) continue;

				inifile << iint->first.substring(posSec + 1).rawStr() << " = ";
				inifile << iint->second << std::endl;
			}

			// Write float data
			for (ifloat = m_dataFloat.begin(); ifloat != m_dataFloat.end(); ++ifloat)
			{
				posDot = ifloat->first.firstIndexOf('.');
				if (posDot == NouString::NULL_INDEX) continue;

				keySection = ifloat->first.substring(0, posDot);
				if (keySection != isec->first) continue;

				inifile << ifloat->first.substring(posSec + 1).rawStr() << " = ";
				inifile << ifloat->second << std::endl;
			}
		}

		inifile.close();

		return true;
	}


	void INIFile::remove(const NouString & key, const NouString & section)
	{
		NouString search = section + "." + key;

		if (m_dataString.count(search) > 0) {
			m_dataString.erase(search);
		}
		else if (m_dataInteger.count(search) > 0) {
			m_dataInteger.erase(search);
		}
		else if (m_dataFloat.count(search) > 0) {
			m_dataFloat.erase(search);
		}
		else {
			return;
		}

		this->decSection(section);
	}


	void INIFile::setString(const NouString & key, const NouString & value, const NouString & section)
	{
		this->remove(key, section);
		this->incSection(section);

		m_dataString.insert(std::make_pair(NouString(section + "." + key), value));
	}


	void INIFile::setInt(const NouString & key, const int32 value, const NouString & section)
	{
		this->remove(key, section);
		this->incSection(section);

		m_dataInteger.insert(std::make_pair(NouString(section + "." + key), value));
	}


	void INIFile::setFloat(const NouString & key, const float32 value, const NouString & section)
	{
		this->remove(key, section);
		this->incSection(section);

		m_dataFloat.insert(std::make_pair(NouString(section + "." + key), value));
	}


	NouString INIFile::getString(const NouString & key, const NouString & section)
	{
		NouString search = section + "." + key;
		std::unordered_map<NouString, NouString, INIFileHash>::const_iterator i = m_dataString.find(search);

		if (i != m_dataString.end()) {
			return i->second;
		}

		// Search in integer map and cast to string if found
		if (m_dataInteger.count(search) > 0) {
			return NouString(this->getInt(key, section));
		}

		// Search in float map and cast to string if found
		if (m_dataFloat.count(search) > 0) {
			return NouString(this->getFloat(key, section));
		}

		return NouString();
	}


	int32 INIFile::getInt(const NouString & key, const NouString & section)
	{
		NouString search = section + "." + key;
		std::unordered_map<NouString, int32>::const_iterator i = m_dataInteger.find(search);

		if (i != m_dataInteger.end()) {
			return i->second;
		}

		// Search in string map and cast to int if found
		if (m_dataString.count(search) > 0) {
			return key.stringToInt32(this->getString(key, section));
		}

		// Search in float map and cast to int if found
		if (m_dataFloat.count(search) > 0) {
			return static_cast<int32>(this->getFloat(key, section));
		}

		return 0;
	}


	float32 INIFile::getFloat(const NouString & key, const NouString & section)
	{
		NouString search = section + "." + key;
		std::unordered_map<NouString, float32>::const_iterator i = m_dataFloat.find(search);

		if (i != m_dataFloat.end()) {
			return i->second;
		}

		// Search in string map and cast to float if found
		if (m_dataString.count(search) > 0) {
			return key.stringToFloat32(this->getString(key, section));
		}

		// Search in integer map and cast to float if found
		if (m_dataInteger.count(search) > 0) {
			return static_cast<float32>(this->getInt(key, section));
		}

		return 0.0;
	}


	boolean INIFile::keyExists(const NouString & key, const NouString & section)
	{
		NouString search = NouString(section + "." + key);

		return (m_dataString.count(search) > 0 || m_dataInteger.count(search) > 0 || m_dataFloat.count(search) > 0);
	}
}