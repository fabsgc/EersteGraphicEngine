#include "PrerequisitesUtil.h"
#include "StackAllocator.h"

namespace ege
{
    StackAllocator* _GlobalStackAllocator = nullptr;

    StackAllocator& gStackAllocator()
    {
        if (_GlobalStackAllocator == nullptr)
        {
            // Note: This will leak memory but since it should exist throughout the entirety 
            // of runtime it should only leak on shutdown when the OS will free it anyway.
            _GlobalStackAllocator = new StackAllocator();
        }

        return *_GlobalStackAllocator;
    }

    void* ege_stack_allocate(UINT32 numBytes)
    {
        return gStackAllocator().Allocate(numBytes);
    }

    void ege_stack_deallocate(void* data)
    {
        gStackAllocator().Deallocate((UINT8*)data);
    }
}