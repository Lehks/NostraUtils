#ifndef NOU_CORE_STD_INCLUDES_HPP
#define NOU_CORE_STD_INCLUDES_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>

/**
\file core/StdIncludes.hpp

\author  Lukas Reichmann
\version 1.0.0
\since   1.0.0

\brief A file that should be included in all other header files of NOU. This provides, along other things, the
       namespace macros and the primitive types.
*/

/**
\brief The name of the main namespace of NOU. All components of NOU are nested in sub-namespaces of this 
       namespace.
*/
#ifndef NOU
#define NOU           nostra::utils
#endif

/**
\brief The name of the namespace that contains all core-components of NOU.
*/
#ifndef NOU_CORE
#define NOU_CORE      core
#endif

/**
\brief The name of the namespace that contains all components that are related to data structures and/or 
       algorithms.
*/
#ifndef NOU_DAT_ALG
#define NOU_DAT_ALG   dat_alg
#endif

/**
\brief The name of the namespace that contains all components that are related to file management.
*/
#ifndef NOU_FILE_MNGT
#define NOU_FILE_MNGT file_mngt
#endif

/**
\brief The name of the namespace that contains all components that are related to math.
*/
#ifndef NOU_MATH
#define NOU_MATH      math
#endif

/**
\brief The name of the namespace that contains all components that are related to memory management.
*/
#ifndef NOU_MEM_MNGT
#define NOU_MEM_MNGT  mem_mngt
#endif		

/**
\brief The name of the namespace that contains all components that are related to threading.
*/
#ifndef NOU_THREAD	  
#define NOU_THREAD    thread
#endif



/**
\brief The operating system identifier for Microsoft Windows.

\details
The operating system identifier for Microsoft Windows. This macro is always defined, to check if the current 
operating system is Windows, use

\code{.cpp}
#if NOU_OS == NOU_OS_WINDOWS
\endcode
*/
#ifndef NOU_OS_WINDOWS
#define NOU_OS_WINDOWS 0
#endif

/**
\brief The operating system identifier for Linux.

\details
The operating system identifier for Linux. This macro is always defined, to check if the current operating 
system is Linux, use

\code{.cpp}
#if NOU_OS == NOU_OS_LINUX
\endcode
*/
#ifndef NOU_OS_LINUX
#define NOU_OS_LINUX 1
#endif

/**
\brief The operating system identifier for Unix.

\details
The operating system identifier for Unix. This macro is always defined, to check if the current operating 
system is Unix, use

\code{.cpp}
#if NOU_OS == NOU_OS_UNIX
\endcode
*/
#ifndef NOU_OS_UNIX
#define NOU_OS_UNIX 2
#endif

/**
\brief The operating system identifier for Macintosh.

\details
The operating system identifier for Apple Macintosh. This macro is always defined, to check if the current 
operating system is Macintosh, use

\code{.cpp}
#if NOU_OS == NOU_OS_MAC
\endcode
*/
#ifndef NOU_OS_MAC
#define NOU_OS_MAC 2
#endif

/**
\brief The operating system identifier for an unknown system.

\details
The operating system identifier for an unknown system. This macro is always defined, to check if the current 
operating system is unknown, use

\code{.cpp}
#if NOU_OS == NOU_OS_UNKNOWN
\endcode

An unknown operating system does not cause an error per-se, however, it may cause major problems (e.g. the
value for NOU_OS_LIBRARY will not be set properly).
*/
#ifndef NOU_OS_UNKNOWN
#define NOU_OS_UNKNOWN 3
#endif

/**
\brief The operating system identifier for the Doxygen documentation.

\details
The operating system identifier for an Doxygen documentation. This macro is always defined, but it does not 
serve any purpose when using the library. In the documentation files NOU_OS will be defined as this 
identifier.
*/
#ifndef NOU_OS_DOXYGEN    
#define NOU_OS_DOXYGEN 4
#endif

