#include "PrerequisitesCore.h"

using namespace ege;

int CALLBACK WinMain(_In_  HINSTANCE hInstance, _In_  HINSTANCE hPrevInstance, _In_  LPSTR lpCmdLine, _In_  int nCmdShow)
{
   String str = "salut";
   Vector<int> test = { 1, 2, 3, 4 };
   SPtr<int> ptr = ege_shared_ptr_new<int, GeneralAllocator>();
   UPtr<int> ptr2 = ege_unique_ptr_new<int, GeneralAllocator>(1);

    return 0;
}