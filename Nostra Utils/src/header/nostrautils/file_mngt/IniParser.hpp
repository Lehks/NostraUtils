#ifndef	NOU_MEM_MNGT_INI_PARSER_HPP
#define	NOU_MEM_MNGT_INI_PARSER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include <unordered_map>
#include <string>

namespace NOU::NOU_FILE_MNGT
{
	int32 const INI_QUOTE_NONE = 0;
	int32 const INI_QUOTE_DOUBLE = 1;
	int32 const INI_QUOTE_SINGLE = 2;
	int32 const INI_TYPE_STRING = 1;
	int32 const INI_TYPE_INT = 2;
	int32 const INI_TYPE_FLOAT = 3;
	const std::string INI_DEFAULT_SECTION = "undefined";

	/**
	\brief Parses .ini files into usable key-value pairs.
	*/
	class NOU_CLASS IniParser
	{
		private:
			/**
			\brief Holds the parsed key value pairs, with the values being strings.
			*/
			std::unordered_map<std::string, std::string> m_string_data;

			/**
			\brief Holds the parsed key value pairs, with the values being int32.
			*/
			std::unordered_map<std::string, int32> m_int_data;

			/**
			\brief Holds the parsed key value pairs, with the values being float32.
			*/
			std::unordered_map<std::string, float32> m_float_data;

			/**
			\brief The target file name to parse.
			*/
			const char * m_filename;

			/**
			\brief The last section that was encountered during parsing.
			*/
			std::string current_section;

			/**
			\brief Error handler.
			*/
			NOU::NOU_CORE::ErrorHandler m_err;

			/**
			\param The current section

			\brief Sets the current section during the parsing process.
			*/
			void setCurrentSection(const std::string &);

			/**
			\param A single line of text.

			\brief Parses a single line from the file.
			*/
			void parseLine(std::string);

			/**
			\param A single line of text.

			\brief Parses the key from a given line.
			*/
			std::string parseKey(const std::string &);

			/**
			\param A single line of text.

			\brief Parses the value from a given line as a string.
			*/
			std::string parseStringValue(const std::string &);

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
			std::string cleanString(std::string);

			/**
			\param A single line of text

			\brief Detects the value quotation style. 
			       Returns 0 if no quotes were detected.
			       Returns 1 if double quotes were detected.
				   Returns 2 if single quotes were detected.
			*/
			int32 getValueQuotationType(std::string);

			/**
			\param A single line of text

			\brief Detects the data type of the value that is in a specific line.
			Returns INI_TYPE_STRING if it is a string.
			Returns INI_TYPE_INT if it is an integer.
			Returns INI_TYPE_FLOAT if it is a float.
			*/
			int32 getValueDataType(const std::string &);

		public:
			/**
			\param File name to parse.

			\brief A file name must be provided to use this class
			*/
			IniParser(const char *);

			/**
			\brief Parses the target file and returns True on success, False on error.
			*/
			boolean parse();

			/**
			\param The key to look up.

			\brief Returns the value that corresponds to the given key.
			Returns an empty string if the key was not found.
			*/
			std::string getString(const char *, const std::string & section = INI_DEFAULT_SECTION) const;

			/**
			\param The key to look up.

			\brief Returns the value that corresponds to the given key.
			Returns 0 if the key was not found.
			*/
			int32 getInt(const char *, const std::string & section = INI_DEFAULT_SECTION) const;

			/**
			\param The key to look up.

			\brief Returns the value that corresponds to the given key.
			Returns 0.0 if the key was not found.
			*/
			float32 getFloat(const char *, const std::string & section = INI_DEFAULT_SECTION) const;

			/**
			\param The key to store.
			\param The string value to store.

			\brief Stores a key-value pair in m_string_data.
			*/
			void addString(const std::string &, const std::string &, const std::string & section = INI_DEFAULT_SECTION);

			/**
			\param The key to store.
			\param The int32 value to store.

			\brief Stores a key-value pair in m_int32_data.
			*/
			void addInt(const std::string &, const int32 &, const std::string & section = INI_DEFAULT_SECTION);

			/**
			\param The key to store.
			\param The float32 value to store.

			\brief Stores a key-value pair in m_float32_data.
			*/
			void addFloat(const std::string &, const float32 &, const std::string & section = INI_DEFAULT_SECTION);

			/**
			\param The key to look up.

			\brief Returns True if the key exists. Returns False if it does not exist.
			*/
			boolean keyExists(const char *, const std::string & section = INI_DEFAULT_SECTION) const;

			/**
			\param The key to look up.

			\brief Returns True if the key exists. Returns False if it does not exist.
			*/
			boolean keyExistsString(const char *, const std::string & section = INI_DEFAULT_SECTION) const;

			/**
			\param The key to look up.

			\brief Returns True if the key exists. Returns False if it does not exist.
			*/
			boolean keyExistsInt(const char *, const std::string & section = INI_DEFAULT_SECTION) const;

			/**
			\param The key to look up.

			\brief Returns True if the key exists. Returns False if it does not exist.
			*/
			boolean keyExistsFloat(const char *, const std::string & section = INI_DEFAULT_SECTION) const;
	};
}
#endif
