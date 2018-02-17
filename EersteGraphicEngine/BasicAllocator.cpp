#include "PrerequisitesUtil.h"
#include "BasicAllocator.h"

namespace ege
{
    BasicAllocator* _GlobalBasicAllocator = nullptr;

    BasicAllocator& gBasicAlloc()
    {
        if (_GlobalBasicAllocator == nullptr)
        {
            // Note: This will leak memory but since it should exist throughout the entirety 
            // of runtime it should only leak on shutdown when the OS will free it anyway.
            _GlobalBasicAllocator = new BasicAllocator();
        }

        return *_GlobalBasicAllocator;
    }

    UINT8* ege_basic_allocate(UINT32 numBytes)
    {
        return gBasicAlloc().Allocate(numBytes);
    }

    void ege_basic_deallocate(void* data)
    {
        gBasicAlloc().Deallocate((UINT8*)data);
    }
}