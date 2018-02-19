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

    class PoolAllocator
    {
    public:
        PoolAllocator()
            : _elementSize(0)
            , _elementsPerBlock(0)
            , _alignment(0)
        {
            EGE_ASSERT_ERROR((_elementSize >= 4), "Pool allocator minimum allowed element size is 4 bytes.");
            EGE_ASSERT_ERROR((_elementsPerBlock > 0), "Number of elements per block must be at least 1.");
        }

        PoolAllocator(
            size_t elementSize = sizeof(UINT32), 
            size_t elementsPerBlock = 512, 
            size_t alignment = 4)
            : _elementSize(elementSize)
            , _elementsPerBlock(elementsPerBlock)
            , _alignment(alignment)
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

    private:
        class PoolBlock
        {
        public:

        private:
            void*      _startPtr;
            PoolBlock* _nextBlock;
        };

    private:
        PoolAllocator(PoolAllocator const&) = delete;
        PoolAllocator& operator=(PoolAllocator const&) = delete;

    private:
        size_t _elementSize;
        size_t _elementsPerBlock;
        size_t _alignment;
    };

    /* ###################################################################
    *  ############# ALLOCATOR METHOD ####################################
    *  ################################################################ */

    PoolAllocator& gPoolAllocator();

    void* ege_pool_allocate(UINT32 numBytes);
    void ege_pool_deallocate(void* data);

    /* ###################################################################
    *  ############# MEMORY ALLOCATOR FOR STD ALLOCATOR ##################
    *  ################################################################ */

    /**
    * Memory allocator using LinearAllocator
    */
    template<>
    class MemoryAllocator<PoolAllocator> : public MemoryAllocatorBase
    {
    public:
        static void* Allocate(size_t bytes)
        {
#if EGE_DEBUG
            AddNewCount();
#endif
            return gPoolAllocator().Allocate((UINT32)bytes);
        }

        static void Deallocate(void* ptr)
        {
#if EGE_DEBUG
            AddFreeCount();
#endif
            gPoolAllocator().Deallocate(ptr);
        }
    };
}