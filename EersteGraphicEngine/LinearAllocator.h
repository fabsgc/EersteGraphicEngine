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
    *  ############# LINEAR ALLOCATOR ####################################
    *  ################################################################ */

    class LinearAllocator
    {
    public:
        LinearAllocator()
        {
        }

        ~LinearAllocator()
        {
            Reset();
        }

        void * Allocate(size_t amount)
        {
            return nullptr;
        }

        void Deallocate(void* data)
        {
        }

        void Reset()
        {
        }

    private:
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
