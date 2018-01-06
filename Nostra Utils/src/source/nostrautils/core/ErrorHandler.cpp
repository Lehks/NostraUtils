#include "nostrautils\core\ErrorHandler.hpp"

namespace NOU::NOU_CORE
{
	ErrorLocation::ErrorLocation(const StringType &fnName, sizeType line, const StringType &file, 
		ErrorType id, const StringType &msg) :
		m_fnName(fnName),
		m_line(line),
		m_file(file),
		m_msg(msg)
	{}

	const ErrorLocation::StringType& ErrorLocation::getFnName() const
	{
		return m_fnName;
	}

	sizeType ErrorLocation::getLine() const
	{
		return m_line;
	}

	const ErrorLocation::StringType& ErrorLocation::getFile() const
	{
		return m_file;
	}

	ErrorLocation::ErrorType ErrorLocation::getID() const
	{
		return m_id;
	}

	const ErrorLocation::StringType& ErrorLocation::getMsg() const
	{
		return m_msg;
	}

	Error::Error(const StringType &name, ErrorType id) :
		m_name(name),
		m_id(id)
	{}

	const Error::StringType& Error::getName() const
	{
		return m_name;
	}

	Error::ErrorType Error::getID() const
	{
		return m_id;
	}

	void ErrorHandler::setCallback(CallbackType callback)
	{
		s_callback = callback;
	}

	void ErrorHandler::standardCallback(const NOU::NOU_CORE::ErrorLocation &loc)
	{}

	NOU_MEM_MNGT::GenericAllocationCallback<const ErrorPool*> ErrorHandler::s_allocator;

	NOU_DAT_ALG::Vector<const ErrorPool*> ErrorHandler::s_errorPools(1, s_allocator);

	ErrorHandler::CallbackType ErrorHandler::s_callback = ErrorHandler::standardCallback;

	ErrorHandler::ErrorHandler() :
		m_errors(DEFAULT_CAPACITY)
	{}

	const ErrorLocation& ErrorHandler::peekError() const
	{
		return ErrorHandler::m_errors.peek();
	}

	ErrorLocation ErrorHandler::popError()
	{
		return ErrorHandler::m_errors.pop();
	}

	const Error& ErrorHandler::getError(ErrorType id)
	{
		const Error *error;
		for (const ErrorPool *errorPool : ErrorHandler::s_errorPools)
		{
			error = errorPool->queryError(id);

			if (error != nullptr)
				return *error;
		}

		return *(s_errorPools[0]->queryError(ErrorCodes::UNKNOWN_ERROR));
	}

	void ErrorHandler::pushError(const StringType &fnName, sizeType line, const StringType &file,
		ErrorType id, const StringType &msg)
	{
		ErrorLocation errLoc(fnName, line, file, id, msg);
		m_errors.push(errLoc);
		s_callback(errLoc);
	}
}