/**
\brief Defined as the identifier of the current operating system.

\details
This macro is defined as the identifier of the current operating system. To check for a certain operating 
system, use

\code{.cpp}
#if NOU_OS == NOU_OS_*
\endcode

and replace * with the os name.
If the current os is unknown, the value will be NOU_OS_UNKNOWN.

An unknown operating system does not cause an error per se, however, it may cause major problems (e.g. the
value for NOU_OS_LIBRARY will not be set properly).
*/
#ifndef NOU_OS
#    ifdef _WIN32
#    define NOU_OS NOU_OS_WINDOWS

#    elif defined __linux__
#    define NOU_OS NOU_OS_LINUX

#    elif defined __unix__
#    define NOU_OS NOU_OS_UNIX

#    elif defined macintosh
#    define NOU_OS NOU_OS_MAC

#    elif defined __DOXYGEN__ //__DOXYGEN__ is defined in the Doxyfile
#    define NOU_OS NOU_OS_DOXYGEN

#    else
#    define NOU_OS NOU_OS_UNKNOWN

#    endif
#endif

/**
\brief This macro should be defined by a user if the library is used as a dynamically linked library 
(<tt>.dll</tt>) on MS Windows.

\details
For optimization purposes, functions that will be imported from a DLL should be marked with
<tt>__declspec(dllimport)</tt> on MS Windows when using the Visual C++ compiler. If this macro is defined, all
symbols that were exported into a DLL will be marked for import.

\note
This macro will never be defined on itself, this must always be done by a user before any of NOU files are 
included.
*/
#ifndef NOU_DLL

#	if NOU_OS == NOU_OS_DOXYGEN //Define NOU_DLL to make it appear in the doc
#	define NOU_DLL
#	else
	//Do not define
#	endif

#endif


/**
\brief The library system identifier for the Windows.h.

\details
The library system identifier for the Windows.h. This macro is always defined, to check if the current 
operating system supports the Windows.h, use

\code{.cpp}
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_WIN_H
\endcode
*/
#ifndef NOU_OS_LIBRARY_WIN_H
#define NOU_OS_LIBRARY_WIN_H 0
#endif

/**
\brief The library system identifier for a the POSIX library.

\details
The library system identifier for a the POSIX library. This macro is always defined, to check if the current 
operating system supports the POSIX library, use

\code{.cpp}
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_POSIX
\endcode
*/
#ifndef NOU_OS_LIBRARY_POSIX
#define NOU_OS_LIBRARY_POSIX 1
#endif

/**
\brief The system library identifier for the Doxygen documentation.

\details
The system library identifier for an Doxygen documentation. This macro is always defined, but it does not 
serve any purpose when using the library. In the documentation files NOU_OS_LIBRARY will show up defined as 
this identifier.
*/
#ifndef NOU_OS_LIBRARY_DOXYGEN    
#define NOU_OS_LIBRARY_DOXYGEN 2
#endif

/**
\brief Defined as the identifier of the current supported os library.

\details
This macro is defined as the identifier of the current supported os library. To check for a certain library, 
use

\code{.cpp}
#if NOU_OS_LIBRARY == NOU_OS_LIBRARY_*
\endcode

and replace * with the library name.
If there is no appropriate library available, a \#error directive will be triggered.

\todo Verify!
*/
#ifndef NOU_OS_LIBRARY
#	if NOU_OS == NOU_OS_WINDOWS
#	define NOU_OS_LIBRARY NOU_OS_LIBRARY_WIN_H

#	elif NOU_OS == NOU_OS_LINUX || NOU_OS == NOU_OS_UNIX || NOU_OS == NOU_OS_MAC
#	define NOU_OS_LIBRARY NOU_OS_LIBRARY_POSIX

#   elif NOU_OS == NOU_OS_DOXYGEN
#   define NOU_OS_LIBRARY NOU_OS_LIBRARY_DOXYGEN

