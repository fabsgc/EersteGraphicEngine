#pragma once

#include <algorithm>

#include "Types.h"
#include "Error.h"
#include "Log.h"
#include "String.h"
#include "StdHeaders.h"

namespace ege
{
    /* ###################################################################
    *  ############# STACK ALLOCATOR #####################################
    *  ################################################################ */

    class StackAllocator
    {
    public:
        StackAllocator(size_t size = sizeof(UINT32) * 8192)
            : _totalSize(size)
        {
            _startPtr = malloc(_totalSize + _totalSize * sizeof(AllocationHeader));
            _offset = 0;
            _used = 0;
            _peak = 0;
        }

        ~StackAllocator()
        {
            if (_offset != 0)
            {
                EGE_LOG_DEBUG("Memory from stack allocator has not been properly free");
            }
            else
            {
                free(_startPtr);
                _startPtr = nullptr;
            }

            Reset();
        }

        void * Allocate(size_t amount)
        {
            const size_t currentAddress = (size_t)_startPtr + _offset;

            size_t padding = 0;
            size_t size = amount;

            EGE_ASSERT_ERROR((_offset + padding + size <= _totalSize), "Not enough memory allocated in stack allocator");

            const size_t headerAddress = currentAddress + padding;
            const size_t dataAddress = headerAddress + sizeof(AllocationHeader);

            AllocationHeader allocationHeader{ padding, size };
            AllocationHeader * headerPtr = (AllocationHeader*)headerAddress;
            headerPtr->padding = padding;
            headerPtr->size = size;

            _offset += padding + sizeof(AllocationHeader) + size;

            _used = _offset;
            _peak = std::max(_peak, _used);

            return (void*)dataAddress;
        }

        void Deallocate(void* data)
        {
            const size_t currentAddress = (size_t)data;
            const size_t headerAddress = currentAddress - sizeof(AllocationHeader);
            const AllocationHeader * allocationHeader{ (AllocationHeader *)headerAddress };

            if (currentAddress == _offset + (size_t)_startPtr - allocationHeader->size)
            {
                _offset = _offset - allocationHeader->size - sizeof(AllocationHeader) - allocationHeader->padding;
                _used = _offset;
            }
            else
            {
                EGE_LOG_DEBUG("Memory leak");
            }
        }

        void Reset()
        {
            _offset = 0;
            _used = 0;
            _peak = 0;
        }

    private:
        StackAllocator(StackAllocator const&) = delete;
        StackAllocator& operator=(StackAllocator const&) = delete;

    private:
        size_t _offset;
        size_t _totalSize;
        size_t _used;
        size_t _peak;
        void * _startPtr;
    };

    /* ###################################################################
    *  ############# ALLOCATOR METHOD ####################################
    *  ################################################################ */

    StackAllocator& gStackAllocator();

    void* ege_stack_allocate(UINT32 numBytes);
    void ege_stack_deallocate(void* data);

    /* ###################################################################
    *  ############# MEMORY ALLOCATOR FOR STD ALLOCATOR ##################
    *  ################################################################ */

    /**
    * Memory allocator using StackAllocator
    */
    template<>
    class MemoryAllocator<StackAllocator> : public MemoryAllocatorBase
    {
    public:
        static void* Allocate(size_t bytes)
        {
#if EGE_DEBUG
            AddNewCount();
#endif
            return gStackAllocator().Allocate((UINT32)bytes);
        }

        static void Deallocate(void* ptr)
        {
#if EGE_DEBUG
            AddFreeCount();
#endif
            gStackAllocator().Deallocate(ptr);
        }
    };

    /* ###################################################################
    *  ############# CUSTOM STD ALLOCATOR FOR STACK ALLOCATOR ############
    *  ################################################################ */
    template <class T>
    class StdStackAllocator
    {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        StdStackAllocator() noexcept
            :_stackAllocator(nullptr)
        { }

        StdStackAllocator(StackAllocator* allocator) noexcept
            : _stackAllocator(allocator)
        { }

        template<class U> StdStackAllocator(const StdStackAllocator<U>& allocator) noexcept
            : _stackAllocator(allocator._stackAllocator)
        { }

        template<class U> bool operator==(const StdStackAllocator<U>&) const noexcept { return true; }
        template<class U> bool operator!=(const StdStackAllocator<U>&) const noexcept { return false; }
        template<class U> class rebind { public: typedef StdStackAllocator<U> other; };

        /** Allocate but don't initialize number elements of type T. */
        T* allocate(const size_t num) const
        {
            if (num == 0)
                return nullptr;

            if (num > static_cast<size_t>(-1) / sizeof(T))
                return nullptr; // Error

            EGE_ASSERT_ERROR((_stackAllocator != nullptr), "Stack allocator not initialized");

            void* const pv = _stackAllocator->Allocate((num * sizeof(T)));

            if (!pv)
                return nullptr; // Error

            return static_cast<T*>(pv);
        }

        /** Deallocate storage p of deleted elements. */
        void deallocate(T* p, size_t num) const noexcept
        {
            _stackAllocator->Deallocate(p);
        }

        size_t max_size() const { return std::numeric_limits<size_type>::max() / sizeof(T); }
        void construct(pointer p, const_reference t) { new (p) T(t); }
        void destroy(pointer p) { p->~T(); }

        /* This version of construct() (with a varying number of parameters)
        * seems necessary in order to use some STL data structures from
        * libstdc++-4.8, but compilation fails on OS X, hence the #if. */
        template<class U, class... Args>
        void construct(U* p, Args&&... args) { new(p) U(std::forward<Args>(args)...); }

        StackAllocator* _stackAllocator;
    };
}