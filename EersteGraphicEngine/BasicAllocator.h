#pragma once

#include "Types.h"
#include "StdHeaders.h"

#include <new>
#include <memory>

namespace ege
{
    class BasicAllocator
    {
    public:
        UINT8 * Allocate(UINT32 amount)
        {
            return (UINT8*)malloc(amount);
        }

        void Deallocate(void* data)
        {
            ::free(data);
        }
    };

    BasicAllocator& gBasicAlloc();

    UINT8* ege_basic_allocate(UINT32 numBytes);
    void ege_basic_deallocate(void* data);

    /**
    * Memory allocator using BasicAllocator
    */
    template<>
    class MemoryAllocator<BasicAllocator> : public MemoryAllocatorBase
    {
    public:
        static void* Allocate(size_t bytes)
        {
#if EGE_DEBUG
            AddNewCount();
#endif
            return gBasicAlloc().Allocate((UINT32)bytes);
        }

        static void Deallocate(void* ptr)
        {
#if EGE_DEBUG
            AddFreeCount();
#endif
            gBasicAlloc().Deallocate(ptr);
        }
    };
}