#	else
#	error Both Windows.h and POSIX are not supported.

#	endif
#endif

/**
\brief The compiler identifier for Visual C++.

\details
The compiler identifier for Visual C++. This macro is always defined, to check if the current compiler is 
Visual C++, use

\code{.cpp}
#if NOU_COMPILER == NOU_COMPILER_VISUAL_CPP
\endcode
*/
#ifndef NOU_COMPILER_VISUAL_CPP
#define NOU_COMPILER_VISUAL_CPP 0
#endif

/**
\brief The compiler identifier for GNU GCC or g++.

\details
The compiler identifier for GNU GCC or g++. This macro is always defined, to check if the current compiler is 
GNU GCC or g++, use

\code{.cpp}
#if NOU_COMPILER == NOU_COMPILER_GCC
\endcode
*/
#ifndef NOU_COMPILER_GCC
#define NOU_COMPILER_GCC        1
#endif						    

/**
\brief The compiler identifier for Clang.

\details
The compiler identifier for Clang. This macro is always defined, to check if the current compiler is Clang, 
use

\code{.cpp}
#if NOU_COMPILER == NOU_COMPILER_CLANG
\endcode
*/
#ifndef NOU_COMPILER_CLANG	    
#define NOU_COMPILER_CLANG      2
#endif						    

/**
\brief The compiler identifier for Intel C++.

\details
The compiler identifier for Intel C++. This macro is always defined, to check if the current compiler is 
Intel C++, use

\code{.cpp}
#if NOU_COMPILER == NOU_COMPILER_INTEL_CPP
\endcode
*/
#ifndef NOU_COMPILER_INTEL_CPP  
#define NOU_COMPILER_INTEL_CPP  3
#endif						    

/**
\brief The compiler identifier for MinGW.

\details
The compiler identifier for MinGW. This macro is always defined, to check if the current compiler is MinGW, 
use

\code{.cpp}
#if NOU_COMPILER == NOU_COMPILER_MIN_GW
\endcode
*/
#ifndef NOU_COMPILER_MIN_GW	    
#define NOU_COMPILER_MIN_GW     4
#endif						    

/**
\brief The compiler identifier for an unknown compiler.

\details
The compiler identifier for an unknown compiler. This macro is always defined, to check if the current 
compiler is unknown, use

\code{.cpp}
#if NOU_COMPILER == NOU_COMPILER_UNKNOWN
\endcode

An unknown compiler does not cause an error per se, however, it may cause major problems (e.g. the
values for NOU_CLASS and NOU_FUNC will not be set properly).
*/
#ifndef NOU_COMPILER_UNKNOWN    
#define NOU_COMPILER_UNKNOWN    5
#endif

/**
\brief The compiler identifier for the Doxygen documentation.

\details
The compiler identifier for an Doxygen documentation. This macro is always defined, but it does not serve any 
purpose when using the library. In the documentation files, NOU_COMPILER will be defined as this identifier.
*/
#ifndef NOU_COMPILER_DOXYGEN    
#define NOU_COMPILER_DOXYGEN    6
#endif

/**
\brief Defined as the identifier of the current compiler.

\details
This macro is defined as the identifier of the current compiler. To check for a certain compiler, use

\code{.cpp}
#if NOU_COMPILER == NOU_COMPILER_*
\endcode

and replace * with the compiler name.

\todo Verify!
*/
#ifndef NOU_COMPILER

#    ifdef _MSC_VER
#    define NOU_COMPILER NOU_COMPILER_VISUAL_CPP
#    elif defined __GNUC__
#    define NOU_COMPILER NOU_COMPILER_GCC
#    elif defined __clang__
#    define NOU_COMPILER NOU_COMPILER_CLANG
#    elif defined __INTEL_COMPILER
#    define NOU_COMPILER NOU_COMPILER_INTEL_CPP
#    elif defined __MINGW32__
#    define NOU_COMPILER NOU_COMPILER_MIN_GW
#    elif defined __DOXYGEN__
#    define NOU_COMPILER NOU_COMPILER_DOXYGEN
#    else 
#    define NOU_COMPILER NOU_COMPILER_UNKNOWN
#    endif

