#ifndef NOU_CORE_ASSERTIONS_HPP
#define	NOU_CORE_ASSERTIONS_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/ErrorHandler.hpp"

/** \file Assertions.hpp
\author	 Lukas Reichmann
\since   1.0.0
\version 1.0.1
\brief   This file provides functionality to use dynamic assertions.
*/

/**
\param ... The expression to check.

\brief Checks whether \p b evaluates to <tt>true</tt>. If not, an ASSERT_ERROR will be set in the error
       handler.
*/
#ifndef NOU_ASSERT
#    ifdef NOU_DEBUG
#        define NOU_ASSERT(...) NOU::NOU_CORE::assertImpl(__VA_ARGS__, "Assertion failed: " NOU_STRINGIFY(__VA_ARGS__)\
				"; Function: " NOU_FUNC_NAME "; Line: " NOU_LINE_STRING "; File: " __FILE__, NOU_FUNC_NAME, __LINE__, \
				__FILE__)
#    else
#        define NOU_ASSERT(...)
#    endif
#endif

namespace NOU::NOU_CORE
{
	/**
	\brief A struct with variables that control the behavior of NOU_ASSERT. 

	\details
	A struct with variables that control the behavior of NOU_ASSERT. This struct does not need instantiation, 
	the instance that will be used by NOU_ASSERT can be obtained by using getAssertionSettings().
	*/
	struct AssertionSettings
	{
		/**
		\brief The type of \p callbackType. See the documentation of that member for further information.
		*/
		using CallbackType = void(*) (const char *, const char *, sizeType, const char *);

		/**
		\brief If true, an error will be pushed to the error handler as soon as an assertion fails.

		\details
		If true, an error will be pushed to the error handler as soon as an assertion fails. That error code
		will be \link nostra::utils::core::ErrorCodes::ASSERT_ERROR ErrorCodes::ASSERT_ERROR \endlink. By
		default, this variable is set to \p true.
		*/
		NOU::boolean pushErrorOnFail;

		/**
		\brief If true, nostra::utils::core::debugbreak() will be called as soon as an assertion fails.

		\details
		If true, nostra::utils::core::debugbreak() will be called as soon as an assertion fails. By default, 
		this variable is set to \p false.
		*/
		NOU::boolean breakOnFail;

		/**
		\brief If true, the message that comes with the assertion is printed to std::cout as soon as an
		assertion fails.

		\details
		If true, the message that comes with the assertion is printed to std::cout as soon as an assertion 
		fails. By default, this variable is set to \p false.
		*/
		NOU::boolean printOnFail;

		/**
		\brief If true, exit() will be called as soon as an assertion fails.

		\details
		If true, exit() will be called as soon as an assertion fails. The exit code will be \p exitCode.
		By default, this variable is set to \p false.
		*/
		NOU::boolean exitOnFail;

		/**
		\brief The exit code that will be passed to exit() if that function is called due to an assertion.

		\details
		The exit code that will be passed to exit() if that function is called due to an assertion. This
		variable has only an effect if \p exitOnFail is set to \p true. By default, this variable is set to
		-1.
		*/
		NOU::int32 exitCode;

		/**
		\brief A pointer to a function that will be called as soon as an assertion fails.

		\details
		 A pointer to a function that will be called as soon as an assertion fails. If the value is \p nullptr, no callback will called. The parameter of the function are the following: 
		
		nr. of parameter | type          | value
		---------------- | ------------- | --------------------------------------------------------------
		1                | const char*   | the message of the assertion
		2                | const char*   | the function name of the function that triggered the assertion
		3                | NOU::sizeType | the line in which the assertion was triggered
		4                | const char*   | the file in which the assertion was triggered

		By default, this variable is set to \p nullptr.
		*/
		CallbackType callbackOnFail;
	};

	/**
	\return A static instance of AssertionSettings.

	\brief This function provides the instance of AssertionSettings that will be used by NOU_ASSERT.
	*/
	NOU_FUNC AssertionSettings& getAssertionSettings();

	/**
	\brief Pauses the execution of a program / hits a breakpoint in a debugger.

	\details
	Pauses the execution of a program / hits a breakpoint in a debugger. 

	On systems that use MSVC (NOU_COMPILER == NOU_COMPILER_VISUAL_CPP), this will call __debugbreak().
	On POSIX systems (NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSX), raise(SIGTRAP) will be called. 
	On all other systems, nothing happens.
	*/
	NOU_FUNC void debugbreak();

	/**
	\param b      The evaluated expression.
	\param msg    The message that will be set.
	\param fnName The name of the function in which the assertion failed.
	\param line   The number of the line on which the assertion failed.
	\param file   The file in which the assertion failed.

	\brief The function that is called by NOU_ASSERT. This function should never called directly, always use
	       NOU_ASSERT.
	*/
	NOU_FUNC void assertImpl(boolean b, const char *msg, const char *fnName, sizeType line, const char *file);
}

#endif
