#pragma once
#include "HeapManager.h"

namespace Engine {
	
	void ConsolePrint(const char * i_fmt, ...); 

}

#if defined(_DEBUG)
#define DEBUG_PRINT(i_fmt,...) Engine::ConsolePrint(i_fmt,__VA_ARGS__) ;
#else
#define DEBUG_PRINT(fmt,...) void(0)
#endif 


