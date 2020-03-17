//#pragma once
//#include "stdio.h"
//#include <inttypes.h>
//#include <malloc.h>
//#include "MemorySystem.h"
//#include "ConsolePrint.h"
//
//
//void * __cdecl malloc(size_t i_size) 
//{
//
//	
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	printf("malloc %zu\n", i_size);
//
//	DEBUG_PRINT("malloc %zu\n", i_size);
//	FixedSizeAllocator * pFSA = getMainHeap()->getFixedSizeAllocator(i_size);
//	
//	if (pFSA)
//		return pFSA->alloc();
//	return getMainHeap()->alloc(i_size, 4);
//	
//}
//
//void __cdecl free(void * i_ptr)
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	printf("free %" PRIxPTR "\n" , reinterpret_cast<uintptr_t>(i_ptr));
//	DEBUG_PRINT("free  %lu \n", reinterpret_cast<uintptr_t>(i_ptr));
//	getMainHeap()->free(i_ptr);
//
//}
//
//void * operator new(size_t i_size) 
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	DEBUG_PRINT("new %zu\n", i_size);
//	printf("new %zu\n", i_size);
//	FixedSizeAllocator * pFSA = getMainHeap()->getFixedSizeAllocator(i_size);
//
//	
//	if (pFSA)
//		return pFSA->alloc();
//	return getMainHeap()->alloc(i_size, 4);
//	
//}
//
//void operator delete(void * i_ptr)
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	printf("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
//	DEBUG_PRINT("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
//	getMainHeap()->free(i_ptr);
//	
//}
//
//void * operator new[](size_t i_size)
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	printf("new [] %zu\n", i_size);
//	DEBUG_PRINT("new [] %zu\n", i_size);
//	FixedSizeAllocator * pFSA = getMainHeap()->getFixedSizeAllocator(i_size);
//
//	
//    if (pFSA)
//			return pFSA->alloc();
//	return getMainHeap()->alloc(i_size, 4);
//	
//}
//
//void operator delete [](void * i_ptr)
//{
//	// replace with calls to your HeapManager or FixedSizeAllocators
//	DEBUG_PRINT("delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
//	printf("delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
//	getMainHeap()->free(i_ptr);
//	
//}
//
//
//
//
