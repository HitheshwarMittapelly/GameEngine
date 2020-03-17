#include "TimerSystem.h"
#include <Windows.h>
static LARGE_INTEGER prevTime, currentTime, frequency, differTime;
void TimerSystem::GetCPUFrequency()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&prevTime);
}


float TimerSystem::GetElapsedTimeinMS()
{
	QueryPerformanceCounter(&currentTime);

	differTime.QuadPart = currentTime.QuadPart - prevTime.QuadPart;
	differTime.QuadPart *= 1000000;
	differTime.QuadPart /= frequency.QuadPart;
	
	prevTime = currentTime;
	float diffTime = static_cast<float>(differTime.QuadPart);
	if (diffTime > 180.0f) {
		diffTime = 180.0f;
	}
	diffTime /= 1000.0f;

	
	return diffTime;
}
