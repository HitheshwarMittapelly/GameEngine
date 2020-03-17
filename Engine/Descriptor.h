#pragma once
#include <cstdint>
namespace BlockDescriptor {
	struct Descriptor {
		
		uintptr_t  startAddress;
		size_t blockSize;
		
		Descriptor * next;
		Descriptor * nextDescriptor;
		
	};
}