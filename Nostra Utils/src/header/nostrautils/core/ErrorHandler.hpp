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
	\tparam T The type of the class.

	\brief Defines the ErrorHandler class.
	*/
	template<typename T>
	class NOU_CLASS ErrorHandler
	{
	private:
		NOU::NOU_DAT_ALG::FastQueue<ErrorHandler> ErrorQueue;
	public:
		ErrorHandler();
		~ErrorHandler();
		void(*)(const ErrorLocation &loc); ///\Todo rework
		void setError(char32 fnName, sizeType line, char32 file, sizeType errorCode, char32 msg) override; //setMethode oder 
																								  //Konstruktor?
	};

	template<typename T>
	class NOU_CLASS ErrorPool
	{
	private:
		T& queryError(sizeType errorCode) override;
	};

	/**
	\tparam The error location type.
	
	\brief Defines an error location object with its attributes and functions.
	*/
	template<typename T>
	class NOU_CLASS ErrorLocation
	{
	private:
		/**
		\brief The function name in which the error occured.
		*/
		char32 m_fnName; //Warten auf String implementierung von Dennis.
		
		/**
		\brief The line in which the error occured.
		*/
		sizeType m_line;

		/**
		\brief The file in which the error occured.
		*/
		char32 m_file;

		/**
		\brief The error message which is showed.
		*/
		char32 m_msg;
	public:

		/**
		\return Returns the function name.

		\brief Returns the name of the function in which the error occured.
		*/
		char32 getFnName() override;

		/**
		\return Returns the line.
		
		\brief Returns the line in which the error occured.
		*/
		sizeType getLine() override;

		/**
		\return Returns the file.
		
		\brief Returns the file in which the error occured.
		*/
		char32 getFile() override;

		/**
		\return Returns the error message.
		
		\brief Returns the error message of the error.
		*/
		char32 getMsg() override;
		
		/**
		\param fnName The name of the function.

		\brief Sets an new name for the function in which the error occured. 
		*/
		void setFnName(char32 fnName) override;

		/**
		\param line The line of the error.

		\brief Sets an new line in which the error occured.
		*/
		void setLine(sizeType line) override;
		
		/**
		\param file The name of the file.

		\brief Sets an new file in which the error occured.
		*/
		void setFile(char32 file) override;
		
		/**
		\param msg The new message

		\brief Sets an new message for the error.
		*/
		void setMsg(char32 msg) override;
	};

	/**
	\tparam The error type
	
	\brief Defines an error object with its attributes and functions.
	*/
	template<typename T>
	class NOU_CLASS Error
	{
	private:

		/**
		\brief The error name.
		*/
		char32 m_name;

		/**
		\brief The error id.
		*/
		sizeType m_id;

	public:

		/**
		\return Returns the name.
		
		\brief Returns the name of the error object.
		*/
		char32 getName() override;

		/**
		\return Returns the id.
		
		\Brief Returns the id of the error object.
		*/
		sizeType getID() override;

		/**
		\param id The new id which will be set.

		\brief Sets a new error id.
		*/
		void setID(sizeType id) override;

		/**
		\param name The new name which will be set.
		
		\brief Sets a new error name. 
		*/
		void setName(char32 name) override;
	};

	template<typename T>
	char32 Error<T>::getName()
	{
		return m_name;
	}

	template<typename T>
	sizeType Error<T>::getID()
	{
		return m_id;
	}

	template<typename T>
	void Error<T>::setID(sizeType id)
	{
		m_id = id;
	}

	template<typename T>
	void Error<T>::setName(char32 name)
	{
		m_name = name;
	}
}
#endif