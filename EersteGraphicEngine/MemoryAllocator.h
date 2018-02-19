#pragma once

#include "Types.h"

#include <new>

namespace ege {

    /* ###################################################################
    *  ############# MEMORY COUNTER ######################################
    *  ################################################################ */

    /**
    * Thread safe class used for storing total number of memory allocations and deallocations, primarily for statistic
    * purposes.
    */
    class MemoryCounter
    {
    public:
        static UINT64 GetNumAllocs()
        {
            return News;
        }

        static UINT64 GetNumFrees()
        {
            return Frees;
        }

    private:
        friend class MemoryAllocatorBase;

        static void AddNewCount() { News++; }
        static void AddFreeCount() { Frees++; }

        static UINT64 News;
        static UINT64 Frees;
    };

    /**
    * Base class all memory allocators need to inherit. Provides allocation and free counting.
    */
    class MemoryAllocatorBase
    {
    protected:
        static void AddNewCount() { MemoryCounter::AddNewCount(); }
        static void AddFreeCount() { MemoryCounter::AddFreeCount(); }
    };

    /* ###################################################################
    *  ############# MEMORY ALLOCATOR BASE ###############################
    *  ################################################################ */

    /**
    * Memory allocator providing a generic implementation. Specialize for specific categories as needed.
    */
    template<class T>
    class MemoryAllocator : public MemoryAllocatorBase
    {
    public:
        static void* Allocate(size_t bytes)
        {
#if EGE_DEBUG
            AddNewCount();
#endif
            return ::malloc(bytes);
        }

        static void Deallocate(void* ptr)
        {
#if EGE_DEBUG
            AddFreeCount();
#endif
            ::free(ptr);
        }
    };

    /**
    * Default allocator when you want to use default os memory management
    */
    class GeneralAllocator
    {
    };

    /* ###################################################################
    *  ############# STL ALLOCATOR WRAPPER ###############################
    *  ################################################################ */

    /** Allocator used for the standard library */
    template <class T, class Allocator = GeneralAllocator>
    class StdAllocator
    {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        StdAllocator() noexcept
        {}

        StdAllocator(Allocator* allocator) noexcept
            : _allocator(allocator)
        {}

        template<class U, class Allocator2> StdAllocator(const StdAllocator<U, Allocator2>& alloc) noexcept 
            : _allocator(alloc._allocator)
        {}

        template<class U, class Allocator2> bool operator==(const StdAllocator<U, Allocator2>&) const noexcept { return true; }
        template<class U, class Allocator2> bool operator!=(const StdAllocator<U, Allocator2>&) const noexcept { return false; }
        template<class U> class rebind { public: typedef StdAllocator<U, Allocator> other; };

        /** Allocate but don't initialize number elements of type T. */
        T* allocate(const size_t num) const
        {
            if (num == 0)
            {
                return nullptr;
            }
                
            if (num > static_cast<size_t>(-1) / sizeof(T))
            {
                return nullptr;
            }

            void* pv = nullptr;

            if (_allocator == nullptr)
            {
                pv = ege_allocate<Allocator>((UINT32)(num * sizeof(T)));
            }
            else
            {
                pv = _allocator->Allocate((num * sizeof(T)));
            }
                
            if (!pv)
            {
                return nullptr; // Error
            }
                
            return static_cast<T*>(pv);
        }

        /** Deallocate storage p of deleted elements. */
        void deallocate(T* p, size_t num) const noexcept
        {
            if (_allocator == nullptr)
            {
                ege_deallocate<Allocator>((void*)p);
            }  
            else
            {
                _allocator->Deallocate(p);
            }    
        }

        size_t max_size() const { return std::numeric_limits<size_type>::max() / sizeof(T); }
        void construct(pointer p, const_reference t) { new (p) T(t); }
        void destroy(pointer p) { p->~T(); }

        /* This version of construct() (with a varying number of parameters)
        * seems necessary in order to use some STL data structures from
        * libstdc++-4.8, but compilation fails on OS X, hence the #if. */
        template<class U, class... Args>
        void construct(U* p, Args&&... args) { new(p) U(std::forward<Args>(args)...); }

    public:
        Allocator * _allocator;
    };

    /* ###################################################################
    *  ############# ENGINE MEMORY ALLOCATION ############################
    *  ################################################################ */

    /**
    * Allocates the specified number of bytes.
    */
    template<class Allocator = GeneralAllocator>
    inline void* ege_allocate(UINT32 count)
    {
        return MemoryAllocator<Allocator>::Allocate(count);
    }

    /**
    * Allocates enough bytes to hold the specified type, but doesn't construct it.
    */
    template<class T, class Allocator = GeneralAllocator>
    inline T* ege_allocate()
    {
        return (T*)MemoryAllocator<Allocator>::Allocate(sizeof(T));
    }

    /**
    * Create a new object with the specified allocator and the specified parameters.
    */
    template<class Type, class Allocator, class... Args>
    Type* ege_allocate(Args &&...args)
    {
        return new (ege_allocate<Allocator>(sizeof(Type))) Type(std::forward<Args>(args)...);
    }

    /**
    * Frees all the bytes allocated at the specified location.
    */
    template<class Allocator = GeneralAllocator>
    inline void ege_deallocate(void* ptr)
    {
        MemoryAllocator<Allocator>::Deallocate(ptr);
    }

    /** Destructs and frees the specified object. */
    template<class T, class Allocator = GeneralAllocator>
    inline void ege_delete(T* ptr)
    {
        (ptr)->~T();
        MemoryAllocator<Allocator>::Deallocate(ptr);
    }
}

#include "BasicAllocator.h"
#include "StackAllocator.h"
#include "PoolAllocator.h"
#include "LinearAllocator.h"