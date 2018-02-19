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
        BasicAllocator() {}
        ~BasicAllocator() {}

        void* Allocate(UINT32 amount)
        {
            return malloc(amount);
        }

        void Deallocate(void* data)
        {
            ::free(data);
        }

    private:
        BasicAllocator(BasicAllocator const&) = delete;
        BasicAllocator& operator=(BasicAllocator const&) = delete;
    };

    BasicAllocator& gBasicAllocator();

    void* ege_basic_allocate(UINT32 numBytes);
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
            return gBasicAllocator().Allocate((UINT32)bytes);
        }

        static void Deallocate(void* ptr)
        {
#if EGE_DEBUG
            AddFreeCount();
#endif
            gBasicAllocator().Deallocate(ptr);
        }
    };
}
