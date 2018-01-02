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
	public:
	private:
		void(*)(const ErrorLocation &loc); ///\Todo rework
		void setError(char32 fnName, sizeType line, char32 file, sizeType errorCode, char32 msg);
	};

	template<typename T>
	class NOU_CLASS ErrorPool
	{
	private:
		T& queryError(sizeType errorCode);
	};

	template<typename T>
	struct NOU_CLASS ErrorLocation
	{
	private:
		char32 m_fnName; //Besser string? Warten auf String implementierung von Dennis.
		sizeType m_line;
		char32 m_file;
		char32 m_msg;
	};

	template<typename T>
	struct NOU_CLASS Error
	{
	private:
		char32 m_name;
		sizeType m_id;
	};

}
#endif