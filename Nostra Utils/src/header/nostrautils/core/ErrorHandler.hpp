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

		/**
		\brief Uses the alias StringType for the NOU::NOU_DAT_ALG::StringView8.
		*/
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
		/**
		\param fnName A reference to the function name in which the error occured.

		\param line The line in which the error occured.

		\param file A reference to the file in which the error occured.

		\param id The ID of the error.

		\param msg A reference to the error message.

		\brief Constructs a new ErrorLocation 
		*/
		ErrorLocation(const StringType &fnName, sizeType line, const StringType &file,
			sizeType id, const StringType &msg);

		/**
		\return Returns the function name.

		\brief Returns the name of the function in which the error occured.
		*/
		const StringType& getFnName() const;

		/**
		\return Returns the line.
		
		\brief Returns the line in which the error occured.
		*/
		sizeType getLine();

		/**
		\return Returns the file.
		
		\brief Returns the file in which the error occured.
		*/
		const StringType& getFile() const;

		/**
		\return Returns the id code.
		
		\brief Returns the id of the error.
		*/
		sizeType getID();

		/**
		\return Returns the error message.
		
		\brief Returns the error message of the error.
		*/
		const StringType& getMsg() const;
	};

	/**
	\brief Defines an error object with its attributes and functions.
	*/
	class NOU_CLASS Error
	{
	public:

		/**
		\brief Uses the alias StringType for the NOU::NOU_DAT_ALG::StringView8.
		*/
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

		/**
		\param name A reference to the name of the error.

		\param id The ID of the error.

		\brief Constructs a new error.
		*/
		Error(const StringType &name, sizeType id);

		/**
		\return Returns the name.
		
		\brief Returns the name of the error object.
		*/
		const StringType& getName() const;

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

		/**
		\brief Constructs a new ErrorPool.
		*/
		ErrorPool();

		/**
		\return Returns a reference to an Error.

		\brief Returns a reference to an error with the passed ID.
		*/
		Error& queryError(sizeType id);
	};

	/**
	\brief Defines the ErrorHandler class.
	*/
	class NOU_CLASS ErrorHandler
	{
	public:

		/**
		\brief Uses the alias StringType for the NOU::NOU_DAT_ALG::StringView8.
		*/
		using StringType = ErrorLocation::StringType;

		/**
		\brief A CallbackType where loc is a reference to the ErrorLocation.
		*/
		using CallbackType = void(*)(const ErrorLocation &loc);

	public:

		/**
		\param fnName A reference to the function name in which the error occured.

		\param line The line in which the error occured.

		\param file A reference to the file in which the error occured.

		\ param id The ID of the error.

		\param msg A reference to the message of the error.

		\brief Constructs a new ErrorHandler.
		*/
		ErrorHandler(const StringType &fnName, sizeType line, const StringType &file, 
			sizeType id, const StringType &msg);

		/**
		\param fnName A reference to the function name in which the error occured.

		\param line The line in which the error occured.
		
		\param file A reference to the file in which the error occured.

		\ param id The ID of the error.

		\param msg A reference to the message of the error.

		\brief Sets an error with its attributes.
		*/
		void setError(const StringType &fnName, sizeType line, const StringType &file, 
			sizeType id, const StringType &msg);
	};
}
#endif