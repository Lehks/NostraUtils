#ifndef	NOU_MEM_MNGT_INI_DOCUMENT_HPP
#define	NOU_MEM_MNGT_INI_DOCUMENT_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/dat_alg/String.hpp"
#include "nostrautils/dat_alg/Hashing.hpp"
#include "nostrautils/dat_alg/HashMap.hpp"

/** \file INIFile.hpp
\author	 Tobias Kuhn
\since   1.0.0
\version 1.0.1
\brief   This file provides a class to parse .ini files.
*/

namespace NOU::NOU_FILE_MNGT
{
	class INIFile
	{
		public:
			using NouString = NOU::NOU_DAT_ALG::String<char8>;

			static constexpr const NOU::char8 *INI_DEFAULT_SECTION = "undefined";
			static constexpr int32 INI_QUOTE_NONE = 0;
			static constexpr int32 INI_QUOTE_DOUBLE = 1;
			static constexpr int32 INI_QUOTE_SINGLE = 2;
			static constexpr int32 INI_TYPE_NouString = 1;
			static constexpr int32 INI_TYPE_INT = 2;
			static constexpr int32 INI_TYPE_FLOAT = 3;

		private:
			/**
			\brief Holds the parsed key value pairs, with the values being NouStrings.
			*/
			NOU::NOU_DAT_ALG::HashMap<NouString, NouString> m_dataString;

			/**
			\brief Holds the parsed key value pairs, with the values being int32.
			*/
			NOU::NOU_DAT_ALG::HashMap<NouString, int32> m_dataInteger;

			/**
			\brief Holds the parsed key value pairs, with the values being float32.
			*/
			NOU::NOU_DAT_ALG::HashMap<NouString, float32> m_dataFloat;

			/**
			\brief Holds the parsed sections and the amount of keys within that section
			*/
			NOU::NOU_DAT_ALG::HashMap<NouString, int32> m_dataSections;

			/**
			\brief The target file name to read from/write to.
			*/
			NouString m_filename;

			/**
			\brief The name of the current section being parsed.
			*/
			NouString m_parserSection;

			/**
			\param line    A single line of text that should be parsed.
			\param section The section to which this line belongs.

			\brief Parses a single line from the file.
			*/
			NOU_FUNC void parseLine(const NouString & line, const NouString & section);

			/**
			\param line A single line of text.
			\return The parsed ini key.

			\brief Parses the key from a given line.
			*/
			NOU_FUNC NouString parseKey(const NouString & line) const;

			/**
			\param line      A single line of text to parse.
			\param quoteType The string value quotation style (single or double).
			\return The parsed ini value.

			\brief Parses the value from a given line as a NouString.
			*/
			NOU_FUNC NouString parseStringValue(const NouString & line, const int32 quoteType) const;

			/**
			\param line A single line of text.
			\return A parsed integer value.

			\brief Parses the value from a given line as an integer.
			*/
			NOU_FUNC int32 parseIntValue(const NouString & line) const;

			/**
			\param line A single line of text.
			\return A parsed float value.

			\brief Parses the value from a given line as a float.
			*/
			NOU_FUNC float32 parseFloatValue(const NouString &line) const;

			/**
			\param line A single line of text
			\return Quotation type flag.

			\brief Detects the value quotation style.
				   Returns 0 if no quotes were detected.
				   Returns 1 if double quotes were detected.
				   Returns 2 if single quotes were detected.
			*/
			NOU_FUNC int32 parseValueQuote(const NouString &line) const;

			/**
			\param section The section name.
			
			\brief Registers a section in m_data_sections, and increases the counter by 1.
			*/
			NOU_FUNC void incSection(const NouString & section);

			/**
			\param section The section name.

			\brief Decreases the value counter of a section by 1.
			*/
			NOU_FUNC void decSection(const NouString & section);