#endif

/**
\brief A macro that is used to add compiler specific attributes to classes.

\todo Add support for all compilers.
*/
#ifndef NOU_CLASS

#	if NOU_COMPILER == NOU_COMPILER_VISUAL_CPP
#		if defined NOU_DLL
#		define NOU_CLASS __declspec(dllimport) //optimize for import
#		else
#		define NOU_CLASS __declspec(dllexport)
#		endif
#	elif NOU_COMPILER == NOU_COMPILER_GCC
#	define NOU_CLASS __attribute__ ((visibility ("default")))

#	else
#	define NOU_CLASS

#	endif

#endif

/**
\brief A macro that is used to add compiler specific attributes to functions.
*/
#ifndef NOU_FUNC
#define NOU_FUNC NOU_CLASS
#endif

/**
\param major The major part of the version.
\param minor The minor part of the version.
\param patch The patch part of the version.

\brief Creates a 32 bit version number.

\details
Creates a 32 bit version number (more precisely a nou::uint32) that consists of the passed parameters. The 
format is major.minor.patch.

E.g:
NOU_MAKE_VERSION(1, 2, 3) creates the version 1.2.3.

Versions made by this macro can be compared using the usual operators (<, >, <=, >=, ==, !=).

The single parts can be read from a version using NOU_VERSION_MAJOR, NOU_VERSION_MINOR and NOU_VERSION_PATCH
respectively.

The sizes of the single parts in bit are: 
Part  | Size | Maximum value
----- | ---- | -------------
major | 8    | 255
minor | 9    | 511
patch | 15   | 32.767

\warning 
These values should never be overflowed since in this case bits will be cut off.
*/
#ifndef NOU_MAKE_VERSION
#define NOU_MAKE_VERSION(major, minor, patch) 				 \
static_cast<NOU::uint32> 									 \
(((major << 24) & 0b11111111000000000000000000000000)  |	 \
 ((minor << 15) & 0b00000000111111111000000000000000)  |	 \
  (patch &        0b00000000000000000111111111111111))
#endif

/**
\param version The version to retrieve the major part from.

\brief Retrieves the major part of a version that was made using NOU_MAKE_VERSION.
*/
#ifndef NOU_VERSION_MAJOR
#define NOU_VERSION_MAJOR(version) static_cast<NOU::uint32> \
									((version & 0b11111111000000000000000000000000) >> (24))
#endif 

/**
\param version The version to retrieve the major part from.

\brief Retrieves the minor part of a version that was made using NOU_MAKE_VERSION.
*/
#ifndef NOU_VERSION_MINOR
#define NOU_VERSION_MINOR(version) static_cast<NOU::uint32> \
									((version & 0b00000000111111111000000000000000) >> (15))
#endif 							   

/**
\param version The version to retrieve the major part from.

\brief Retrieves the patch part of a version that was made using NOU_MAKE_VERSION.
*/
#ifndef NOU_VERSION_PATCH
#define NOU_VERSION_PATCH(version) static_cast<NOU::uint32>(version & 0b00000000000000000111111111111111)
#endif 

/**
\brief The maximum value of the major part of a version when creating a version with NOU_MAKE_VERSION.
*/
#ifndef NOU_VERSION_MAJOR_MAX
#define NOU_VERSION_MAJOR_MAX static_cast<NOU::uint32>(255)
#endif

/**
\brief The maximum value of the minor part of a version when creating a version with NOU_MAKE_VERSION.
*/
#ifndef NOU_VERSION_MINOR_MAX
#define NOU_VERSION_MINOR_MAX static_cast<NOU::uint32>(511)
#endif

