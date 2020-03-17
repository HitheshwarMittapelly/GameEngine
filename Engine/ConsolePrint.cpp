#include "ConsolePrint.h"
#include <Windows.h>
#include <assert.h>		
#include <stdarg.h>		
#include <stdio.h>	
#include <string.h>


namespace Engine 
{
	void ConsolePrint(const char * i_fmt, ...)
	{
		assert(i_fmt);
		const size_t bufferLength = 256;
		char temp[bufferLength] = "LOG : ";
		strcat_s(temp, i_fmt);
		strcat_s(temp, "\n");
		const size_t outputBufferLength = bufferLength + 32;
		char outputBuffer[outputBufferLength];
		va_list args;



		va_start(args, i_fmt);

		vsprintf_s(outputBuffer,outputBufferLength,temp,args);

		va_end(args);

		OutputDebugStringA(outputBuffer);


	}
}