		public:
			/**
			\param filename The full to the ini file that should be loaded.
			*/
			NOU_FUNC INIFile(const NouString & filename);

			/**
			\return True on success, False on error.

			\brief Parses the INI file
			*/
			NOU_FUNC boolean read();

			/**
			\return True on success, False on error.

			\brief Writes the INI file
			*/
			NOU_FUNC boolean write(const NouString & = NouString(""));

			/**
			\param key     The key to remove
			\param section The target section (Optional)

			\brief Removes a key-value pair from the ini
			*/
			NOU_FUNC void remove(const NouString & key, const NouString & section = INI_DEFAULT_SECTION);

			/**
			\param key     The key to set
			\param value   The NouString to set
			\param section The section to set

			\brief Sets a key-value NouString pair, overriding any existing key.
			*/
			NOU_FUNC void setString(const NouString & key, const NouString & value, const NouString & section = INI_DEFAULT_SECTION);

			/**
			\param key     The key to set
			\param value   The NouString to set
			\param section The section to set

			\brief Sets a key-value integer pair, overriding any existing key.
			*/
			NOU_FUNC void setInt(const NouString & key, int32 value, const NouString & section = INI_DEFAULT_SECTION);

			/**
			\param key     The key to set
			\param value   The NouString to set
			\param section The section to set

			\brief Sets a key-value float pair, overriding any existing key.
			*/
			NOU_FUNC void setFloat(const NouString & key, float32 value, const NouString & section = INI_DEFAULT_SECTION);

			/**
			\param key     The key to search
			\param section The section to search in
			\return        The value of the given key if found, or an empty string if not.

			\brief Retrieves a value of a given key as NouString.
			*/
			NOU_FUNC NouString getString(const NouString & key, const NouString & section = INI_DEFAULT_SECTION);

			/**
			\param  key     The key to search
			\param  section The section to search in
			\return         The value of the given key if found, or an empty string if not.

			\brief Retrieves a value of a given key as integer.
			*/
			NOU_FUNC int32 getInt(const NouString &key, const NouString & section = INI_DEFAULT_SECTION);

			/**
			\param key     The key to search
			\param section The section to search in
			\return        The value of the given key if found, or an empty string if not.

			\brief Retrieves a value of a given key as float.
			*/
			NOU_FUNC float32 getFloat(const NouString &, const NouString & = INI_DEFAULT_SECTION);

			/**
			\param key     The key to search
			\param section The section to search in
			\return        True if found, False if not.

			\brief Checks if a given key exists in the given section.
			*/
			NOU_FUNC boolean keyExists(const NouString &key, const NouString & section = INI_DEFAULT_SECTION);

			/**
			\param key     The key to search for
			\param section The section to search in
			\return        0 = Key not found, 1 = String, 2 = Integer, 3 = Float

			\brief Returns the data type for the value of a given key.
			*/
			NOU_FUNC int32 getDataType(const NouString &key, const NouString & section = INI_DEFAULT_SECTION);

			/**
			\return A hashmap with the key - section pairs.

			\brief Returns a list of all keys in the ini file, including their corresponding section.
			*/
			NOU_FUNC NOU::NOU_DAT_ALG::HashMap<NouString, NouString> getKeys();

			/**
			\param other The inifile that should be merged into this one.

			\brief Merges the given ini file data into the current file. Existing keys will be replaced.
			*/
			NOU_FUNC void merge(INIFile &other);
	};

	constexpr const NOU::char8 *INIFile::INI_DEFAULT_SECTION;
	constexpr int32 INIFile::INI_QUOTE_NONE;
	constexpr int32 INIFile::INI_QUOTE_DOUBLE;
	constexpr int32 INIFile::INI_QUOTE_SINGLE;
	constexpr int32 INIFile::INI_TYPE_NouString;
	constexpr int32 INIFile::INI_TYPE_INT;
	constexpr int32 INIFile::INI_TYPE_FLOAT;

}
#endif