#include "PrerequisitesUtil.h"
#include "PoolAllocator.h"

namespace ege
{
    PoolAllocator* _GlobalPoolAllocator = nullptr;

    PoolAllocator& gPoolAllocator()
    {
        if (_GlobalPoolAllocator == nullptr)
        {
            // Note: This will leak memory but since it should exist throughout the entirety 
            // of runtime it should only leak on shutdown when the OS will free it anyway.
            _GlobalPoolAllocator = new PoolAllocator();
        }

        return *_GlobalPoolAllocator;
    }

    void* ege_pool_allocate(UINT32 numBytes)
    {
        return gPoolAllocator().Allocate(numBytes);
    }

    void ege_pool_deallocate(void* data)
    {
        gPoolAllocator().Deallocate((UINT8*)data);
    }
}