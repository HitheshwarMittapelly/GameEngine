#include "HeapManager.h"

#include <cstdint>
#include <assert.h>
#include <iostream>
#include "ConsolePrint.h"
using namespace std;
HeapManager*  HeapManager::createHeapManager(void * i_pMemoryBlock, size_t size, unsigned int numOfdDescriptors)
{
	static HeapManager Instance;
	Instance.heapMemory.startAddress = reinterpret_cast<uintptr_t>(i_pMemoryBlock);
	Instance.heapMemory.blockSize = size;
	Instance.sizeOfTotalMemory = size;
	Instance.numOfDescriptors = numOfdDescriptors;
	Instance.setUpDataAndDescriptorBlocks();

	return &Instance;
}


FixedSizeAllocator * HeapManager::getFixedSizeAllocator(size_t size)
{
	if (size <= FSA16.getSize())
		return &FSA16;
	else if (size <= FSA32.getSize())
		return &FSA32;
	else if (size <= FSA96.getSize())
		return &FSA96;
	else
		return NULL;
}

void HeapManager::setUpDataAndDescriptorBlocks()
{
	DEBUG_PRINT("Total bytes of memory %lu", sizeOfTotalMemory);

	sizeOfDescriptorsMemory = numOfDescriptors * sizeof(Descriptor);
	sizeOfDataMemory = sizeOfTotalMemory - sizeOfDescriptorsMemory;

	oneByte = reinterpret_cast<char *>(heapMemory.startAddress);
	oneByte += heapMemory.blockSize;
	oneByte -= sizeOfDescriptorsMemory;
	//provide start address and size for descriptor memory 
	descriptorMemoryDescriptor.startAddress = reinterpret_cast<uintptr_t>(oneByte);
	descriptorMemoryDescriptor.blockSize = sizeOfDescriptorsMemory;
	
	//Create Fixed size allocators using the memory in data memory
	//size 16 FSA setup
	size_t size = 16;
	size_t blocks = 100;
	uintptr_t memory = (heapMemory.startAddress);
	FSA16.setupInfo(size, blocks, memory);
	char * oneByte = reinterpret_cast<char *>(memory);
	oneByte += (size * blocks);
	memory = reinterpret_cast<uintptr_t>(oneByte);
	//size 32 FSA setup
	size = 32;
	blocks = 200;
	FSA32.setupInfo(size, blocks, memory);
	oneByte = reinterpret_cast<char *>(memory);
	oneByte += (size * blocks);
	memory = reinterpret_cast<uintptr_t>(oneByte);
	//size 96 FSA setup
	size = 96;
	blocks = 400;
	FSA96.setupInfo(size, blocks, memory);
	oneByte = reinterpret_cast<char *>(memory);
	oneByte += (size * blocks);
	memory = reinterpret_cast<uintptr_t>(oneByte);


	//Provide the start address for data memory
	sizeOfDataMemory -= (size * blocks);
	heapMemory.startAddress =memory;
	dataMemoryDescriptor.startAddress = heapMemory.startAddress;
	dataMemoryDescriptor.blockSize = sizeOfDataMemory ;
	
	DEBUG_PRINT("Data Memory itself is at %p ", dataMemoryDescriptor);
	DEBUG_PRINT("data memory start address %p", dataMemoryDescriptor.startAddress);

	DEBUG_PRINT("data memory bytes %lu", dataMemoryDescriptor.blockSize);


	DEBUG_PRINT("Descriptor Memory itself is at %p ", descriptorMemoryDescriptor);
	DEBUG_PRINT("descriptor memory is at %p", descriptorMemoryDescriptor.startAddress);

	DEBUG_PRINT("Descriptor memory bytes %lu", descriptorMemoryDescriptor.blockSize);

	freeList.addDescriptor(&dataMemoryDescriptor);

	//Generate 2048 descriptors
	generateDescriptorBlocks(&descriptorMemoryDescriptor);



}

void HeapManager::generateDescriptorBlocks(Descriptor * descriptorMemoryBlock)
{

	while (descriptorMemoryBlock->blockSize != 0)
	{

		oneByte = reinterpret_cast<char *>(descriptorMemoryBlock->startAddress);
		oneByte += descriptorMemoryBlock->blockSize;
		oneByte -= sizeof(Descriptor);
		Descriptor * nextDescriptorBlock = reinterpret_cast<Descriptor *>(oneByte);
		descriptorFreeList.addDescriptorBlock(nextDescriptorBlock);

		descriptorMemoryBlock->blockSize -= sizeof(Descriptor);

	}

}

