#pragma once

#include "Log.h"
#include "Error.h"
#include "Types.h"
#include "StdHeaders.h"

namespace ege
{
    /* ###################################################################
    *  ############# POOL ALLOCATOR  #####################################
    *  ################################################################ */

    class FreeListAllocator
    {
    public:
        FreeListAllocator()
        {}

        void * Allocate(size_t amount)
        {
            return nullptr;
        }

        void Deallocate(void* data)
        {
            return;
        }

        void Reset()
        {
        }
    };
}