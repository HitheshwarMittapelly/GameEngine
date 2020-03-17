#include "HeapManagerProxy.h"


#include <assert.h>
#include <stdio.h>

#include "HeapManager.h"

namespace HeapManagerProxy
{

	HeapManager * CreateHeapManager(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
	{
		return  HeapManager::createHeapManager(i_pMemory, i_sizeMemory, i_numDescriptors);
	}



	void * alloc(HeapManager * i_pManager, size_t i_size)
	{
		assert(i_pManager);
		return i_pManager->alloc(i_size);
	}

	void * alloc(HeapManager * i_pManager, size_t i_size, unsigned int i_alignment)
	{
		assert(i_pManager);

		return i_pManager->alloc(i_size, i_alignment);
	}
	bool free(HeapManager * i_pManager, void * i_ptr) 
	{
		assert(i_pManager);
		return i_pManager->free(i_ptr);
	}
	bool IsAllocated(HeapManager * i_pManager, void * i_ptr)
	{
		assert(i_pManager);
		return i_pManager->isAllocated(i_ptr);
	}
	bool Contains(HeapManager * i_pManager, void * i_ptr)
	{
		assert(i_pManager);
		return i_pManager->contains(i_ptr);
	}
	void ShowFreeBlocks(HeapManager * i_pManager)
	{
		assert(i_pManager);
		return i_pManager->showFreeBlocks();
	}
	void ShowOutstandingAllocations(HeapManager * i_pManager)
	{
		assert(i_pManager);
		return i_pManager->ShowOutstandingAllocations();
	}

	size_t	GetLargestFreeBlock( HeapManager * i_pManager)
	{
		assert(i_pManager);
		return i_pManager->getLargestFreeBlock();
	}
	size_t	GetTotalFreeMemory( HeapManager * i_pManager)
	{
		assert(i_pManager);
		return i_pManager->getTotalFreeMemory();
	}
	void Collect(HeapManager * i_pManager)
	{
		assert(i_pManager);
		return i_pManager->collect();
	}
	void Destroy(HeapManager * i_pManager)
	{
		assert(i_pManager);
		return i_pManager->destroy();
	}
}
