
#pragma once
#include "HeapManager.h"
#include "ConsolePrint.h"
#include <cstdlib>
#include "assert.h"

#include "FixedSizeAllocator.h"
//namespace Allocator {
//	extern HeapManager * mainHeap;
//}

//
void * __cdecl malloc(size_t i_size) ;
void __cdecl free(void * i_ptr) ;
void* operator new(size_t);
void operator delete(void*);

void* operator new[](size_t);

void operator delete[](void*);

//void * operator new(size_t size, HeapManager * i_pManager);
//void operator delete(void * p, HeapManager * i_pManager);
//
//void * operator new(size_t size, unsigned int nAlignment);
//void operator delete(void *p, unsigned int nAlignment);






