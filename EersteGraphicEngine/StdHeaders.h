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
#include <string>

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
#include "BasicAllocator.h"

#undef min
#undef max
#   if !defined(NOMINMAX) && defined(_MSC_VER)
#		define NOMINMAX // required to stop windows.h messing up std::min
#	endif
#if defined( __MINGW32__ )
#    include <unistd.h>
#endif

#define EE_SLEEP(us) Sleep(us)

namespace ege
{
    template <typename T>
    using SPtr = std::shared_ptr<T>;

    template <typename T, typename Allocator = GeneralAllocator>
    using UPtr = std::unique_ptr<T, decltype(&ege_delete<T, Allocator>)>;

    template <typename T, typename A = StdAllocator<T, BasicAllocator>>
    using Vector = std::vector<T, A>;

    template <typename T, typename A = StdAllocator<T, BasicAllocator>>
    using List = std::list<T, A>;

    template <typename K, typename V, typename P = std::less<K>, typename A = StdAllocator<std::pair<const K, V>, BasicAllocator>>
    using Map = std::map<K, V, P, A>;

    /** Create a new shared pointer using a custom allocator category. */
    template<class Type, class Allocator, class... Args>
    SPtr<Type> ege_shared_ptr_new(Args &&... args)
    {
        return std::allocate_shared<Type>(StdAllocator<Type, Allocator>(), std::forward<Args>(args)...);
    }

    /** Create a new shared pointer using the default allocator category. */
    template<class Type, class... Args>
    SPtr<Type> ege_shared_ptr_new(Args &&... args)
    {
        return std::allocate_shared<Type>(StdAllocator<Type, BasicAllocator>(), std::forward<Args>(args)...);
    }

    /**
    * Create a new shared pointer from a previously constructed object.
    * Pointer specific data will be allocated using the provided allocator category.
    */
    template<class Type, class MainAllocator = BasicAllocator, class PtrDataAllocator = BasicAllocator>
    SPtr<Type> ege_shared_ptr(Type* data)
    {
        return SPtr<Type>(data, &ege_delete<Type, MainAllocator>, StdAllocator<Type, PtrDataAllocator>());
    }

    /** Create a new unique pointer using a custom allocator category. */
    template<class Type, class Allocator, class... Args>
    UPtr<Type, Allocator> ege_unique_ptr_new(Args &&... args)
    {
        Type* rawPtr = ege_allocate<Type, Allocator>(std::forward<Args>(args)...);

        return ege_unique_ptr<Type, Allocator>(rawPtr);
    }

    /** Create a new unique pointer using the default allocator category. */
    template<class Type, class... Args>
    UPtr<Type> ege_unique_ptr_new(Args &&... args)
    {
        Type* rawPtr = ege_allocate<Type, BasicAllocator>(std::forward<Args>(args)...);

        return ege_unique_ptr<Type, BasicAllocator>(rawPtr);
    }

    /**
    * Create a new unique pointer from a previously constructed object.
    * Pointer specific data will be allocated using the provided allocator category.
    */
    template<class Type, class Allocator = BasicAllocator>
    UPtr<Type, Allocator> ege_unique_ptr(Type* data)
    {
        return std::unique_ptr<Type, decltype(&ege_delete<Type, Allocator>)>(data, ege_delete<Type, Allocator>);
    }
}
