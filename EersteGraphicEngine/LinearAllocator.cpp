#include "PrerequisitesUtil.h"
#include "LinearAllocator.h"

namespace ege
{
	LinearAllocator* _GlobalLinearAllocator = nullptr;

	LinearAllocator& gLinearAllocator()
	{
		if (_GlobalLinearAllocator == nullptr)
		{
			// Note: This will leak memory but since it should exist throughout the entirety 
			// of runtime it should only leak on shutdown when the OS will free it anyway.
			_GlobalLinearAllocator = new LinearAllocator();
		}

		return *_GlobalLinearAllocator;
	}

	void* ege_linear_allocate(UINT32 numBytes)
	{
		return gLinearAllocator().Allocate(numBytes);
	}

	void ege_linear_deallocate(void* data)
	{
		gLinearAllocator().Deallocate((UINT8*)data);
	}
}