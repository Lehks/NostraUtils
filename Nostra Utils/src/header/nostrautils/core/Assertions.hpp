#ifndef NOU_CORE_ASSERTIONS_HPP
#define	NOU_CORE_ASSERTIONS_HPP

#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/ErrorHandler.hpp"

/** \file Assertions.hpp
\author	 Lukas Reichmann
\since   0.0.1
\version 0.0.1
\brief   This file provides functionality to use dynamic assertions.
*/

/**
\param b The expression to check.

\brief Checks whether \p b evaluates to <tt>true</tt>. If not, an ASSERT_ERROR will be set in the error
       handler.
*/
#ifndef NOU_ASSERT
#    ifdef NOU_DEBUG
#        define NOU_ASSERT(b) NOU::NOU_CORE::assert(b, "Assertion failed: " NOU_STRINGIFY(b) "; Function: "\
				 NOU_FUNC_NAME "; Line: " NOU_LINE_STRING "; File: " __FILE__, NOU_FUNC_NAME, __LINE__, \
				__FILE__)
#    else
#        define NOU_ASSERT
#    endif
#endif

namespace NOU::NOU_CORE
{
	/**
	\param b      The evaluated expression.
	\param msg    The message that will be set.
	\param fnName The name of the function in which the assertion failed.
	\param line   The number of the line on which the assertion failed.
	\param file   The file in which the assertion failed.

	\brief The function that is called by NOU_ASSERT. This function should never called directly, always use
	       NOU_ASSERT.
	*/
	NOU_FUNC void assert(boolean b, const char *msg, const char *fnName, sizeType line, const char *file);
}

#endif
