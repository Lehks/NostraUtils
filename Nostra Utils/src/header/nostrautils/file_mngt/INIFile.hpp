#ifndef	NOU_MEM_MNGT_INI_DOCUMENT_HPP
#define	NOU_MEM_MNGT_INI_DOCUMENT_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include <unordered_map>


namespace NOU::NOU_FILE_MNGT
{
	const std::string INI_DEFAULT_SECTION = "undefined";
	int32 const INI_QUOTE_NONE = 0;
	int32 const INI_QUOTE_DOUBLE = 1;
	int32 const INI_QUOTE_SINGLE = 2;
	int32 const INI_TYPE_STRING = 1;
	int32 const INI_TYPE_INT = 2;
	int32 const INI_TYPE_FLOAT = 3;


	class NOU_CLASS INIFile
	{
		private:
			/**
			\brief Holds the parsed key value pairs, with the values being strings.
			*/
			std::unordered_map<std::string, std::string> m_data_string;

			/**
			\brief Holds the parsed key value pairs, with the values being int32.
			*/
			std::unordered_map<std::string, int32> m_data_integer;

			/**
			\brief Holds the parsed key value pairs, with the values being float32.
			*/
			std::unordered_map<std::string, float32> m_data_float;

			/**
			\brief Holds the parsed sections and the amount of keys within that section
			*/
			std::unordered_map<std::string, int32> m_data_sections;

			/**
			\brief The target file name to read from/write to.
			*/
			std::string m_filename;

			/**
			\brief The name of the current section being parsed.
			*/
			std::string m_parser_section;

			/**
			\param A single line of text.

			\brief Parses a single line from the file.
			*/
			void parseLine(const std::string &, const std::string &);

			/**
			\param A single line of text.

			\brief Parses the key from a given line.
			*/
			std::string parseKey(const std::string &) const;

			/**
			\param A single line of text.

			\brief Parses the value from a given line as a string.
			*/
			std::string parseStringValue(const std::string &, const int32);

			/**
			\param A single line of text.

			\brief Parses the value from a given line as an integer.
			*/
			int32 parseIntValue(const std::string &);

			/**
			\param A single line of text.

			\brief Parses the value from a given line as a float.
			*/
			float32 parseFloatValue(const std::string &);

			/**
			\param A single line of text.

			\brief Utility function that sanitizes a string before it may be processed.
			*/
			std::string parseCleanString(std::string) const;

			/**
			\param A single line of text

			\brief Detects the value quotation style.
				   Returns 0 if no quotes were detected.
				   Returns 1 if double quotes were detected.
				   Returns 2 if single quotes were detected.
			*/
			int32 parseValueQuote(const std::string &) const;

			/**
			\param The section name.

			\brief Registers a section in m_data_sections, and increases the counter by 1.
			*/
			void incSection(const std::string &);

			/**
			\param The section name.

			\brief Decreases the value counter of a section by 1.
			*/
			void decSection(const std::string &);


		public:
			INIFile(const std::string &);

			/**
			\brief Parses the INI file
			*/
			boolean read();

			/**
			\brief Writes the INI file
			*/
			boolean write(const std::string & = "");

			/**
			\param The key to remove
			\param The target section (Optional)

			\brief Removes a key-value pair from the ini
			*/
			void remove(const std::string &, const std::string & = INI_DEFAULT_SECTION);

			/**
			\param The key to set
			\param The string to set
			\param The section to set

			\brief Sets a key-value string pair, overriding any existing key.
			*/
			void setString(const std::string &, const std::string &, const std::string & = INI_DEFAULT_SECTION);

			/**
			\param The key to set
			\param The string to set
			\param The section to set

			\brief Sets a key-value integer pair, overriding any existing key.
			*/
			void setInt(const std::string &, int32, const std::string & = INI_DEFAULT_SECTION);

			/**
			\param The key to set
			\param The string to set
			\param The section to set

			\brief Sets a key-value float pair, overriding any existing key.
			*/
			void setFloat(const std::string &, float32, const std::string & = INI_DEFAULT_SECTION);

			/**
			\param The key to search
			\param The section to search in

			\brief Retrieves a value of a given key as string.
			*/
			std::string getString(const std::string &, const std::string & = INI_DEFAULT_SECTION) const;

			/**
			\param The key to search
			\param The section to search in

			\brief Retrieves a value of a given key as integer.
			*/
			int32 getInt(const std::string &, const std::string & = INI_DEFAULT_SECTION) const;

			/**
			\param The key to search
			\param The section to search in

			\brief Retrieves a value of a given key as float.
			*/
			float32 getFloat(const std::string &, const std::string & = INI_DEFAULT_SECTION) const;

			/**
			\param The key to search
			\param The section to search in

			\brief Checks if a given key exists in the given section.
			*/
			boolean keyExists(const std::string &, const std::string & = INI_DEFAULT_SECTION) const;
	};
}
#endif