#pragma once
#include <cstdint>
#include "BitArray.h"


class FixedSizeAllocator 
{
public:
	
	void setupInfo(size_t size, size_t numOfBlocks, uintptr_t startAddress)
	{
		this->size = size;
		this->numOfBlocks = numOfBlocks;
		this->startAddress = startAddress;
		size_t sizeOfByte = 8;
		if (numOfBlocks % sizeOfByte == 0)
			bitArray.setMaxBytes(numOfBlocks / sizeOfByte);
		else
			bitArray.setMaxBytes((numOfBlocks / sizeOfByte) + 1);
		bitArray.ClearAll();
		
	}
	void * alloc();
	bool free(void * iPtr);
	bool contains(void * iptr);
	size_t getSize() {
		return size;
	}
private:
	uintptr_t startAddress;
	size_t size;
	size_t numOfBlocks;
	BitArray bitArray;
	

};