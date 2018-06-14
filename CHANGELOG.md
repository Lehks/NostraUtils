# Changelog

## Version 1.0.0

### Features
- Added an assertion system
- Added an error handling system
- Added a logging system
- Added a bunch of meta functions (this is not a complete meta-function library, it only contains the 
  functions that are required by NOU) The functions (and related structures) are
  - IdentityType, IdentityType_t
  - RemoveReference, RemoveReference_t
  - Constant
  - BooleanConstant, TrueType, FalseType
  - TypeIf, TypeIf_t
  - RemoveConst, RemoveConst_t
  - UnderlyingType, UnderlyingType_t
  - AreSame
  - InvokeResult, InvokeResult_t
  - IsInvokable, IsInvokableR
  - IsDefaultConstructible
  - IsBaseOf
- Added basic, pre-process time, platform detection
- Added a compiler independent macro to export symbols into a library
- Added macro based versioning
- Added struct based versioning (compatible to the versioning from the previous bullet point)
- Added alias names for primitive data types, like _uint32_ or _float64_
- Added basic time measurement by using a milli- and nanosecond counter
- Added utility Functions:
  - min() / max()
  - move()
  - forward()
  - apply()
- Added a binary tree data structure
- Added a binary search function
- Added comparators
- Added a FIFO-queue called FastQueue that is optimized for a balanced push/pull ratio
- Added a hashing algorithm (meant to be used with e.g. hash maps, it is not a security hash)
- Added a hash map data structure
- Added a class for lazy evaluation
- Added ObjectPool, a very specialized class for storing objects in a pool
- Added a quicksort function
- Added a class to generate random numbers
- Added a string class
- Added a string view class, an interface between the "normal" string class and C-Strings.
- Added a class that reserves (stack) memory for objects without initializing them
- Added a macro that generates pair classes (this allows custom names for each of the two members)
- Added a function to swap objects
- Added a function to measure the length of a string (at compile time if possible)
- Added a function to compare floating point numbers (the operator == does not always work properly)
- Added an array based list class (vector)
- Added a class to read/write from/to a file
- Added a platform independent class that represents a path in the filesystem
- Added a parser for INI files
- Added a platform independent class that represents a folder
- Added a class that represents a color with four components
- Added classes for vector and matrix calculations
- Added a bunch of math related functions (like cosine and power functions) and constants (like PI)
- Added a system to pass user defined memory allocators to data structures that need to allocate memory
- Added an allocator that can allocate any type of object
- Added an allocator that can only allocate a instances of a single types (per instance of the allocator)
- Added a unique pointer class (and the basis for more smart pointers that may come in the future)
- Added memory allocation related utility functions:
  - alignedAlloc/alignedFree
  - allocateUninitialized/deallocateUninitialized
  - addressof()
- Added a thread management system

### Improvements
- None

### Fixes
- None