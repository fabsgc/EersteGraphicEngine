#pragma once

#include "Types.h"
#include "StdHeaders.h"

#include <new>
#include <memory>

namespace ege
{
    /* ###################################################################
    *  ############# BASIC ALLOCATOR #####################################
    *  ################################################################ */

    class BasicAllocator
    {
    public:
        BasicAllocator() {}
        ~BasicAllocator() {}

        void* Allocate(size_t amount)
        {
            return malloc(amount);
        }

        void Deallocate(void* data)
        {
            free(data);
        }

    protected:
        BasicAllocator(BasicAllocator const&) = delete;
        BasicAllocator& operator=(BasicAllocator const&) = delete;
    };

    /* ###################################################################
    *  ############# ALLOCATOR METHODS ###################################
    *  ################################################################ */

    BasicAllocator& gBasicAllocator();

    void* ege_basic_allocate(UINT32 numBytes);
    void ege_basic_deallocate(void* data);

    /* ###################################################################
    *  ############# MEMORY ALLOCATOR FOR STD ALLOCATOR ##################
    *  ################################################################ */

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
