#ifndef	NOU_MEM_MNGT_INI_DOCUMENT_HPP
#define	NOU_MEM_MNGT_INI_DOCUMENT_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/dat_alg/String.hpp"
#include "nostrautils/dat_alg/HashMap.hpp"
#include <unordered_map>


namespace NOU::NOU_FILE_MNGT
{
	using NouString = NOU::NOU_DAT_ALG::String<char8>;

	const NouString INI_DEFAULT_SECTION("undefined");
	int32 const INI_QUOTE_NONE = 0;
	int32 const INI_QUOTE_DOUBLE = 1;
	int32 const INI_QUOTE_SINGLE = 2;
	int32 const INI_TYPE_NouString = 1;
	int32 const INI_TYPE_INT = 2;
	int32 const INI_TYPE_FLOAT = 3;


	class NOU_CLASS INIFile
	{
		private:
			/**
			\brief Holds the parsed key value pairs, with the values being NouStrings.
			*/
			std::unordered_map<NouString, NouString> m_dataString;

			/**
			\brief Holds the parsed key value pairs, with the values being int32.
			*/
			std::unordered_map<NouString, int32> m_dataInteger;

			/**
			\brief Holds the parsed key value pairs, with the values being float32.
			*/
			std::unordered_map<NouString, float32> m_dataFloat;

			/**
			\brief Holds the parsed sections and the amount of keys within that section
			*/
			std::unordered_map<NouString, int32> m_dataSections;

			/**
			\brief The target file name to read from/write to.
			*/
			NouString m_filename;

			/**
			\brief The name of the current section being parsed.
			*/
			NouString m_parserSection;

			/**
			\param A single line of text.

			\brief Parses a single line from the file.
			*/
			void parseLine(NouString &, const NouString &);

			/**
			\param A single line of text.

			\brief Parses the key from a given line.
			*/
			NouString parseKey(NouString &) const;

			/**
			\param A single line of text.

			\brief Parses the value from a given line as a NouString.
			*/
			NouString parseStringValue(NouString &, const int32);

			/**
			\param A single line of text.

			\brief Parses the value from a given line as an integer.
			*/
			int32 parseIntValue(const NouString &);

			/**
			\param A single line of text.

			\brief Parses the value from a given line as a float.
			*/
			float32 parseFloatValue(const NouString &);

			/**
			\param A single line of text

			\brief Detects the value quotation style.
				   Returns 0 if no quotes were detected.
				   Returns 1 if double quotes were detected.
				   Returns 2 if single quotes were detected.
			*/
			int32 parseValueQuote(const NouString &) const;

			/**
			\param The section name.

			\brief Registers a section in m_data_sections, and increases the counter by 1.
			*/
			void incSection(const NouString &);

			/**
			\param The section name.

			\brief Decreases the value counter of a section by 1.
			*/
			void decSection(const NouString &);


		public:
			INIFile(const NouString &);

			/**
			\brief Parses the INI file
			*/
			boolean read();

			/**
			\brief Writes the INI file
			*/
			boolean write(const NouString & = NouString(""));

			/**
			\param The key to remove
			\param The target section (Optional)

			\brief Removes a key-value pair from the ini
			*/
			void remove(const NouString &, const NouString & = INI_DEFAULT_SECTION);

			/**
			\param The key to set
			\param The NouString to set
			\param The section to set

			\brief Sets a key-value NouString pair, overriding any existing key.
			*/
			void setString(const NouString &, const NouString &, const NouString & = INI_DEFAULT_SECTION);

			/**
			\param The key to set
			\param The NouString to set
			\param The section to set

			\brief Sets a key-value integer pair, overriding any existing key.
			*/
			void setInt(const NouString &, int32, const NouString & = INI_DEFAULT_SECTION);

			/**
			\param The key to set
			\param The NouString to set
			\param The section to set

			\brief Sets a key-value float pair, overriding any existing key.
			*/
			void setFloat(const NouString &, float32, const NouString & = INI_DEFAULT_SECTION);

			/**
			\param The key to search
			\param The section to search in

			\brief Retrieves a value of a given key as NouString.
			*/
			NouString getString(const NouString &, const NouString & = INI_DEFAULT_SECTION);

			/**
			\param The key to search
			\param The section to search in

			\brief Retrieves a value of a given key as integer.
			*/
			int32 getInt(const NouString &, const NouString & = INI_DEFAULT_SECTION);

			/**
			\param The key to search
			\param The section to search in

			\brief Retrieves a value of a given key as float.
			*/
			float32 getFloat(const NouString &, const NouString & = INI_DEFAULT_SECTION);

			/**
			\param The key to search
			\param The section to search in

			\brief Checks if a given key exists in the given section.
			*/
			boolean keyExists(const NouString &, const NouString & = INI_DEFAULT_SECTION);
	};
}
#endif