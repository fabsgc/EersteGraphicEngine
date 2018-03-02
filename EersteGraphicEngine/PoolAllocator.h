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

    template <size_t ElementSize = 4, size_t ElementsPerBlock = 512, size_t Alignment = 4>
    class PoolAllocator
    {
    private:
        class PoolBlock
        {
        public:
            PoolBlock(UINT8* poolBlock)
                : _poolBlock(poolBlock)
                , _freePtr(0)
                , _freeElements(ElementsPerBlock)
                , _nextBlock(nullptr)
            {
                UINT32 offset = 0;
                for (UINT32 i = 0; i < ElementsPerBlock; i++)
                {
                    UINT32* entryPtr = (UINT32*)&_poolBlock[offset];

                    offset += ActualElementSize;
                    *entryPtr = offset;
                }
            }

            ~PoolBlock()
            {
                EGE_ASSERT_ERROR((_freeElements == ElementsPerBlock), "Not all elements were deallocated from a block.");
            }

            UINT8 * Allocate()
            {
                UINT8* freeEntry = &_poolBlock[_freePtr];
                _freePtr = *(UINT32*)freeEntry;
                --_freeElements;

                return freeEntry;
            }

            void Deallocate(void* data)
            {
                UINT32* entryPtr = (UINT32*)data;
                *entryPtr = _freePtr;
                ++_freeElements;

                _freePtr = (UINT32)(((UINT8*)data) - _poolBlock);
            }

        public:
            UINT8 *    _poolBlock;
            UINT32     _freePtr;
            UINT32     _freeElements;
            PoolBlock* _nextBlock;
        };

    public:
        PoolAllocator()
        {
            EGE_ASSERT_ERROR((ElementSize >= 4), "Pool allocator minimum allowed element size is 4 bytes.");
            EGE_ASSERT_ERROR((ElementsPerBlock > 0), "Number of elements per block must be at least 1.");
            EGE_ASSERT_ERROR((ElementsPerBlock * ActualElementSize <= UINT_MAX), "Pool allocator block size too large.");
        }

        ~PoolAllocator()
        {

        }

        void * Allocate(size_t amount = sizeof(UINT32))
        {
            if (_freePoolBlock == nullptr || _freePoolBlock->_freeElements == 0)
                AllocatePoolBlock();

            _totalElements++;
            return (void*)_freePoolBlock->Allocate();
        }

        void Deallocate(void* data)
        {
            PoolBlock* currentBlock = _freePoolBlock;
            while (currentBlock)
            {
                constexpr UINT32 blockDataSize = ActualElementSize * ElementsPerBlock;
                if (data >= currentBlock->_poolBlock && data < (currentBlock->_poolBlock + blockDataSize))
                {
                    currentBlock->Deallocate(data);
                    _totalElements--;

                    if (currentBlock->_freeElements == 0 && currentBlock->_nextBlock)
                    {
                        // Free the block, but only if there is some extra free space in other blocks
                        const UINT32 totalSpace = (_numberBlocks - 1) * ElementsPerBlock;
                        const UINT32 freeSpace = totalSpace - _totalElements;

                        if (freeSpace > ElementsPerBlock / 2)
                        {
                            _freePoolBlock = currentBlock->_nextBlock;
                            DeallocatePoolBlock(currentBlock);
                        }
                    }

                    return;
                }

                currentBlock = currentBlock->_nextBlock;
            }
            
            EGE_ASSERT_ERROR(false, "Can't deallocate memory pool");
        }

    private:
        PoolAllocator(PoolAllocator const&) = delete;
        PoolAllocator& operator=(PoolAllocator const&) = delete;

        PoolBlock* AllocatePoolBlock()
        {
            PoolBlock* newBlock = nullptr;
            PoolBlock* currentBlock = _freePoolBlock;

            while (currentBlock != nullptr)
            {
                PoolBlock* nextBlock = currentBlock->_nextBlock;
                if (nextBlock != nullptr && nextBlock->_freeElements > 0)
                {
                    // Found an existing block with free space
                    newBlock = nextBlock;

                    currentBlock->_nextBlock = newBlock->_nextBlock;
                    newBlock->_nextBlock = _freePoolBlock;

                    break;
                }

                currentBlock = nextBlock;
            }

            if (newBlock == nullptr)
            {
                constexpr UINT32 blockDataSize = ActualElementSize * ElementsPerBlock;
                size_t paddedBlockDataSize = blockDataSize + (Alignment - 1); // Padding for potential alignment correction

                UINT8* data = (UINT8*)ege_allocate(sizeof(PoolBlock) + (UINT32)paddedBlockDataSize);

                void* blockData = data + sizeof(PoolBlock);
                blockData = std::align(Alignment, blockDataSize, blockData, paddedBlockDataSize);

                newBlock = new (data) PoolBlock((UINT8*)blockData);
                _numberBlocks++;

                newBlock->_nextBlock = _freePoolBlock;
            }

            _freePoolBlock = newBlock;
            return newBlock;
        }

        void DeallocatePoolBlock(PoolBlock* block)
        {
            block->~PoolBlock();
            ege_deallocate(block);

            _numberBlocks--;
        }

    private:
        static constexpr int ActualElementSize = ((ElementSize + Alignment - 1) / Alignment) * Alignment;

        PoolBlock* _freePoolBlock;
        UINT32     _totalElements;
        UINT32     _numberBlocks;
    };
}