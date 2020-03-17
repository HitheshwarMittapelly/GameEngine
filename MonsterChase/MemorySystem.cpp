#include "MemorySystem.h"

#include "Engine/HeapManagerProxy.h"
using namespace HeapManagerProxy;

bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors)
{
	// create your HeapManager and FixedSizeAllocators
	defaultHeap = CreateHeapManager(i_pHeapMemory, i_sizeHeapMemory, i_OptionalNumDescriptors);

	

	return true;
}

void Collect()
{
	
	
	// coalesce free blocks
	// you may or may not need to do this depending on how you've implemented your HeapManager
	Collect(defaultHeap);
}

void DestroyMemorySystem()
{
	// Destroy your HeapManager and FixedSizeAllocators
	Destroy(defaultHeap);
}

HeapManager * getMainHeap()
{
	return defaultHeap;
}