/**
\brief The maximum value of the patch part of a version when creating a version with NOU_MAKE_VERSION.
*/
#ifndef NOU_VERSION_PATCH_MAX
#define NOU_VERSION_PATCH_MAX static_cast<NOU::uint32>(32767)
#endif

/**
\brief The first version of NOU.
*/
#ifndef NOU_VERSION_1_0_0
#define NOU_VERSION_1_0_0 NOU_MAKE_VERSION(1, 0, 0)
#endif

/**
\brief The current version of NOU.
*/
#ifndef NOU_VERSION
#define NOU_VERSION NOU_VERSION_1_0_0
#endif

/**
\brief The version of the compiler in a normalized form.

\todo Verify!
*/
#ifndef NOU_COMPILER_VERSION

#    if NOU_COMPILER == NOU_COMPILER_VISUAL_CPP
#        if defined _MSC_FULL_VER
			 //From this version on, an additional bit is used to determine the version
#            if _MSC_FULL_VER >= 150030729 
#            define NOU_COMPILER_VERSION NOU_MAKE_VERSION((_MSC_FULL_VER % 1'00'00'00000) / 1'00'00000, \
							(_MSC_FULL_VER % 1'00'00000) / 1'00000, _MSC_FULL_VER % 1'00000)
#            else
#            define NOU_COMPILER_VERSION NOU_MAKE_VERSION((_MSC_FULL_VER % 100'00'0000) / 100'0000, \
							(_MSC_FULL_VER % 100'0000) / 10000, _MSC_FULL_VER % 1000)
#            endif
#        else 
#        define NOU_COMPILER_VERSION NOU_MAKE_VERSION(((_MSC_VER % 10000) / 100), (_MSC_VER % 100), 0)
#        endif
#    elif NOU_COMPILER == NOU_COMPILER_GCC
#        if defined __GNUC_PATCHLEVEL__
#        define NOU_COMPILER_VERSION NOU_MAKE_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#        else
#        define NOU_COMPILER_VERSION NOU_MAKE_VERSION(__GNUC__, __GNUC_MINOR__, 0)
#        endif
#    elif NOU_COMPILER == NOU_COMPILER_CLANG
#    define NOU_COMPILER_VERSION NOU_MAKE_VERSION(__clang_major__, __clang_minor__, __clang_patchlevel__)
#    elif NOU_COMPILER == NOU_COMPILER_INTEL_CPP
#    define NOU_COMPILER_VERSION NOU_MAKE_VERSION(((__INTEL_COMPILER % 10000) / 100), \
										(__INTEL_COMPILER % 100), 0)
#    elif NOU_COMPILER == NOU_COMPILER_MIN_GW
#    define NOU_COMPILER_VERSION NOU_MAKE_VERSION(__MINGW32_MAJOR_VERSION, __MINGW32_MINOR_VERSION, 0)
#    elif NOU_COMPILER == NOU_COMPILER_DOXYGEN
#    define NOU_COMPILER_VERSION NOU_VERSION_MIN
#    elif NOU_COMPILER == NOU_COMPILER_UNKNOWN
#    define NOU_COMPILER_VERSION NOU_VERSION_MAX
#    endif

#endif

/**
\param str The expression to convert.

\brief Converts any expression into a const char*.
*/
#ifndef NOU_STRINGIFY
#define NOU_STRINGIFY(str) #str
#endif 

/**
\brief Returns the result of __LINE__ as a c-string (NOU_STRINGIFY(__LINE__) would not work).
*/
#ifndef NOU_LINE_STRING
#define NOU_LINE_STRING_HELPER(str) NOU_STRINGIFY(str)
#define NOU_LINE_STRING NOU_LINE_STRING_HELPER(__LINE__)
#endif

/**
\brief The macro which is used for getting the function name.

\todo Verify!
*/
#ifndef NOU_FUNC_NAME

