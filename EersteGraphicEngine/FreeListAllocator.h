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

    template <size_t BlockSize = sizeof(UINT32) * 64>
    class FreeListAllocator
    {
    private:
        struct FreeListHeader
        {
            size_t  Size;
            UINT32* BlockPtr;

            FreeListHeader()
                : Size(0)
                , BlockPtr(nullptr)
            {}
        };

        class FreeListBlock
        {
        public:
        };

        
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