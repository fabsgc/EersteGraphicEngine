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

   List<int, StdStackAllocator<int>> test(stackAllocator);

   test.push_back(1);
   test.push_back(1);
   test.push_back(1);
   test.push_back(1);
   test.push_back(1);
   test.push_back(1);

   return 0;
}