#pragma once
#include "MonsterChase.h"
#include "Lua/export/lua.hpp"
#define _CRTDBG_MAP_ALLOC
#include "Engine/Matrix_UnitTest.h"
#include "Engine/Engine.h"
using namespace std;
using namespace Monsterchase;


namespace Monsterchase {

	bool Monsterchase::Initialize()
	{

		return Engine::Init();

	}

	bool Monsterchase::InitializeGLib(HINSTANCE i_hInstance, int i_nCmdShow, const char * windowName, WORD i_IcondId, unsigned int height, unsigned int width)
	{
		bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", i_IcondId, height, width);
		assert(bSuccess);
		return bSuccess;
	}


	void  Monsterchase::game(bool bSuccess)
	{
		Engine::Game(bSuccess);

	}

}

	
	


	
	

	