void * HeapManager::alloc(size_t size)
{
	Descriptor * freeListReturned;
	//get the free memory from free list
	freeListReturned = freeList.getFirstFit(size + guardSize);

	if (freeListReturned == nullptr)
		return nullptr;
	//Allocate memory for new descriptor
	Descriptor * addToAllocatedList = allocateForDescriptor(sizeof(Descriptor));
	if (addToAllocatedList == NULL)
		return NULL;


	//iterate through the memory
	oneByte = reinterpret_cast<char *>(freeListReturned->startAddress);
	oneByte += freeListReturned->blockSize;
	oneByte -= (size + guardSize);


	//allocate start address and block size
	addToAllocatedList->startAddress = reinterpret_cast<uintptr_t>(oneByte);
	//Write guardbands
	oneByte += size;
	for (size_t i = 0; i < guardSize; i++)
	{
		*oneByte = guard;
		oneByte++;
	}
	addToAllocatedList->blockSize = (size + guardSize);

	freeListReturned->blockSize -= (size + guardSize);

	//add the new descriptors to the respective lists
	allocatedList.addDescriptor(addToAllocatedList);


	freeList.addDescriptor(freeListReturned);



	return reinterpret_cast<void *>(addToAllocatedList->startAddress);

}
void * HeapManager::alloc(size_t size, unsigned int alignment)
{
	Descriptor * freeListReturned;
	//get the free memory from free list
	freeListReturned = freeList.getFirstFit(size + (size_t)alignment);
	if (freeListReturned == nullptr)
		return nullptr;
	//Allocate memory for new descriptor
	Descriptor * addToAllocatedList = allocateForDescriptor(sizeof(Descriptor));
	//Descriptors run out of memory
	if (addToAllocatedList == NULL)
		return NULL;



	//iterate through the memory
	oneByte = reinterpret_cast<char *>(freeListReturned->startAddress);
	oneByte += freeListReturned->blockSize;
	oneByte -= (size);

	//Align to the given alignment
	size_t loopValue = 0;
	void * alignedAddress = reinterpret_cast<void *>(oneByte);
	while (!(reinterpret_cast<uintptr_t>(alignedAddress) & (alignment - 1)) == 0) {
		alignedAddress = (char*)alignedAddress - 1;
		loopValue = loopValue + (size_t)1;
	}

	//allocate start address and block size
	addToAllocatedList->startAddress = reinterpret_cast<uintptr_t>(alignedAddress);
	assert(((addToAllocatedList->startAddress) & (alignment - 1)) == 0);
	addToAllocatedList->blockSize = size + loopValue;

	freeListReturned->blockSize -= (size + loopValue);

	//add the new descriptors to the respective lists
	allocatedList.addDescriptor(addToAllocatedList);

	freeList.addDescriptor(freeListReturned);

	//showFreeBlocks();
	return reinterpret_cast<void *>(addToAllocatedList->startAddress);

}



Descriptor * HeapManager::allocateForDescriptor(size_t size)
{

	Descriptor * pReturnedFromList = descriptorFreeList.getNextFromList();
	if (pReturnedFromList == nullptr) {
		DEBUG_PRINT("Descriptors run out of memory");
		return NULL;
	}
	descriptorFreeList.deleteDescriptorBlock(pReturnedFromList);
	descriptorAllocatedList.addDescriptorBlock(pReturnedFromList);

	return pReturnedFromList;

}



bool HeapManager::free(void * i_ptr)
{
	if (FSA16.contains(i_ptr))
		return FSA16.free(i_ptr);
	else if (FSA32.contains(i_ptr))
		return FSA32.free(i_ptr);
	else if (FSA96.contains(i_ptr))
		return FSA96.free(i_ptr);

	Descriptor * freeingBlock = nullptr;
	freeingBlock = allocatedList.getDescriptorFromStartAddress(i_ptr);
	assert(freeingBlock);
	

	//delete from allocated list
	allocatedList.deleteDescriptor(freeingBlock);
	

	//add to free list

	freeList.addDescriptor(freeingBlock);
	return true;

}
bool HeapManager::isAllocated(void * i_ptr)
{
	Descriptor * pReturn = nullptr;
	pReturn = allocatedList.getDescriptorFromStartAddress(i_ptr);
	if (pReturn)
		return true;
	else
		return false;
}

bool HeapManager::contains(void * i_ptr)
{
	Descriptor * pReturn = nullptr;
	pReturn = allocatedList.getDescriptorFromStartAddress(i_ptr);
	if (!pReturn)
	{
		pReturn = freeList.getDescriptorFromStartAddress(i_ptr);
		if (!pReturn)
			return false;
		else
			return true;

	}
	else
		return true;

}

void HeapManager::destroy()
{
	freeList.deleteList();
	allocatedList.deleteList();
}

void HeapManager::showFreeBlocks()
{
	//1 is id for freelist
	freeList.displayList(1);
}
void HeapManager::ShowOutstandingAllocations()
{
	//2 is id for allocated list
	allocatedList.displayList(2);
}

size_t HeapManager::getLargestFreeBlock()
{
	return freeList.getLargestBlock();
}
size_t HeapManager::getTotalFreeMemory()
{
	return freeList.getTotalMemory();
}

void HeapManager::collect()
{
	freeList.joinConsecutiveBlocks(&descriptorFreeList, &descriptorAllocatedList);

}

