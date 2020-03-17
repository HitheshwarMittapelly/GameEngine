#pragma once
#include "Descriptor.h"


using namespace BlockDescriptor;

class DescriptorList {

public:
	DescriptorList() {

	}

	~DescriptorList();

	void addDescriptor(Descriptor * newDescriptor);
	void addDescriptorBlock(Descriptor * newDescriptor);
	Descriptor * getDescriptorFromStartAddress(void * iptr);
	Descriptor * getDescriptorBlockFromStartAddress(void * startAddr);
	Descriptor * getNextFromList();
	Descriptor * getFirstFit(size_t size);
	void deleteDescriptor(Descriptor * deleteThis);
	void deleteDescriptorBlock(Descriptor * deleteThis);

	void displayList(int i);
	size_t getTotalMemory();
	size_t getLargestBlock();
	void  joinConsecutiveBlocks(DescriptorList * descriptorFreeList, DescriptorList * descriptorAllocatedList);

	void deleteList();

	void freeDescriptorPtr(Descriptor * deletePtr);


	

private:
	Descriptor * head;


};


