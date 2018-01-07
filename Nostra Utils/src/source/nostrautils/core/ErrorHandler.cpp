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

	NOU_MEM_MNGT::GenericAllocationCallback<Error> DefaultErrorPool::s_poolAllocator;

	NOU_DAT_ALG::Vector<Error> DefaultErrorPool::s_defaultErrorPool(ErrorCodes::LAST_ELEMENT,
		s_poolAllocator);

#ifndef NOU_ADD_ERROR
#define NOU_ADD_ERROR(pool, code) pool##[ErrorCodes::##code] = Error(#code, ErrorCodes::##code)
#endif

	DefaultErrorPool::DefaultErrorPool()
	{

		if (s_defaultErrorPool.size() != 0) //errors have already been pushed
			return;

		for (sizeType i = 0; i < ErrorCodes::LAST_ELEMENT; i++)
			s_defaultErrorPool.push(Error("", -1));

		NOU_ADD_ERROR(s_defaultErrorPool, UNKNOWN_ERROR);
		NOU_ADD_ERROR(s_defaultErrorPool, INDEX_OUT_OF_BOUNDS);
	}

	const Error* DefaultErrorPool::queryError(ErrorPool::ErrorType id) const
	{
		if(id < ErrorCodes::LAST_ELEMENT)
			return &s_defaultErrorPool[id];
		else
			return nullptr;
	}

	ErrorHandler::ErrorPoolVectorWrapper::ErrorPoolVectorWrapper(sizeType initialCapacity) :
		m_errorPools(initialCapacity, m_allocator)
	{}

	ErrorHandler::ErrorPoolVectorWrapper::~ErrorPoolVectorWrapper()
	{
		for (const ErrorPool *errorPool : m_errorPools)
		{
			delete errorPool;
		}
	}

	const NOU_DAT_ALG::Vector<const ErrorPool*>& ErrorHandler::ErrorPoolVectorWrapper::getVector() const
	{
		return m_errorPools;
	}

	//NOU_MEM_MNGT::GenericAllocationCallback<NOU_MEM_MNGT::UniquePtr<const ErrorPool>> ErrorHandler::s_allocator;
	//
	//NOU_DAT_ALG::Vector<NOU_MEM_MNGT::UniquePtr<const ErrorPool>> ErrorHandler::s_errorPools(1, s_allocator);
	ErrorHandler::ErrorPoolVectorWrapper ErrorHandler::s_errorPools(1);

	ErrorHandler::CallbackType ErrorHandler::s_callback = ErrorHandler::standardCallback;

	void ErrorHandler::setCallback(CallbackType callback)
	{
		s_callback = callback;
	}

	void ErrorHandler::standardCallback(const NOU::NOU_CORE::ErrorLocation &loc)
	{}

	const Error& ErrorHandler::getError(ErrorType id)
	{
		const Error *error;
		for (const ErrorPool *errorPool : ErrorHandler::s_errorPools.getVector())
		{
			error = errorPool->queryError(id);

			if (error != nullptr)
				return *error;
		}

		return *(s_errorPools.getVector()[0]->queryError(ErrorCodes::UNKNOWN_ERROR));
	}

	sizeType ErrorHandler::getErrorCount() const
	{
		return m_errors.size();
	}
	
	ErrorHandler::ErrorHandler() :
		m_errors(DEFAULT_CAPACITY)
	{
		pushPool<DefaultErrorPool>();
	}

	const ErrorLocation& ErrorHandler::peekError() const
	{
		return ErrorHandler::m_errors.peek();
	}

	ErrorLocation ErrorHandler::popError()
	{
		return ErrorHandler::m_errors.pop();
	}

	void ErrorHandler::pushError(const StringType &fnName, sizeType line, const StringType &file,
		ErrorType id, const StringType &msg)
	{
		ErrorLocation errLoc(fnName, line, file, id, msg);
		m_errors.push(errLoc);
		s_callback(errLoc);
	}
}