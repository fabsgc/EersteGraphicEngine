#pragma once

#include "Types.h"
#include "StdHeaders.h"

#include <new>
#include <memory>

namespace ege
{
    class PoolAllocator
    {
    public:
        UINT8 * Allocate(UINT32 amount)
        {
            return nullptr;
        }

        void Deallocate(void* data)
        {
        }

    private:
        PoolAllocator(PoolAllocator const&) = delete;
        PoolAllocator& operator=(PoolAllocator const&) = delete;
    };
}