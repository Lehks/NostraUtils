#ifndef NOU_CORE_ERROR_HANDLER_HPP
#define NOU_CORE_ERROR_HANDLER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\FastQueue.hpp"


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
	private:
		/**
		\brief The function name in which the error occured.
		*/
		const char8* m_fnName; //Warten auf String implementierung von Dennis.
		
		/**
		\brief The line in which the error occured.
		*/
		sizeType m_line;

		/**
		\brief The file in which the error occured.
		*/
		const char8* m_file;

		/**
		\brief The error message which is showed.
		*/
		const char8* m_msg;

	public:
		ErrorLocation(const char8* fnName, sizeType line, const char8* file, sizeType errorCode, const char8* msg);

		/**
		\return Returns the function name.

		\brief Returns the name of the function in which the error occured.
		*/
		const char8* getFnName();

		/**
		\return Returns the line.
		
		\brief Returns the line in which the error occured.
		*/
		sizeType getLine();

		/**
		\return Returns the file.
		
		\brief Returns the file in which the error occured.
		*/
		const char8* getFile();

		/**
		\return Returns the error message.
		
		\brief Returns the error message of the error.
		*/
		const char8* getMsg();
	};

	/**
	\brief Defines an error object with its attributes and functions.
	*/
	class NOU_CLASS Error
	{
	private:

		/**
		\brief The error name.
		*/
		const char8* m_name;

		/**
		\brief The error id.
		*/
		sizeType m_id;

	public:

		/**
		\return Returns the name.
		
		\brief Returns the name of the error object.
		*/
		const char8* getName();

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
		Error& queryError(sizeType errorCode);
	};

	/**
	\brief Defines the ErrorHandler class.
	*/
	class NOU_CLASS ErrorHandler
	{
	public:
		using CallbackType = void(*)(const ErrorLocation &loc);

	private:
		NOU::NOU_DAT_ALG::FastQueue<ErrorHandler> m_errorQueue;
	public:
		ErrorHandler();

		void setError(const char8* fnName, sizeType line, const char8* file, sizeType errorCode, const char8* msg);
	};
}
#endif