#pragma once
#include "DescriptorList.h"
#include "FixedSizeAllocator.h"

class HeapManager
{
public:

	static HeapManager * createHeapManager(void * i_pMemoryBlock, size_t size, unsigned int numOfDescriptors);

	void * alloc(size_t size);
	void * alloc(size_t size, unsigned int allignment);
	bool free(void * i_ptr);
	bool isAllocated(void * i_ptr);
	bool contains(void * i_ptr);
	void destroy();
	void showFreeBlocks();
	void ShowOutstandingAllocations();
	size_t getLargestFreeBlock();
	size_t getTotalFreeMemory();
	void collect();
	
	FixedSizeAllocator * getFixedSizeAllocator(size_t size);
	
	
	static const size_t s_MinimumToLeave = 128;
	
private:
	HeapManager() {

	}
	Descriptor * allocateForDescriptor(size_t size);
	void setUpDataAndDescriptorBlocks();
	void generateDescriptorBlocks(Descriptor * descriptorMemoryBlock);

	Descriptor dataMemoryDescriptor;
	Descriptor  descriptorMemoryDescriptor;
	Descriptor  heapMemory;


	DescriptorList  freeList;
	DescriptorList  allocatedList;
	DescriptorList  descriptorAllocatedList;
	DescriptorList  descriptorFreeList;

	const char guard = 'g';
	const size_t guardSize = 4;
	unsigned int numOfDescriptors;
	size_t sizeOfTotalMemory;
	size_t sizeOfDataMemory;
	size_t sizeOfDescriptorsMemory;
	char * oneByte;
	FixedSizeAllocator  FSA16;
	FixedSizeAllocator FSA32;
	FixedSizeAllocator FSA96;


};




