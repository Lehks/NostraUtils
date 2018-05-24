#include "nostrautils/core/ErrorHandler.hpp"
#include "nostrautils/dat_alg/FastQueue.hpp"
#include "nostrautils/thread/ThreadManager.hpp"

namespace NOU::NOU_CORE
{
	ErrorLocation::ErrorLocation(const StringType &fnName, sizeType line, const StringType &file, 
		ErrorType id, const StringType &msg) :
		m_fnName(fnName),
		m_line(line),
		m_file(file),
		m_id(id),
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
		return ErrorHandler::getError(getActualID()).getID();
	}

	ErrorLocation::ErrorType ErrorLocation::getActualID() const
	{
		return m_id;
	}

	const ErrorLocation::StringType& ErrorLocation::getMsg() const
	{
		return m_msg;
	}

	const ErrorLocation::StringType& ErrorLocation::getName() const
	{
		return ErrorHandler::getError(getActualID()).getName();
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

//	NOU_MEM_MNGT::GenericAllocationCallback<Error> DefaultErrorPool::s_poolAllocator;

	NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::FastQueue<Error>> DefaultErrorPool::s_defaultErrorPool(
		new NOU_DAT_ALG::FastQueue<Error>(ErrorCodes::LAST_ELEMENT, 
		NOU_MEM_MNGT::GenericAllocationCallback<Error>::get()), NOU_MEM_MNGT::defaultDeleter);

	constexpr sizeType DefaultErrorPool::DEFAULT_CAPACITY;

#ifndef NOU_ADD_ERROR
#define NOU_ADD_ERROR(pool, code) pool->at(ErrorCodes::code) = Error(#code, ErrorCodes::code)
#endif

	DefaultErrorPool::DefaultErrorPool()
	{

		if (s_defaultErrorPool->size() != 0) //errors have already been pushed
			return;

		for (sizeType i = 0; i < ErrorCodes::LAST_ELEMENT; i++)
			s_defaultErrorPool->push(Error("", -1));

		NOU_ADD_ERROR(s_defaultErrorPool, UNKNOWN_ERROR);
		NOU_ADD_ERROR(s_defaultErrorPool, INDEX_OUT_OF_BOUNDS);
		NOU_ADD_ERROR(s_defaultErrorPool, ASSERT_ERROR); 
		NOU_ADD_ERROR(s_defaultErrorPool, BAD_ALLOCATION);
		NOU_ADD_ERROR(s_defaultErrorPool, BAD_DEALLOCATION);
		NOU_ADD_ERROR(s_defaultErrorPool, INVALID_OBJECT);
		NOU_ADD_ERROR(s_defaultErrorPool, INVALID_STATE);
		NOU_ADD_ERROR(s_defaultErrorPool, MUTEX_ERROR);
		NOU_ADD_ERROR(s_defaultErrorPool, PATH_NOT_FOUND);
		NOU_ADD_ERROR(s_defaultErrorPool, ALREADY_EXISTS);
		NOU_ADD_ERROR(s_defaultErrorPool, CANNOT_OPEN_FILE);
	}

	const Error* DefaultErrorPool::queryError(ErrorPool::ErrorType id) const
	{
		if(id < ErrorCodes::LAST_ELEMENT)
			return &s_defaultErrorPool->at(id);
		else
			return nullptr;
	}

	ErrorHandler::ErrorPoolContainerWrapper::ErrorPoolContainerWrapper(sizeType initialCapacity) :
		m_errorPools(new NOU_DAT_ALG::FastQueue<const ErrorPool*>(initialCapacity, 
			NOU_MEM_MNGT::GenericAllocationCallback<const ErrorPool*>::get()),
			NOU_MEM_MNGT::defaultDeleter)
	{
		pushPool<DefaultErrorPool>();
	}

	ErrorHandler::ErrorPoolContainerWrapper::~ErrorPoolContainerWrapper()
	{
		for (sizeType i = 0; i < m_errorPools->size(); i++)
		{
			delete m_errorPools->at(i);
		}
	}

	void ErrorHandler::ErrorPoolContainerWrapper::_pushPool(const ErrorPool *pool)
	{
		m_errorPools->pushBack(pool); //must be pushBack!
	}

	const NOU_DAT_ALG::FastQueue<const ErrorPool*>& 
		ErrorHandler::ErrorPoolContainerWrapper::getContainer() const
	{
		return *m_errorPools;
	}

	ErrorHandler::ErrorPoolContainerWrapper ErrorHandler::s_errorPools(1);

	ErrorHandler::CallbackType ErrorHandler::s_callback = ErrorHandler::standardCallback;

	constexpr sizeType ErrorHandler::DEFAULT_CAPACITY;

	void ErrorHandler::setCallback(CallbackType callback)
	{
		s_callback = callback;
	}

	void ErrorHandler::standardCallback(const NOU::NOU_CORE::ErrorLocation &loc)
	{}

	const Error& ErrorHandler::getError(ErrorType id)
	{
		const Error *error;
		for (sizeType i = 0; i < s_errorPools.getContainer().size(); i++)
		{
			error = s_errorPools.getContainer().at(i)->queryError(id);

			if (error != nullptr)
				return *error;
		}

		return *(s_errorPools.getContainer()[0]->queryError(ErrorCodes::UNKNOWN_ERROR));
	}

	ErrorHandler::ErrorPoolContainerWrapper& ErrorHandler::getPools()
	{
		return s_errorPools;
	}

	sizeType ErrorHandler::getErrorCount() const
	{
		return m_errors->size();
	}

	ErrorHandler& ErrorHandler::getMainThreadHandler()
	{
		static ErrorHandler handler;
		return handler;
	}

	ErrorHandler::ErrorHandler() :
		m_errors(new NOU_DAT_ALG::FastQueue<ErrorLocation>(DEFAULT_CAPACITY, 
			NOU_MEM_MNGT::GenericAllocationCallback<ErrorLocation>::get()), 
			NOU_MEM_MNGT::defaultDeleter)
	{}

	const ErrorLocation& ErrorHandler::peekError() const
	{
		return ErrorHandler::m_errors->peek();
	}

	ErrorLocation ErrorHandler::popError()
	{
		return ErrorHandler::m_errors->pop();
	}

	void ErrorHandler::pushError(const StringType &fnName, sizeType line, const StringType &file,
		ErrorType id, const StringType &msg)
	{
		ErrorLocation errLoc(fnName, line, file, id, msg);
		m_errors->push(errLoc);
		s_callback(errLoc);
	}

	ErrorHandler& getErrorHandler()
	{
		return NOU_THREAD::getThreadManager().getErrorHandlerByThreadId(std::this_thread::get_id());
	}
}