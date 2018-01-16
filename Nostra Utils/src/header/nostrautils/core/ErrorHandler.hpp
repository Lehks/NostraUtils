#ifndef NOU_CORE_ERROR_HANDLER_HPP
#define NOU_CORE_ERROR_HANDLER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\mem_mngt\Pointer.hpp"
#include "nostrautils\core\Meta.hpp"

/**
\file core/ErrorHandler.hpp

\author	 Lukas Groﬂ
\version 0.0.1
\since	 1.0.0

\brief A file that contains the nostra::utils::core::ErrorHandler class.
*/

namespace NOU::NOU_DAT_ALG
{
	template<typename T>
	class FastQueue;
}

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
		using StringType = const char*;

		/**
		\brief Uses the alias ErrorType for the sizeType.
		*/
		using ErrorType = sizeType;

	private:
		/**
		\brief The function name in which the error occured.
		*/
		StringType m_fnName;
		
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
		ErrorType m_id;

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

		\param msg A reference to the message of the error.

		\brief Constructs a new ErrorLocation 
		*/
		ErrorLocation(const StringType &fnName, sizeType line, const StringType &file,
			ErrorType id, const StringType &msg);

		/**
		\return Returns the function name.

		\brief Returns the name of the function in which the error occured.
		*/
		const StringType& getFnName() const;

		/**
		\return Returns the line.
		
		\brief Returns the line in which the error occured.
		*/
		sizeType getLine() const;

		/**
		\return Returns the file.
		
		\brief Returns the file in which the error occured.
		*/
		const StringType& getFile() const;

		/**
		\return Returns the id code.
		
		\brief Returns the id of the error, or ErrorCodes::UNKNOWN_ERROR if the error is not known.
		*/
		ErrorType getID() const;

		/**
		\brief Returns the error code that was actually set. If the set error code is a valid one, this will
		       be the same as getId(), but if the code is invalid (not part of any error pool) the returned 
			   code will be the error that was set, not ErrorCodes::UNKNOWN_ERROR.
		*/
		ErrorType getActualID() const;

		/**
		\return Returns the error message.
		
		\brief Returns the error message of the error.
		*/
		const StringType& getMsg() const;

		/**
		\return The name of the error as a string.

		\brief Returns the name of the error as provided by ErrorHandler::getError().getName().
		*/
		const StringType& getName() const;
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

		/**
		\brief Uses the alias ErrorType for the sizeType.
		*/
		using ErrorType = ErrorLocation::ErrorType;

	private:

		/**
		\brief The error name.
		*/
		StringType m_name;

		/**
		\brief The error id.
		*/
		ErrorType m_id;

	public:

		/**
		\param name A reference to the name of the error.

		\param id The ID of the error.

		\brief Constructs a new error.
		*/
		Error(const StringType &name, ErrorType id);

		/**
		\return Returns the name.

		\brief Returns the name of the error object.
		*/
		const StringType& getName() const;

		/**
		\return Returns the id.

		\Brief Returns the id of the error object.
		*/
		ErrorType getID() const;
	};

	/**
	\brief Defines the ErrorPool interface. This interface is used to provide new errors for the 
	       ErrorHandler.
	*/
	class NOU_CLASS ErrorPool
	{
	public:

		/**
		\brief Uses the alias ErrorType for the sizeType.
		*/
		using ErrorType = typename Error::ErrorType;

		/**
		\return Returns a const pointer to an error.

		\brief Returns a const pointer to an error with the passed ID.
		*/
		virtual const Error* queryError(ErrorType id) const = 0;
	};

	/**
	\brief Defines the DefaultErrorPool class.
	*/
	class NOU_CLASS DefaultErrorPool : public ErrorPool
	{
	private:

		/**
		\brief The AllocationCallback that is used by the ErrorPool
		*/
		static NOU_MEM_MNGT::GenericAllocationCallback<Error> s_poolAllocator;

		/**
		\brief The vector that stores the single errors of the defaultErrorPool.
		*/
		static NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::FastQueue<Error>> s_defaultErrorPool;

	public:

		/**
		\brief The default capacity of the vector.
		*/
		constexpr static sizeType DEFAULT_CAPACITY = 20;

		/**
		\brief Constructs a new defaultErrorPool.
		*/
		DefaultErrorPool();

		/**
		\param id The id that is searched for in the pool.

		\brief Searches for a passed id int the pool.
		*/
		virtual const Error* queryError(ErrorType id) const override;
	};

	/**
	\brief Defines the ErrorHandler class.
	*/
	class NOU_CLASS ErrorHandler
	{
	private:
		/**
		\brief A wrapper for a container that stores const pointers to error pools.
		*/
		class NOU_CLASS ErrorPoolContainerWrapper
		{
		private:
			/**
			\brief The allocation callback that is used by m_errorPools. 
			GenericAllocationCallback::getInstance() can not be used, since it may not be constructed yet (
			this class is only used as a static member).
			*/
			NOU_MEM_MNGT::GenericAllocationCallback<const ErrorPool*> m_allocator;

			/**
			\brief The vector that this class wrapps around.
			*/
			NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::FastQueue<const ErrorPool*>> m_errorPools;

			/**
			\param pool The error pool to push.

			\brief Used to push back an actual error pool. This needs to be in a .cpp file, since the
			       FastQueue's operations are not known in the .hpp file.
			*/
			void _pushPool(const ErrorPool *pool);

		public:
			/**
			\param initialCapacity The initial capacity of the vector.

			\brief Constructs the vector with the passed capacity.
			*/
			ErrorPoolContainerWrapper(sizeType initialCapacity);

			/**
			\brief Deletes all the error pools that are in the vector.
			*/
			~ErrorPoolContainerWrapper();

			/**
			\brief Pushes a pool into the vector.
			*/
			template<typename T>
			void pushPool();

			/**
			\return m_errorPools

			\brief Returns the vector that this class wrapps around.
			*/
			const NOU_DAT_ALG::FastQueue<const ErrorPool*>& getContainer() const;
		};

	public:

		/**
		\brief Uses the alias StringType for the NOU::NOU_DAT_ALG::StringView8.
		*/
		using StringType = ErrorLocation::StringType;

		/**
		\brief Uses the alias ErrorType for the sizeType.
		*/
		using ErrorType = typename Error::ErrorType;

		/**
		\brief The callback type
		*/
		using CallbackType = void(*)(const ErrorLocation &loc);

	private:
		/**
		\brief A wrapper for the vector that stores the single error pools.
		*/
		static ErrorPoolContainerWrapper s_errorPools;

		NOU_MEM_MNGT::GenericAllocationCallback<ErrorLocation> m_allocator; //remove later

		/**
		\brief Creates a new FastQueue from ErrorLocation.
		*/
		NOU_MEM_MNGT::UniquePtr<NOU_DAT_ALG::FastQueue<ErrorLocation>> m_errors;

		/**
		\return s_errorPools

		\brief Returns the s_errorPools member. This is used by pushPools().
		*/
		static ErrorPoolContainerWrapper& getPools();

	public:

		//static instance of the error handler. will be removed as soon as the thread manager is ready
		static ErrorHandler s_handler;

		/**
		\brief The default capacity for m_errors.
		*/
		constexpr static sizeType DEFAULT_CAPACITY = 20;
		 
		/**
		\brief A CallbackType where loc is a reference to the ErrorLocation.
		*/
		static CallbackType s_callback;

		/**
		\brief Sets the callback in s_callback.
		*/
		static void setCallback(CallbackType callback);

		/**
		\brief A standard callback that does nothing.
		*/
		static void standardCallback(const NOU::NOU_CORE::ErrorLocation &loc);

		/**
		\param id The passed ID of the error which will be returned.

		\return Returns a reference to an error.

		\brief Returns an error with the passed ID.
		*/
		static const Error& getError(ErrorType id);

		/**
		\brief The type of the error pool to push. Must be default constructible.

		\brief Pushes an error pool into the error handler.
		*/
		template<typename T>
		static void pushPool();

		/**
		\return Returns the error count.

		\brief Returns the count of errors in the queue.
		*/
		sizeType getErrorCount() const;

		/**
		\brief Constructs an new ErrorHandler.
		*/
		ErrorHandler();

		/**
		\return Returns a reference to an ErrorLocation.

		\brief Returns the first error in the queue.
		*/
		const ErrorLocation& peekError() const;

		/**
		\return Returns an ErrorLocation.

		\brief Removes the first element in the queue and returns it.
		*/
		ErrorLocation popError();

		/**
		\param fnName A reference to the function name in which the error occured.

		\param line The line in which the error occured.
		
		\param file A reference to the file in which the error occured.

		\param id The ID of the error.

		\param msg A reference to the message of the error.

		\brief Sets an error with its attributes.
		*/
		void pushError(const StringType &fnName, sizeType line, const StringType &file, 
			ErrorType id, const StringType &msg);

	};

	/**
	\brief Defines the enum values for the error codes
	*/
	class ErrorCodes
	{
	public:
		/**
		\brief Enum values for the error type.
		*/
		enum Codes : typename ErrorLocation::ErrorType
		{
			/**
			\brief An unknown error has occured or an invalid error code has been passed to 
			       ErrorHandler::pushError().
			*/
			UNKNOWN_ERROR = 0,			//Must start at 0!

			/**
			\brief An index was out of bounds.
			*/
			INDEX_OUT_OF_BOUNDS,

			/**
			\brief An assertion failed.
			*/
			ASSERT_ERROR,

			/**
			\brief An allocation failed.
			*/
			BAD_ALLOCATION,

			/**
			\brief A deallocation failed.
			*/
			BAD_DEALLOCATION,
#
			/**
			\brief A string conversion failed.
			*/
			INVALID_STRING_CONVERSION,

			/**
			\brief An object of some kind is invalid.
			*/
			INVALID_OBJECT,

			/**
			\brief An error has occrued in a mutex.
			*/
			MUTEX_ERROR,

			/**
			\brief Not an actual error, but always the last element in the enum. The error codes 0 - 
			LAST_ELEMENT are always reserved for the default error pool.
			*/
			LAST_ELEMENT				 //Must be the last element!
		};
	};

	/**
	\return The error handler that is associated with the calling thread.

	\brief Returns the error handler that is associated with the calling thread. This function is the 
	       preferred way to obtain the current error handler.
	*/
	NOU_FUNC ErrorHandler& getErrorHandler();

