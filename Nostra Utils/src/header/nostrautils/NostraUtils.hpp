#ifndef NOU_NOSTRA_UTILS_HPP
#define NOU_NOSTRA_UTILS_HPP

/**
\file NostraUtils.hpp

\author  Lukas Reichmann
\version 1.0.0
\since   1.0.0

\brief A single file that includes all other files of the Nostra Utils library.
*/

#include "nostrautils/core/Assertions.hpp"
#include "nostrautils/core/ErrorHandler.hpp"
#include "nostrautils/core/Logging.hpp"
#include "nostrautils/core/Meta.hpp"
#include "nostrautils/core/StdIncludes.hpp"
#include "nostrautils/core/SystemInformation.hpp"
#include "nostrautils/core/Utils.hpp"
#include "nostrautils/core/Version.hpp"
#include "nostrautils/core/Time.hpp"

#include "nostrautils/dat_alg/BinaryHeap.hpp"
#include "nostrautils/dat_alg/BinarySearch.hpp"
#include "nostrautils/dat_alg/Comparator.hpp"
#include "nostrautils/dat_alg/FastQueue.hpp"
#include "nostrautils/dat_alg/Hashing.hpp"
#include "nostrautils/dat_alg/HashMap.hpp"
#include "nostrautils/dat_alg/LazyEvaluationProperty.hpp"
#include "nostrautils/dat_alg/ObjectPool.hpp"
#include "nostrautils/dat_alg/Quicksort.hpp"
#include "nostrautils/dat_alg/Random.hpp"
#include "nostrautils/dat_alg/String.hpp"
#include "nostrautils/dat_alg/StringView.hpp"
#include "nostrautils/dat_alg/Uninitialized.hpp"
#include "nostrautils/dat_alg/Utils.hpp"
#include "nostrautils/dat_alg/Vector.hpp"

#include "nostrautils/file_mngt/File.hpp"
#include "nostrautils/file_mngt/INIFile.hpp"
#include "nostrautils/file_mngt/Path.hpp"
#include "nostrautils/file_mngt/Folder.hpp"

#include "nostrautils/math/Color.hpp"
#include "nostrautils/math/Vector.hpp"
#include "nostrautils/math/Matrix.hpp"
#include "nostrautils/math/Utils.hpp"

#include "nostrautils/mem_mngt/AllocationCallback.hpp"
#include "nostrautils/mem_mngt/GeneralPurposeAllocator.hpp"
#include "nostrautils/mem_mngt/Pointer.hpp"
#include "nostrautils/mem_mngt/PoolAllocator.hpp"
#include "nostrautils/mem_mngt/Utils.hpp"

#include "nostrautils/thread/Threads.hpp"

#endif