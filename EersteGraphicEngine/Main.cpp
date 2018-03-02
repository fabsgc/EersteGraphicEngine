#include "PrerequisitesCore.h"

using namespace ege;

void custom_deleter(UINT32* type, void* allocator)
{
    PoolAllocator<sizeof(UINT32)>* alloc = static_cast<PoolAllocator<sizeof(UINT32)>*>(allocator);
    alloc->Deallocate(type);
}

int CALLBACK WinMain(_In_  HINSTANCE hInstance, _In_  HINSTANCE hPrevInstance, _In_  LPSTR lpCmdLine, _In_  int nCmdShow)
{
    PoolAllocator<sizeof(UINT32)>* poolAllocator = new PoolAllocator<sizeof(UINT32)>();

    //UPtr<UINT32> ptr = ege_unique_ptr_new<UINT32>(42);
    //UPtr<UINT32> ptr2 = ege_unique_ptr_allocator_new<UINT32, PoolAllocator<sizeof(UINT32)>>(poolAllocator);
    //*ptr2 = 45;
    //EGE_LOG_DEBUG(*ptr);
    //EGE_LOG_DEBUG(*ptr2);

    /*UINT32* rawPtr = (UINT32*)poolAllocator->Allocate(sizeof(UINT32));
    auto myDeleter = std::bind(custom_deleter, std::placeholders::_1, rawPtr, poolAllocator);
    std::unique_ptr<UINT32, decltype(myDeleter)> ptr(rawPtr, myDeleter);

    //ptr.release();*/

    UINT32* data = (UINT32*)poolAllocator->Allocate();
    *data = 25;

    return 0;
}