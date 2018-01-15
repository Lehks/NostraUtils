#ifndef	NOU_MEM_MNGT_INI_PARSER_HPP
#define	NOU_MEM_MNGT_INI_PARSER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\core\ErrorHandler.hpp"
#include <unordered_map>
#include <string>

namespace NOU::NOU_FILE_MNGT
{
	/**
	\brief Parses .ini files into usable key-value pairs.
	*/
	class NOU_CLASS IniParser
	{
		private:
			/**
			\brief Holds the parsed key value pairs
			*/
			std::unordered_map<std::string, std::string> m_data;

			/**
			\brief The target file name to parse.
			*/
			const char * m_filename;

			/**
			\brief Error handler.
			*/
			NOU::NOU_CORE::ErrorHandler m_err;

			/**
			\param A single line of text.

			\brief Parses a single line from the file.
			*/
			void parseLine(std::string);

			/**
			\param A single line of text.

			\brief Parses the key from a given line.
			*/
			std::string parseKey(std::string);

			/**
			\param A single line of text.

			\brief Parses the value from a given line.
			*/
			std::string parseValue(std::string);

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
			int getValueQuotationType(std::string);

			/**
			\param The key to store.
			\param The value to store.

			\brief Stores a key-value pair in m_data.
			*/
			void addPair(std::string, std::string);

		public:
			/**
			\param File name to parse.

			\brief A file name must be provided to use this class
			*/
			IniParser(const char *);

			/**
			\brief Todo.
			*/
			~IniParser();

			/**
			\brief Parses the target file and returns True on success, False on error.
			*/
			boolean parse();

			/**
			\param The key to look up.

			\brief Returns the value that corresponds to the given key.
			       Returns an empty string if the key was not found.
			*/
			std::string getValue(const char *) const;

			/**
			\param The key to look up.

			\brief Returns True if the key exists. Returns False if it does not exist.
			*/
			boolean keyExists(const char *) const;
	};
}
#endif
