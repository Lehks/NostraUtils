#ifndef NOU_CORE_CONFIG_HPP
#define NOU_CORE_CONFIG_HPP

/** 
\file Config.hpp.in
\author	 Lukas Reichmann
\since   1.0.1
\version 1.0.1
\brief   This file will be configured by CMake and provides macros that put CMake defined variables into the
         source code of NOU.
*/

#ifndef NOU_IS_CONFIG_FILE_PRESENT
#define NOU_IS_CONFIG_FILE_PRESENT
#endif

#ifndef NOU_VERSION_MAJOR
#define NOU_INTERNAL_VERSION_MAJOR 1
#endif

#ifndef NOU_VERSION_MINOR
#define NOU_INTERNAL_VERSION_MINOR 0
#endif

#ifndef NOU_VERSION_PATCH
#define NOU_INTERNAL_VERSION_PATCH 1
#endif

#endif
