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
		m_filename = filename;
		m_dataSections.map(INI_DEFAULT_SECTION, 0);
	}


	void INIFile::incSection(const NouString & section)
	{
		if (!m_dataSections.containsKey(section)) {
			m_dataSections.map(section, 1);
			return;
		}

		int32 value = m_dataSections.get(section) + 1;

		m_dataSections.remove(section);
		m_dataSections.map(section, value);
	}


	void INIFile::decSection(const NouString & section)
	{
		if (!m_dataSections.containsKey(section)) {
			return;
		}

		int32 value = m_dataSections.get(section) - 1;

		m_dataSections.remove(section);

		if (value > 0) {
			m_dataSections.map(section, value);
		}
	}


	INIFile::NouString INIFile::parseKey(const NouString &line) const
	{
		return line.copy().trim();
	}


	INIFile::NouString INIFile::parseStringValue(const NouString & line, const int32 quoteType) const
	{
		int32 posQuoteFirst;
		int32 posQuoteLast;
		char quote;

		// Clean line
		NouString value = line.copy().trim();

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


	int32 INIFile::parseIntValue(const NouString &line) const
	{
		return std::stoi(line.rawStr());
	}


	float32 INIFile::parseFloatValue(const NouString &line) const
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


	void INIFile::parseLine(const NouString & line, const NouString & section)
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
		if (line.copy().at(0) == ';') {
			return;
		}

		// Split the string into a left and right part
		lineLft = line.substring(0, posEq);
		lineRgt = line.substring(posEq + 1);
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

		if (!inifile.good()) {
			inifile.close();
			return false;
		}

		// Set the default section
		section = INI_DEFAULT_SECTION;

		// Parse file content line by line
		while (std::getline(inifile, ln))
		{
			line = NouString(ln.c_str());

			if (line.size() == 0) {
				continue;
			}

			line.trim();

			if (line.size() == 0) {
				continue;
			}

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
		NOU::NOU_DAT_ALG::Vector<const NouString *> sectionKeys = m_dataSections.keySet();
		NOU::NOU_DAT_ALG::Vector<const int32 *> sectionValues = m_dataSections.entrySet();
		NOU::NOU_DAT_ALG::Vector<const NouString *> stringKeys = m_dataString.keySet();
		NOU::NOU_DAT_ALG::Vector<const NouString *> stringValues = m_dataString.entrySet();
		NOU::NOU_DAT_ALG::Vector<const NouString *> integerKeys = m_dataInteger.keySet();
		NOU::NOU_DAT_ALG::Vector<const int32 *> integerValues = m_dataInteger.entrySet();
		NOU::NOU_DAT_ALG::Vector<const NouString *> floatKeys = m_dataFloat.keySet();
		NOU::NOU_DAT_ALG::Vector<const float32 *> floatValues = m_dataFloat.entrySet();

		std::ofstream inifile;
		NouString key_section;
		int32 pos_dot;
		int32 pos_sec;

		// Open file stream
		if (filename.size()) {
			inifile = std::ofstream(filename.rawStr(), std::ofstream::trunc);
		}
		else {
			inifile = std::ofstream(this->m_filename.rawStr(), std::ofstream::trunc);
		}

		if (!inifile.is_open()) {
			return false;
		}

		// Loop through all the sections
		for (int32 isec = (sectionKeys.size() - 1); isec >= 0; isec--)
		{
			// Write section
			if (*sectionValues.at(isec) > 0) {
				if (sectionKeys.at(isec)->rawStr() != INI_DEFAULT_SECTION) {
					inifile << "[" << sectionKeys.at(isec)->rawStr() << "]" << std::endl;
				}
			}

			// Save string size for later
			pos_sec = sectionKeys.at(isec)->size();

			// Write string data
			for (auto istr = 0; istr < stringKeys.size(); istr++)
			{
				pos_dot = stringKeys.at(istr)->firstIndexOf('.');
				if (pos_dot == NouString::NULL_INDEX) continue;

				key_section = stringKeys.at(istr)->substring(0, pos_dot);
				if (key_section != sectionKeys.at(isec)->rawStr()) continue;

				inifile << stringKeys.at(istr)->substring(pos_sec + 1).rawStr() << " = ";
				inifile << "\"" << stringValues.at(istr)->rawStr() << "\"" << std::endl;
			}

			// Write int data
			for (auto iint = 0; iint < integerKeys.size(); iint++)
			{
				pos_dot = integerKeys.at(iint)->firstIndexOf('.');
				if (pos_dot == NouString::NULL_INDEX) continue;

				key_section = integerKeys.at(iint)->substring(0, pos_dot);
				if (key_section != sectionKeys.at(isec)->rawStr()) continue;

				inifile << integerKeys.at(iint)->substring(pos_sec + 1).rawStr() << " = ";
				inifile << integerValues.at(iint) << std::endl;
			}

			// Write float data
			for (auto ifloat = 0; ifloat < floatKeys.size(); ifloat++)
			{
				pos_dot = floatKeys.at(ifloat)->firstIndexOf('.');
				if (pos_dot == NouString::NULL_INDEX) continue;

				key_section = floatKeys.at(ifloat)->substring(0, pos_dot);
				if (key_section != sectionKeys.at(isec)->rawStr()) continue;

				inifile << floatKeys.at(ifloat)->substring(pos_sec + 1).rawStr() << " = ";
				inifile << floatValues.at(ifloat) << std::endl;
			}
		}

		inifile.close();

		return true;
	}


	void INIFile::remove(const NouString & key, const NouString & section)
	{
		NouString search = section + "." + key;

		if (m_dataString.containsKey(search)) {
			m_dataString.remove(search);
		}
		else if (m_dataInteger.containsKey(search)) {
			m_dataInteger.remove(search);
		}
		else if (m_dataFloat.containsKey(search)) {
			m_dataFloat.remove(search);
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

		m_dataString.map(NouString(section + "." + key), value);
	}


	void INIFile::setInt(const NouString & key, const int32 value, const NouString & section)
	{
		this->remove(key, section);
		this->incSection(section);

		m_dataInteger.map(NouString(section + "." + key), value);
	}


	void INIFile::setFloat(const NouString & key, const float32 value, const NouString & section)
	{
		this->remove(key, section);
		this->incSection(section);

		m_dataFloat.map(NouString(section + "." + key), value);
	}


	INIFile::NouString INIFile::getString(const NouString & key, const NouString & section)
	{
		const NouString search = section + "." + key;

		if (m_dataString.containsKey(search)) {
			return m_dataString.get(search);
		}

		// Search in integer map and cast to string if found
		if (m_dataInteger.containsKey(search)) {
			return NouString(this->getInt(key, section));
		}

		// Search in float map and cast to string if found
		if (m_dataFloat.containsKey(search)) {
			return NouString(this->getFloat(key, section));
		}

		return NouString();
	}


	int32 INIFile::getInt(const NouString & key, const NouString & section)
	{
		const NouString search = section + "." + key;

		if (m_dataInteger.containsKey(search)) {
			return m_dataInteger.get(search);
		}

		// Search in string map and cast to int if found
		if (m_dataString.containsKey(search)) {
			return key.stringToInt32(this->getString(key, section));
		}

		// Search in float map and cast to int if found
		if (m_dataFloat.containsKey(search)) {
			return static_cast<int32>(this->getFloat(key, section));
		}

		return 0;
	}


	float32 INIFile::getFloat(const NouString & key, const NouString & section)
	{
		const NouString search = section + "." + key;

		if (m_dataFloat.containsKey(search)) {
			return m_dataFloat.get(search);
		}

		// Search in string map and cast to float if found
		if (m_dataString.containsKey(search)) {
			return key.stringToFloat32(this->getString(key, section));
		}

		// Search in integer map and cast to float if found
		if (m_dataInteger.containsKey(search)) {
			return static_cast<float32>(this->getInt(key, section));
		}

		return 0.0;
	}


	boolean INIFile::keyExists(const NouString & key, const NouString & section)
	{
		NouString search = NouString(section + "." + key);

		return (m_dataString.containsKey(search) || m_dataInteger.containsKey(search) || m_dataFloat.containsKey(search));
	}


	NOU::NOU_DAT_ALG::HashMap<INIFile::NouString, INIFile::NouString> INIFile::getKeys()
	{
		NOU::NOU_DAT_ALG::HashMap<NouString, NouString> keys = NOU::NOU_DAT_ALG::HashMap<NouString, NouString>();

		NOU::NOU_DAT_ALG::Vector<const NouString *> sectionKeys = m_dataSections.keySet();
		NOU::NOU_DAT_ALG::Vector<const int32 *> sectionValues = m_dataSections.entrySet();
		NOU::NOU_DAT_ALG::Vector<const NouString *> stringKeys = m_dataString.keySet();
		NOU::NOU_DAT_ALG::Vector<const NouString *> integerKeys = m_dataInteger.keySet();
		NOU::NOU_DAT_ALG::Vector<const NouString *> floatKeys = m_dataFloat.keySet();

		NouString key_section;
		int32 pos_dot;
		int32 pos_sec;

		// Loop through all the sections
		for (int32 isec = (sectionKeys.size() - 1); isec >= 0; isec--)
		{
			// Save string size for later
			pos_sec = sectionKeys.at(isec)->size();

			// Get keys from string map
			for (auto istr = 0; istr < stringKeys.size(); istr++)
			{
				pos_dot = stringKeys.at(istr)->firstIndexOf('.');
				if (pos_dot == NouString::NULL_INDEX) continue;

				key_section = stringKeys.at(istr)->substring(0, pos_dot);
				if (key_section != sectionKeys.at(isec)->rawStr()) continue;

				keys.map(stringKeys.at(istr)->substring(pos_sec + 1).rawStr(), key_section);
			}

			// Get keys from int map
			for (auto iint = 0; iint < integerKeys.size(); iint++)
			{
				pos_dot = integerKeys.at(iint)->firstIndexOf('.');
				if (pos_dot == NouString::NULL_INDEX) continue;

				key_section = integerKeys.at(iint)->substring(0, pos_dot);
				if (key_section != sectionKeys.at(isec)->rawStr()) continue;

				keys.map(integerKeys.at(iint)->substring(pos_sec + 1).rawStr(), key_section);
			}

			// Get keys from float data
			for (auto ifloat = 0; ifloat < floatKeys.size(); ifloat++)
			{
				pos_dot = floatKeys.at(ifloat)->firstIndexOf('.');
				if (pos_dot == NouString::NULL_INDEX) continue;

				key_section = floatKeys.at(ifloat)->substring(0, pos_dot);
				if (key_section != sectionKeys.at(isec)->rawStr()) continue;

				keys.map(floatKeys.at(ifloat)->substring(pos_sec + 1).rawStr(), key_section);
			}
		}

		return keys;
	}


	int32 INIFile::getDataType(const NouString &key, const NouString & section)
	{
		NouString search = section + "." + key;

		if (m_dataString.containsKey(search)) {
			return INI_TYPE_NouString;
		}

		if (m_dataInteger.containsKey(search)) {
			return INI_TYPE_INT;
		}

		if (m_dataFloat.containsKey(search)) {
			return INI_TYPE_FLOAT;
		}

		return 0;
	}


	void INIFile::merge(INIFile & other)
	{
		NOU::NOU_DAT_ALG::HashMap<NouString, NouString> otherKeySections = other.getKeys();

		NOU::NOU_DAT_ALG::Vector<const NouString *> keys = otherKeySections.keySet();
		NOU::NOU_DAT_ALG::Vector<const NouString *> sections = otherKeySections.entrySet();

		NouString key, section;

		// Loop through all the keys
		for (int32 i = (keys.size() - 1); i >= 0; i--)
		{
			key = keys.at(i)->rawStr();
			section = sections.at(i)->rawStr();

			switch (other.getDataType(key, section))
			{
			case INI_TYPE_NouString:
				this->setString(key, other.getString(key, section), section);
				break;

			case INI_TYPE_INT:
				this->setInt(key, other.getInt(key, section), section);
				break;

			case INI_TYPE_FLOAT:
				this->setFloat(key, other.getFloat(key, section), section);
				break;
			}
		}
	}
}