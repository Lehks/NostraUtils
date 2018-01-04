#ifndef NOU_CORE_ERROR_HANDLER_HPP
#define NOU_CORE_ERROR_HANDLER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\FastQueue.hpp"
#include "nostrautils\dat_alg\StringView.hpp"

/**
\file core/ErrorHandler.hpp

\author	 Lukas Groﬂ
\version 0.0.1
\since	 1.0.0

\brief A file that contains the nostra::utils::core::ErrorHandler class.
*/
namespace NOU::NOU_CORE
{
	/**
	\brief Defines an error location object with its attributes and functions.
	*/
	class NOU_CLASS ErrorLocation
	{
	public:
		using StringType = NOU::NOU_DAT_ALG::StringView8;
	private:
		/**
		\brief The function name in which the error occured.
		*/
		StringType  m_fnName;
		
		/**
		\brief The line in which the error occured.
		*/
		sizeType m_line;

		/**
		\brief The file in which the error occured.
		*/
		StringType m_file;

		/**
		\brief The error code of the error.
		*/
		sizeType m_id;

		/**
		\brief The error message which is showed.
		*/
		StringType m_msg;

	public:
		ErrorLocation(const StringType &fnName, sizeType line, const StringType &file,
			sizeType id, const StringType &msg);

		/**
		\return Returns the function name.

		\brief Returns the name of the function in which the error occured.
		*/
		const StringType &getFnName() const;

		/**
		\return Returns the line.
		
		\brief Returns the line in which the error occured.
		*/
		sizeType getLine();

		/**
		\return Returns the file.
		
		\brief Returns the file in which the error occured.
		*/
		const StringType &getFile() const;

		/**
		\return Returns the id code.
		
		\brief Returns the id of the error.
		*/
		sizeType getID();

		/**
		\return Returns the error message.
		
		\brief Returns the error message of the error.
		*/
		const StringType &getMsg() const;
	};

	/**
	\brief Defines an error object with its attributes and functions.
	*/
	class NOU_CLASS Error
	{
	public:
		using StringType = ErrorLocation::StringType;

	private:

		/**
		\brief The error name.
		*/
		StringType m_name;

		/**
		\brief The error id.
		*/
		sizeType m_id;

	public:

		Error(const StringType &name, sizeType id);

		/**
		\return Returns the name.
		
		\brief Returns the name of the error object.
		*/
		const StringType &getName() const;

		/**
		\return Returns the id.
		
		\Brief Returns the id of the error object.
		*/
		sizeType getID();
	};

	/**
	\brief Defines the ErrorPool class.
	*/
	class NOU_CLASS ErrorPool
	{
	public:
		ErrorPool();
		Error& queryError(sizeType id);
	};

	/**
	\brief Defines the ErrorHandler class.
	*/
	class NOU_CLASS ErrorHandler
	{
	public:
		using StringType = ErrorLocation::StringType;

		using CallbackType = void(*)(const ErrorLocation &loc);

	public:
		ErrorHandler(const StringType &fnName, sizeType line, const StringType &file, 
			sizeType id, const StringType &msg);

		void setError(const StringType &fnName, sizeType line, const StringType &file, 
			sizeType id, const StringType &msg);
	};
}
#endif