#	if NOU_COMPILER == NOU_COMPILER_VISUAL_CPP
#	define NOU_FUNC_NAME __FUNCSIG__
#	elif NOU_COMPILER == NOU_COMPILER_GCC
#	define NOU_FUNC_NAME __PRETTY_FUNCTION__
#	elif NOU_COMPILER == NOU_COMPILER_CLANG
#	define NOU_FUNC_NAME __func__ ///\Todo check
#	elif NOU_COMPILER == NOU_COMPILER_INTEL_CPP
#	define NOU_FUNC_NAME __func__ ///\Todo check
#	elif NOU_COMPILER == NOU_COMPILER_MIN_GW
#	define NOU_FUNC_NAME __func__ ///\Todo check
#	elif NOU_COMPILER == NOU_COMPILER_DOXYGEN
#	define NOU_FUNC_NAME __FUNCSIG__
#	else
#	define NOU_FUNC_NAME __func__
#	endif

#endif

namespace NOU::NOU_CORE
{
	/**
	\return (In the member type "type") The type that was chosen.

	\brief Chooses from the available floating point types <tt>float</tt>, <tt>float</tt> and <tt>long 
	       double</tt> one that has a size of 32 bit. If none of the have a size of 32 bit, long double will 
		   be chosen.
	*/
	struct NOU_CLASS ChooseFloat32 :
		std::conditional<sizeof(float) == 4,
		float,
		typename std::conditional_t<sizeof(double) == 4,
		double,
		long double
		>
		> {};

	/**
	\return (In the member type "type") The type that was chosen.

	\brief Chooses from the available floating point types <tt>float</tt>, <tt>float</tt> and <tt>long
		   double</tt> one that has a size of 64 bit. If none of the have a size of 32 bit, long double will
		   be chosen.
	*/
	struct NOU_CLASS ChooseFloat64 :
		std::conditional<sizeof(float) == 8,
		float,
		typename std::conditional_t<sizeof(double) == 8,
		double,
		long double
		>
		> {};

}

namespace NOU
{
	/**
	\brief A signed integer type with a width of 8 bit.
	*/
	using  int8 = std::int8_t;

	/**
	\brief An unsigned integer type with a width of 8 bit.
	*/
	using uint8 = std::uint8_t;

	/**
	\brief A signed integer type with a width of 16 bit.
	*/
	using  int16 = std::int16_t;

	/**
	\brief An unsigned integer type with a width of 16 bit.
	*/
	using uint16 = std::uint16_t;

	/**
	\brief A signed integer type with a width of 32 bit.
	*/
	using  int32 = std::int32_t;

	/**
	\brief An unsigned integer type with a width of 32 bit.
	*/
	using uint32 = std::uint32_t;

	/**
	\brief A signed integer type with a width of 64 bit.
	*/
	using  int64 = std::int64_t;

	/**
	\brief An unsigned integer type with a width of 64 bit.
	*/
	using uint64 = std::uint64_t;

	/**
	\brief An unsigned integer type that is defined as the integer that is the maximum size of any object.
	*/
	using sizeType = std::size_t;

	/**
	\brief A boolean type.
	*/
	using boolean = bool;

	/**
	\brief A type that is one byte.
	*/
	using byte = unsigned char;

	/**
	\brief A character type with a width of 8 bit.
	*/
	using char8 = char;

	/**
	\brief A character type with a width of 16 bit.
	*/
	using char16 = char16_t;

	/**
	\brief A character type with a width of 32 bit.
	*/
	using char32 = char32_t;

	/**
	\brief A floating point type with a width of 32 bit.

	\note If the compiler does not support a 32 bit float, this will be the largest floating point type 
	      available.
	*/
	using float32 = NOU_CORE::ChooseFloat32::type;

	/**
	\brief A floating point type with a width of 64 bit.

	\note If the compiler does not support a 64 bit float, this will be the largest floating point type
	available.
	*/
	using float64 = NOU_CORE::ChooseFloat64::type;
}

#endif
