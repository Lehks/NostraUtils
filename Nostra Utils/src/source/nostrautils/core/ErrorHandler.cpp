#include "nostrautils\core\ErrorHandler.hpp"

namespace NOU::NOU_CORE
{
	ErrorLocation::ErrorLocation(const StringType &fnName, sizeType line, const StringType &file, 
		sizeType id, const StringType &msg) :
		m_fnName(fnName),
		m_line(line),
		m_file(file),
		m_msg(msg)
	{
		
	}

	const ErrorLocation::StringType& ErrorLocation::getFnName() const
	{
		return m_fnName;
	}

	sizeType ErrorLocation::getLine()
	{
		return m_line;
	}

	const ErrorLocation::StringType& ErrorLocation::getFile() const
	{
		return m_file;
	}

	sizeType ErrorLocation::getID()
	{
		return m_id;
	}

	const ErrorLocation::StringType& ErrorLocation::getMsg() const
	{
		return m_msg;
	}

	Error::Error(const StringType &name, sizeType id) :
		m_name(name),
		m_id(id)
	{}
	const Error::StringType& Error::getName() const
	{
		return m_name;
	}

	sizeType Error::getID()
	{
		return m_id;
	}

	ErrorHandler::ErrorHandler()
	{}

	void ErrorHandler::setError(const StringType &fnName, sizeType line, const StringType &file,
		sizeType id, const StringType &msg)
	{
		m_errors.push(ErrorLocation::ErrorLocation(fnName, line, file, id, msg));
	}
}