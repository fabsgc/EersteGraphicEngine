#include "PrerequisitesCore.h"

using namespace ege;

int CALLBACK WinMain(_In_  HINSTANCE hInstance, _In_  HINSTANCE hPrevInstance, _In_  LPSTR lpCmdLine, _In_  int nCmdShow)
{
   String str = "salut";

  // StackAllocator* stackAllocator = new StackAllocator(3 * sizeof(int));

   //Vector<int, StdAllocator<int, StackAllocator>> test = { 1, 2, 3, 4 };
   //SPtr<int> ptr = ege_shared_ptr_new<int, BasicAllocator>();
   //UPtr<int> ptr2 = ege_unique_ptr_new<int, BasicAllocator>(1);

   /*StackAllocator* stackAllocator = new StackAllocator(3 * sizeof(int));
   
   int* i = (int*)stackAllocator->Allocate(sizeof(int));
   int* j = (int*)stackAllocator->Allocate(sizeof(int));
   int* k = (int*)stackAllocator->Allocate(sizeof(int));
   *i = 5;*/

   //SPtr<int> ptr3 = ege_shared_ptr_new<int, StackAllocator>();
   //*ptr3 = 10;

   //EGE_LOG_DEBUG(*ptr3);

   StackAllocator* stackAllocator = new StackAllocator();

   //List<int, StdStackAllocator<int>> test(stackAllocator);
   /*List<int> test;

   test.push_back(1);
   test.push_back(2);
   test.push_back(3);
   test.push_back(4);
   test.clear();*/

   UINT8* var1 = (UINT8*)stackAllocator->Allocate(sizeof(UINT8));
   *var1 = (UINT8)'a';
   EGE_LOG_DEBUG(*var1);

   UINT16* var2 = (UINT16*)stackAllocator->Allocate(sizeof(UINT16));
   *var2 = 16;
   EGE_LOG_DEBUG(*var2);

   UINT32* var3 = (UINT32*)stackAllocator->Allocate(sizeof(UINT32));
   *var3 = 32;
   EGE_LOG_DEBUG(*var3);

   stackAllocator->Deallocate(var3);
   stackAllocator->Deallocate(var2);
   stackAllocator->Deallocate(var1);

   UINT8* var4 = (UINT8*)stackAllocator->Allocate(sizeof(UINT8));
   *var4 = (UINT8)'b';
   EGE_LOG_DEBUG(*var4);

   stackAllocator->Deallocate(var4);
   delete stackAllocator;

   return 0;
}