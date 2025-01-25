#pragma once
// STL
#include<memory>
#include<stdint.h>
#include<set>
#include<random>
#include<limits>
#include<vector>
#include<string>
#include<bitset>
#include<cassert>
#include<assert.h>
#include<sstream>
#include<istream>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<map>
#include<stack>

template<typename T> using Shared = std::shared_ptr<T>;
template<typename T> using Unique = std::unique_ptr<T>;

#if ON_SEREN_ENGINE
	#if DYNAMIC_BUILD
		#ifdef _MSC_VER
			#define SEREN_API __declspec(dllexport)
		#else
			#define SEREN_API __attribute__((visibility("default")))
		#endif
	#else
		#define SEREN_API
	#endif
#else
	#if DYNAMIC_IMPORT
		#ifdef _MSC_VER
			#define SEREN_API __declspec(dllimport)
		#else
			#define SEREN_API
		#endif
	#else
		#define SEREN_API
	#endif
#endif

// Runtime assert
#define ASSERT assert

// Static assert
#if defined(__clang__) || defined(__gcc__)
	#define SEREN_STATIC_ASSERT _Static_assert
#else
	#define STATIC_ASSERT static_assert
#endif

#if defined(__clang__) || defined(_gcc__)
	#define FORCE_INLINE __attribute__((always_inline)) inline
	#define NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
	#define FORCE_INLINE __forceinline
	#define NOINLINE __declspec(noinline)
#else
	#define FORCE_INLINE inline
	#define NOINLINE
#endif

#define FREE_MEMORY(memory) if (memory != nullptr) { delete memory; memory = nullptr; }