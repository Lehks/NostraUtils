#ifndef NOU_CORE_ERROR_HANDLER_HPP
#define NOU_CORE_ERROR_HANDLER_HPP

#include "nostrautils\core\StdIncludes.hpp"
#include "nostrautils\dat_alg\FastQueue.hpp"
#include "nostrautils\dat_alg\StringView.hpp"
#include "nostrautils\mem_mngt\Pointer.hpp"

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
	\brief Defines an error location object with its attributes and functions.
	*/
	class NOU_CLASS ErrorLocation
	{
	public:

		/**
		\brief Uses the alias StringType for the NOU::NOU_DAT_ALG::StringView8.
		*/
		using StringType = NOU::NOU_DAT_ALG::StringView8;

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
		using ErrorType = typename Error::ErrorType;

		/**
		\return Returns a const pointer to an error.

		\brief Returns a const pointer to an error with the passed ID. This function is abstract.
		*/
		virtual const Error* queryError(ErrorType id) const = 0;
	};

	/**
	\brief Defines the ErrorHandler class.
	*/
	class NOU_CLASS ErrorHandler
	{
	public:
		using ErrorType = typename Error::ErrorType;

		/**
		\brief Uses the alias StringType for the NOU::NOU_DAT_ALG::StringView8.
		*/
		using StringType = ErrorLocation::StringType;

		/**
		\brief The callback type
		*/
		using CallbackType = void(*)(const ErrorLocation &loc);

	private:
		static NOU_MEM_MNGT::GenericAllocationCallback<const ErrorPool*> s_allocator;
		static NOU_DAT_ALG::Vector<const ErrorPool*> s_errorPools;

		NOU_DAT_ALG::FastQueue<ErrorLocation> m_errors;

	public:
		constexpr static sizeType DEFAULT_CAPACITY = 20;
		 
		/**
		\brief A CallbackType where loc is a reference to the ErrorLocation.
		*/
		static CallbackType s_callback;

		static void setCallback(CallbackType callback);

		static void standardCallback(const NOU::NOU_CORE::ErrorLocation &loc);

		static const Error& getError(ErrorType id);

		ErrorHandler();

		const ErrorLocation& peekError() const;

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

	class ErrorCodes
	{
	public:
		enum Codes : typename ErrorLocation::ErrorType
		{
			UNKNOWN_ERROR,
			INDEX_OUT_OF_BOUNDS
		};
	};
}
#endif