#include "nostrautils\core\ErrorHandler.hpp"

namespace NOU::NOU_CORE
{
	ErrorLocation::ErrorLocation(const char8* fnName, sizeType line, const char8* file, sizeType errorCode, const char8* msg)
	{

	}

	const char8* ErrorLocation::getFnName()
	{
		return m_fnName;
	}

	sizeType ErrorLocation::getLine()
	{
		return m_line;
	}

	const char8* ErrorLocation::getFile()
	{
		return m_file;
	}

	const char8* ErrorLocation::getMsg()
	{
		return m_msg;
	}

	const char8* Error::getName()
	{
		return m_name;
	}


	sizeType Error::getID()
	{
		return m_id;
	}

	ErrorPool::ErrorPool()
	{

	}

	Error& ErrorPool::queryError(sizeType errorCode)
	{

	}

	ErrorHandler::ErrorHandler()
	{

	}

	void ErrorHandler::setError(const char8* fnName, sizeType line, const char8* file, sizeType errorCode, const char8* msg)
	{

	}
}