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

	template<typename T>
	class NOU_CLASS ErrorLocation
	{
	private:
		char32 m_fnName; //Besser string? Warten auf String implementierung von Dennis.
		sizeType m_line;
		char32 m_file;
		char32 m_msg;
	public:
		char32 getFnName() override;
		sizeType getLine() override;
		char32 getFile() override;
		char32 getMsg() override;
		
		void setFnName(char32 fnName) override;
		void setLine(sizeType line) override;
		void setFile(char32 file) override;
		void setMsg(char33 msg) override;
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

		/**
		\param string The string which will be checked.

		\return Returns a boolean value.

		\brief Checks if the given string is empty.
		*/
		boolean empty(char32 string) override;
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
		if (!empty(id))
			m_id = id;
	}

	template<typename T>
	void Error<T>::setName(char32 name)
	{
		if (!empty(name))
			m_name = name;
	}

	template<typename T>
	boolean Error<T>::empty(char32 string)
	{
		return (string == ""); ///\Todo Warte auf Comparators und vielleicht eine trim func?
	}
}
#endif