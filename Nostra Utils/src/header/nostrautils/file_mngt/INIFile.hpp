#ifndef	NOU_MEM_MNGT_INI_DOCUMENT_HPP
#define	NOU_MEM_MNGT_INI_DOCUMENT_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/dat_alg/String.hpp"
#include "nostrautils/dat_alg/Hashing.hpp"
#include "nostrautils/dat_alg/HashMap.hpp"

#include <string>
#include <unordered_map>


namespace NOU::NOU_FILE_MNGT
{
	struct INIFileHash 
	{
		std::size_t operator()(const NOU::NOU_DAT_ALG::String<char8> &str) const
		{
			return std::hash<std::string>()(std::string(str.rawStr()));
		}
	};

	class NOU_CLASS INIFile
	{
		public:
			using NouString = NOU::NOU_DAT_ALG::String<char8>;

			static constexpr NOU::char8 *INI_DEFAULT_SECTION = "undefined";
			static const int32 INI_QUOTE_NONE;
			static const int32 INI_QUOTE_DOUBLE;
			static const int32 INI_QUOTE_SINGLE;
			static const int32 INI_TYPE_NouString;
			static const int32 INI_TYPE_INT;
			static const int32 INI_TYPE_FLOAT;

		private:
			/**
			\brief Holds the parsed key value pairs, with the values being NouStrings.
			*/
			std::unordered_map<NouString, NouString, INIFileHash> m_dataString;

			/**
			\brief Holds the parsed key value pairs, with the values being int32.
			*/
			std::unordered_map<NouString, int32, INIFileHash> m_dataInteger;

			/**
			\brief Holds the parsed key value pairs, with the values being float32.
			*/
			std::unordered_map<NouString, float32, INIFileHash> m_dataFloat;

			/**
			\brief Holds the parsed sections and the amount of keys within that section
			*/
			std::unordered_map<NouString, int32, INIFileHash> m_dataSections;

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
			void parseLine(const NouString & line, const NouString & section);

			/**
			\param line A single line of text.
			\return The parsed ini key.

			\brief Parses the key from a given line.
			*/
			NouString parseKey(const NouString & line) const;

			/**
			\param line      A single line of text to parse.
			\param quoteType The string value quotation style (single or double).
			\return The parsed ini value.

			\brief Parses the value from a given line as a NouString.
			*/
			NouString parseStringValue(const NouString & line, const int32 quoteType) const;

			/**
			\param line A single line of text.
			\return A parsed integer value.

			\brief Parses the value from a given line as an integer.
			*/
			int32 parseIntValue(const NouString & line) const;

			/**
			\param line A single line of text.
			\return A parsed float value.

			\brief Parses the value from a given line as a float.
			*/
			float32 parseFloatValue(const NouString &line) const;

			/**
			\param line A single line of text
			\return Quotation type flag.

			\brief Detects the value quotation style.
				   Returns 0 if no quotes were detected.
				   Returns 1 if double quotes were detected.
				   Returns 2 if single quotes were detected.
			*/
			int32 parseValueQuote(const NouString &line) const;

			/**
			\param section The section name.
			
			\brief Registers a section in m_data_sections, and increases the counter by 1.
			*/
			void incSection(const NouString & section);

			/**
			\param section The section name.

			\brief Decreases the value counter of a section by 1.
			*/
			void decSection(const NouString & section);

		public:
			/**
			\param filename The full to the ini file that should be loaded.
			*/
			INIFile(const NouString & filename);

			/**
			\return True on success, False on error.

			\brief Parses the INI file
			*/
			boolean read();

			/**
			\return True on success, False on error.

			\brief Writes the INI file
			*/
			boolean write(const NouString & = NouString("")) const;

			/**
			\param key     The key to remove
			\param section The target section (Optional)

			\brief Removes a key-value pair from the ini
			*/
			void remove(const NouString & key, const NouString & section = INI_DEFAULT_SECTION);

			/**
			\param key     The key to set
			\param value   The NouString to set
			\param section The section to set

			\brief Sets a key-value NouString pair, overriding any existing key.
			*/
			void setString(const NouString & key, const NouString & value, const NouString & section = INI_DEFAULT_SECTION);

			/**
			\param key     The key to set
			\param value   The NouString to set
			\param section The section to set

			\brief Sets a key-value integer pair, overriding any existing key.
			*/
			void setInt(const NouString & key, int32 value, const NouString & section = INI_DEFAULT_SECTION);

			/**
			\param key     The key to set
			\param value   The NouString to set
			\param section The section to set

			\brief Sets a key-value float pair, overriding any existing key.
			*/
			void setFloat(const NouString & key, float32 value, const NouString & section = INI_DEFAULT_SECTION);

			/**
			\param key     The key to search
			\param section The section to search in
			\return        The value of the given key if found, or an empty string if not.

			\brief Retrieves a value of a given key as NouString.
			*/
			NouString getString(const NouString & key, const NouString & section = INI_DEFAULT_SECTION) const;

			/**
			\param  key     The key to search
			\param  section The section to search in
			\return         The value of the given key if found, or an empty string if not.

			\brief Retrieves a value of a given key as integer.
			*/
			int32 getInt(const NouString &key, const NouString & section = INI_DEFAULT_SECTION) const;

			/**
			\param key     The key to search
			\param section The section to search in
			\return        The value of the given key if found, or an empty string if not.

			\brief Retrieves a value of a given key as float.
			*/
			float32 getFloat(const NouString &, const NouString & = INI_DEFAULT_SECTION) const;

			/**
			\param key     The key to search
			\param section The section to search in
			\return        TTrue if found, False if not.

			\brief Checks if a given key exists in the given section.
			*/
			boolean keyExists(const NouString &key, const NouString & section = INI_DEFAULT_SECTION) const;
	};
}
#endif