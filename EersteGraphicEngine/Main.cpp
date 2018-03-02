#include "CoreApplication.h"
#include <windows.h>

using namespace ege;

int CALLBACK WinMain(_In_  HINSTANCE hInstance, _In_  HINSTANCE hPrevInstance, _In_  LPSTR lpCmdLine, _In_  int nCmdShow)
{
    /*PoolAllocator<sizeof(UINT32)>* poolAllocator = new PoolAllocator<sizeof(UINT32)>();

    {
        auto ptr1 = ege_unique_ptr_allocator_new<UINT32, PoolAllocator<sizeof(UINT32)>>(poolAllocator);
        *ptr1 = 45;

        auto ptr3 = ege_unique_ptr_allocator<UINT32, PoolAllocator<sizeof(UINT32)>>(&(*ptr1), poolAllocator);
        *ptr3 = 44;

        auto ptr2 = ege_shared_ptr_allocator_new<UINT32, PoolAllocator<sizeof(UINT32)>>(poolAllocator);
        *ptr2 = 42;
    }

    UINT32* ptr4 = (UINT32*)poolAllocator->Allocate();
    *ptr4 = 50;

    poolAllocator->Deallocate((void*)ptr4);

    delete poolAllocator;*/

    START_UP_DESC desc;

    desc.WindowDesc.Width = 960;
    desc.WindowDesc.Height = 540;
    desc.WindowDesc.Title = "My first application";

    CoreApplication::StartUp(desc);
    CoreApplication& app = gCoreApplication();

    app.RunMainLoop();
    app.ShutDown();

    return 0;
}