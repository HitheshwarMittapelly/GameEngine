#include "FixedSizeAllocator.h"
#include "ConsolePrint.h"
#include <iostream>
using namespace std;
void * FixedSizeAllocator::alloc()
{
	cout << "In FSA alloc with size "<<size<< endl;
	DEBUG_PRINT("In FSA alloc with size in hex %zx", size);
	size_t index = bitArray.GetFirstClearBit();
	//For some reason, I couldn't return null from the GetFirstClearBit so when I didn't find a index, I set index > numOfBlocks
	if (index > numOfBlocks)
		return nullptr;
	else
	{
		bitArray.SetBit(index);
		return reinterpret_cast<void *>(reinterpret_cast<char *>(startAddress) + (index * size));
	}
}

bool FixedSizeAllocator::free(void * iptr)
{
	cout << "In FSA free with size " <<size<< endl;
	DEBUG_PRINT("In FSA free with size in hex %zx", size);
	size_t index = reinterpret_cast<size_t>(iptr);

	index -= startAddress;
	index /= size;
	bitArray.ClearBit(index);
	return true;

}

bool FixedSizeAllocator::contains(void * iptr)
{
	uintptr_t pLocate = reinterpret_cast<uintptr_t>(iptr);
	if (pLocate >= startAddress && pLocate < (startAddress + (size * numOfBlocks)))
		return true;
	return false;
}
