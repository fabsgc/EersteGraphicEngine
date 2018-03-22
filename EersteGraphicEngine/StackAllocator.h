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
    private:
        struct StackAllocationHeader {
            size_t padding;
            size_t size;
        };

    public:
        StackAllocator(size_t size = sizeof(UINT32) * 8192)
            : _totalSize(size)
        {
            _startPtr = malloc(_totalSize + _totalSize * sizeof(StackAllocationHeader));
            Reset();
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
            const size_t dataAddress = headerAddress + sizeof(StackAllocationHeader);

            StackAllocationHeader allocationHeader{ padding, size };
            StackAllocationHeader * headerPtr = (StackAllocationHeader*)headerAddress;
            headerPtr->padding = padding;
            headerPtr->size = size;

            _offset += padding + sizeof(StackAllocationHeader) + size;

            _used = _offset;
            _peak = std::max(_peak, _used);

            return (void*)dataAddress;
        }

        void Deallocate(void* data)
        {
            const size_t currentAddress = (size_t)data;
            const size_t headerAddress = currentAddress - sizeof(StackAllocationHeader);
            const StackAllocationHeader * allocationHeader{ (StackAllocationHeader *)headerAddress };

            if (currentAddress == _offset + (size_t)_startPtr - allocationHeader->size)
            {
                _offset = _offset - allocationHeader->size - sizeof(StackAllocationHeader) - allocationHeader->padding;
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
    *  ############# ALLOCATOR METHODS ###################################
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
}