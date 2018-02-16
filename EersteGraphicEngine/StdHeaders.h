#pragma once

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <atomic>
#include <cstring>
#include <cstdarg>
#include <cmath>
#include <chrono>
#include <ctime>
#include <memory>

// STL containers
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <bitset>
#include <array>

#include <unordered_map>
#include <unordered_set>

// STL algorithms & functions
#include <algorithm>
#include <functional>
#include <limits>

// C++ Stream stuff
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

extern "C" {
#   include <sys/types.h>
#   include <sys/stat.h>
}

#include <Windows.h>

#undef min
#undef max
#   if !defined(NOMINMAX) && defined(_MSC_VER)
#		define NOMINMAX // required to stop windows.h messing up std::min
#	endif
#if defined( __MINGW32__ )
#    include <unistd.h>
#endif

#define EE_SLEEP(us) Sleep(us)

template <typename T>
using SPtr = std::shared_ptr<T>;

template <typename T, typename Alloc = BasicAllocator>
using UPtr = std::unique_ptr<T, Alloc>;

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using List = std::list<T>;

template <typename K, typename V>
using Map = std::map<K, V>;