/**
\brief This macro is a convenience macro for pushing errors to the specified handler. This macro automatically
       passes the functionname, line number and filename.
*/
#ifndef NOU_PUSH_ERROR
#define NOU_PUSH_ERROR(handler, error, msg) handler.pushError(NOU_FUNC_NAME, __LINE__, __FILE__, error, msg)
#endif

/**
\brief This macro is a convenience macro, that behaves exactly like NOU_PUSH_ERROR, but only if NOU_DEBUG is 
       defined. Otherwise, it will do nothing.
*/
#ifndef NOU_PUSH_DBG_ERROR
#    ifdef  NOU_DEBUG
#        define NOU_PUSH_DBG_ERROR(handler, error, msg) NOU_PUSH_ERROR(handler, error, msg)
#    else
#        define NOU_PUSH_DBG_ERROR(handler, error, msg)
#    endif
#endif

/**
\brief This macro is a convenience macro for pushing errors to the specified handler. This macro automatically
       passes the functionname, line number and filename. This macro will only bush the error, if \p b 
	   evaluates to <tt>true.</tt>
*/
#ifndef NOU_COND_PUSH_ERROR
#define NOU_COND_PUSH_ERROR(b, handler, error, msg) \
	if (b) { handler.pushError(NOU_FUNC_NAME, __LINE__, __FILE__, error, msg); }
#endif

/**
\brief This macro is a convenience macro, that behaves exactly like NOU_PUSH_ERROR, but only if NOU_DEBUG is
       defined. Otherwise, it will do nothing. This macro will only bush the error, if \p b evaluates to 
	   <tt>true.</tt>
*/
#ifndef NOU_COND_PUSH_DBG_ERROR
#    ifdef  NOU_DEBUG
#        define NOU_COND_PUSH_DBG_ERROR(b, handler, error, msg) NOU_COND_PUSH_ERROR(b, handler, error, msg)
#    else
#        define NOU_COND_PUSH_DBG_ERROR(b, handler, error, msg)
#    endif
#endif

	template<typename T>
	void ErrorHandler::ErrorPoolContainerWrapper::pushPool()
	{
		static_assert(IsDefaultConstructible<T>::value);

		_pushPool(new T());
	}

	template<typename T>
	void ErrorHandler::pushPool()
	{
		getPools().pushPool<T>();
	}
}
#endif