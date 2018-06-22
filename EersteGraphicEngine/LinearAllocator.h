#pragma once

#include "Log.h"
#include "Error.h"
#include "Types.h"
#include "StdHeaders.h"

namespace ege
{
    /* ###################################################################
    *  ############# LINEAR ALLOCATOR ####################################
    *  ################################################################ */

    class LinearAllocator
    {
    public:
        LinearAllocator(size_t size = sizeof(UINT32) * 8192)
            : _totalSize(size)
        {
            _startPtr = malloc(_totalSize);
            Reset();
        }

        ~LinearAllocator()
        {
            free(_startPtr);
            Reset();
        }

        void * Allocate(size_t amount)
        {
            const size_t dataAddress = (size_t)_startPtr + _offset;
            size_t size = amount;
            _offset += size;

            EGE_ASSERT_ERROR((_offset + size <= _totalSize), "Not enough memory allocated in stack allocator");

            return (void*)dataAddress;
        }

        void Deallocate(void* data)
        {
            return;
        }

        void Reset()
        {
            _offset = 0;
        }

    protected:
        LinearAllocator(LinearAllocator const&) = delete;
        LinearAllocator& operator=(LinearAllocator const&) = delete;

    protected:
        size_t _offset;
        size_t _totalSize;
        void * _startPtr;
    };

    /* ###################################################################
    *  ############# ALLOCATOR METHOD ####################################
    *  ################################################################ */

    LinearAllocator& gLinearAllocator();

    void* ege_linear_allocate(UINT32 numBytes);
    void ege_linear_deallocate(void* data);

    /* ###################################################################
    *  ############# MEMORY ALLOCATOR FOR STD ALLOCATOR ##################
    *  ################################################################ */

    /**
    * Memory allocator using LinearAllocator
    */
    template<>
    class MemoryAllocator<LinearAllocator> : public MemoryAllocatorBase
    {
    public:
        static void* Allocate(size_t bytes)
        {
#if EGE_DEBUG
            AddNewCount();
#endif
            return gLinearAllocator().Allocate((UINT32)bytes);
        }

        static void Deallocate(void* ptr)
        {
#if EGE_DEBUG
            AddFreeCount();
#endif
            gLinearAllocator().Deallocate(ptr);
        }
    };
}
