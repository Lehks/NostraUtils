#ifndef	NOU_DAT_ALG_FWD_DCL_HPP
#define	NOU_DAT_ALG_FWD_DCL_HPP

#include "nostrautils/dat_alg/Utils.hpp"
#include "nostrautils/mem_mngt/Pointer.hpp"
#include "nostrautils/mem_mngt/AllocationCallback.hpp"

/**
\file	 dat_alg/FwdDcl.hpp
\author  Lukas Reichmann
\since   1.0.1
\version 1.0.1
\brief   A file that contains forward declarations for various container classes.

\details
A file that contains forward declarations for various container classes.

This file contains forward declarations for:

- nou::dat_alg::ObjectPool
- nou::dat_alg::BinaryHeap
- nou::dat_alg::HashMap
- nou::dat_alg::FastQueue
- nou::dat_alg::Vector

This file exists, because some other files (like thread/ThreadManager.hpp) need those containers, but can not
or should not include the files. Hence, forward declarations are required. However, all of these classes have
default values for (some of) their template parameters. Those can only be defined once (either with the 
forward declaration, or with the actual definition). When the forward declarations were still in the files
that needed them, the problem was, that   
a) The default parameters were with the forward declarations, which meant that they were not defined if the
   file with the forward declarations was not included by any other file that used the container classes.   
b) The default parameters were with the definitions, which meant that they were not defined in the files that
   only used the forward declarations.    

This file solves this problem, because it is included by the files that require the forward declarations and
by the files that contain the class definitions.
*/

///\cond
namespace NOU::NOU_DAT_ALG
{
	template<typename T, template<typename> class ALLOC =
		NOU_MEM_MNGT::GenericAllocationCallback>
	class ObjectPool;

	template<typename T, template<typename> class ALLOC = NOU_MEM_MNGT::GenericAllocationCallback>
	class BinaryHeap;

	template<typename K, typename V, template<typename> class ALLOC =
		NOU_MEM_MNGT::GenericAllocationCallback>
	class HashMap;

	template<typename T, template<typename> class ALLOC = NOU_MEM_MNGT::GenericAllocationCallback>
	class FastQueue;

	template<typename T, template<typename> class ALLOC = NOU_MEM_MNGT::GenericAllocationCallback>
	class Vector;
}
///\endcond

#endif