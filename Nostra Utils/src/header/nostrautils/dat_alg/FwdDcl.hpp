#ifndef	NOU_DAT_ALG_FWD_DCL_HPP
#define	NOU_DAT_ALG_FWD_DCL_HPP

#include "nostrautils/dat_alg/Utils.hpp"
#include "nostrautils/mem_mngt/Pointer.hpp"
#include "nostrautils/mem_mngt/AllocationCallback.hpp"

///\cond
namespace NOU::NOU_DAT_ALG
{
	namespace internal
	{
		template<typename T>
		struct ObjectPoolChunk;
	}

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