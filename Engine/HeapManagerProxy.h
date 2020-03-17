#pragma once
#include "HeapManager.h"
class HeapManager;

namespace HeapManagerProxy
{

	HeapManager *	CreateHeapManager(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors);
	void *			alloc(HeapManager * i_pManager, size_t i_size);
	void *			alloc(HeapManager * i_pManager, size_t i_size, unsigned int i_alignment);
	bool			free(HeapManager * i_pManager, void * i_ptr);
	bool			IsAllocated( HeapManager * i_pManager, void * i_ptr);
	bool			Contains(HeapManager * i_pManager, void * i_ptr);

	void			ShowFreeBlocks( HeapManager * i_pManager);
	void			ShowOutstandingAllocations( HeapManager * i_pManager);
	size_t			GetLargestFreeBlock( HeapManager * i_pManager);
	size_t			GetTotalFreeMemory( HeapManager * i_pManager);
	void			Collect(HeapManager * i_pManager);


	
	void			Destroy(HeapManager * i_pManager);

}

