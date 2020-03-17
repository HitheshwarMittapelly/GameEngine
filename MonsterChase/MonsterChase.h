#pragma once
#include <Windows.h>
#include "headerfiles.h"

#include "GLib/GLib.h"
//#include "MemorySystem.h"
#include "Engine/InputSystem.h"
#include "Engine/RenderSystem.h"
#include "Engine/PhysicsSystem.h"
#include <assert.h>

#include <stdio.h>
#include <stdint.h>


#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG
using namespace std;
using namespace HeapManagerProxy;
namespace Monsterchase {
	
		
		bool Initialize();
		bool InitializeGLib(HINSTANCE i_hInstance, int i_nCmdShow, const char * windowName, WORD i_IcondId, unsigned int height, unsigned int width);
			
		
		void game(bool bSuccess);
	
		
		
}
