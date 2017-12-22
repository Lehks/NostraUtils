#ifndef NOU_CORE_STD_INCLUDES_HPP
#define NOU_CORE_STD_INCLUDES_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>

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
\brief The name of the namespace that contains all components that are related to datastructures and/or 
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
operating system is unknwon, use

\code{.cpp}
#if NOU_OS == NOU_OS_UNKNOWN
\endcode

An unknown operating system does not cause an error per se, however, it may cause major problems (e.g. the
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
This macro is defined as the identifier of the current operating system. To check for a certain opeating 
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
For optimisation purposes, functions that will be imported from a DLL should be marked with
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
	using  int8 = std::int8_t;
	using uint8 = std::uint8_t;

	using  int16 = std::int16_t;
	using uint16 = std::uint16_t;

	using  int32 = std::int32_t;
	using uint32 = std::uint32_t;

	using  int64 = std::int64_t;
	using uint64 = std::uint64_t;

	using sizeType = std::size_t;

	using boolean = bool;

	using char8 = char;
	using char16 = char16_t;
	using char32 = char32_t;

	using float32 = NOU_CORE::ChooseFloat32::type;
	using float64 = NOU_CORE::ChooseFloat64::type;

}

#endif
