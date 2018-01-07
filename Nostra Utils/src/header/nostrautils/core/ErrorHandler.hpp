#ifndef NOU_CORE_ERROR_HANDLER_HPP
#define NOU_CORE_ERROR_HANDLER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\FastQueue.hpp"
#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\mem_mngt\Pointer.hpp"

/**
\file core/ErrorHandler.hpp

\author	 Lukas Gro�
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
	public:

		/**
		\brief Uses the alias StringType for the NOU::NOU_DAT_ALG::StringView8.
		*/
		using StringType = NOU::NOU_DAT_ALG::StringView8;

		/**
		\brief Uses the alias ErrorType for the sizeType.
		*/
		using ErrorType = sizeType;

	private:
		/**
		\brief The function name in which the error occured.
		*/
		StringType  m_fnName;
		
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
		
		\brief Returns the id of the error.
		*/
		ErrorType getID() const;

		/**
		\return Returns the error message.
		
		\brief Returns the error message of the error.
		*/
		const StringType& getMsg() const;
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
	\brief Defines the ErrorPool class.
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

		\brief Returns a const pointer to an error with the passed ID. This function is abstract.
		*/
		virtual const Error* queryError(ErrorType id) const = 0;
	};

	class NOU_CLASS DefaultErrorPool : public ErrorPool
	{
	private:
		static NOU_MEM_MNGT::GenericAllocationCallback<Error> s_poolAllocator;

		static NOU_DAT_ALG::Vector<Error> s_defaultErrorPool;

	public:

		constexpr static sizeType DEFAULT_CAPACITY = 20;

		DefaultErrorPool();

		virtual const Error* queryError(ErrorType id) const override;
	};

	/**
	\brief Defines the ErrorHandler class.
	*/
	class NOU_CLASS ErrorHandler
	{
	private:
		/**
		\brief A wrapper for a vector that stores const pointers to error pools.
		*/
		class ErrorPoolVectorWrapper
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
			NOU_DAT_ALG::Vector<const ErrorPool*> m_errorPools;

		public:
			/**
			\param initialCapacity The initial capacity of the vector.

			\brief Constructs the vector with the passed capacity.
			*/
			ErrorPoolVectorWrapper(sizeType initialCapacity);

			/**
			\brief Deletes all the error pools that are in the vector.
			*/
			~ErrorPoolVectorWrapper();

			/**
			\brief Pushes a pool into the vector.
			*/
			template<typename T>
			void pushPool();

			/**
			\return m_errorPools

			\brief Returns the vector that this class wrapps around.
			*/
			const NOU_DAT_ALG::Vector<const ErrorPool*>& getVector() const;
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
		static ErrorPoolVectorWrapper s_errorPools;

		/**
		\brief Creates a new FastQueue from ErrorLocation.
		*/
		NOU_DAT_ALG::FastQueue<ErrorLocation> m_errors;

	public:
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
			UNKNOWN_ERROR = 0,			//Must start at 0!
			INDEX_OUT_OF_BOUNDS,

			LAST_ELEMENT				 //Must be the last element!
		};
	};

	template<typename T>
	void ErrorHandler::ErrorPoolVectorWrapper::pushPool()
	{
		///\todo check if default constructible
		//static_assert();

		m_errorPools.pushBack(new T()); //must be push back, default pool must be at index #0.
	}

	template<typename T>
	void ErrorHandler::pushPool()
	{
		s_errorPools.pushPool<T>();
	}
}
#endif