#include "Engine.h"
#include "RenderSystem.h"
#include "PhysicsSystem.h"
#include "Lua/export/lua.hpp"
#include "TimerSystem.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>

#define INSTALLDIR SOLUTION_DIR
namespace fs = std::filesystem;


namespace {
	std::wstring ConvertUtf8ToUtf16(const char* const i_string_utf8)
	{
		// Calculate how many UTF-16 code units are required
		int requiredCodeUnitCount_includingNullTerminator;
		constexpr DWORD flags = 0;
		constexpr int processEntireString = -1;
		{
			constexpr wchar_t* const noOutput = nullptr;
			constexpr int returnRequiredCount = 0;

			requiredCodeUnitCount_includingNullTerminator = MultiByteToWideChar(CP_UTF8, flags, i_string_utf8,
				processEntireString, noOutput, returnRequiredCount);
			if (requiredCodeUnitCount_includingNullTerminator != 0)
			{

			}
			else
			{
				std::cout << "Windows Error: Invalid conversion" << std::endl;
			}
		}
		// Allocate space
		if (requiredCodeUnitCount_includingNullTerminator > 1)
		{
			std::wstring o_string_utf16(requiredCodeUnitCount_includingNullTerminator, L'\0');
			// Convert the string
			{

				const auto convertedCodeUnitCount = MultiByteToWideChar(CP_UTF8, flags, i_string_utf8,
					processEntireString, &o_string_utf16[0], requiredCodeUnitCount_includingNullTerminator);
				if (convertedCodeUnitCount != 0)
				{

					// std::wstring automatically manages NULL terminators
					o_string_utf16.resize(requiredCodeUnitCount_includingNullTerminator - 1);
				}
				else
				{
					std::cout << "Windows Error: Invalid conversion" << std::endl;
				}
			}

			return o_string_utf16;
		}
		else
		{
			// The string is empty
			return std::wstring();
		}
	}

	std::string ConvertUtf16ToUtf8(const wchar_t* const i_string_utf16)
	{
		// Calculate how many UTF-18 code units are required
		int requiredCodeUnitCount_includingNullTerminator;
		constexpr DWORD flags = 0;
		constexpr int processEntireString = -1;
		constexpr char* const defaultCharacter = nullptr;	// This must be NULL for UTF-8
		constexpr BOOL* const wasDefaultCharacterUsed = nullptr;	// This must be NULL for UTF-8
		{
			constexpr char* const noOutput = nullptr;
			constexpr int returnRequiredCount = 0;

			requiredCodeUnitCount_includingNullTerminator = WideCharToMultiByte(CP_UTF8, flags, i_string_utf16,
				processEntireString, noOutput, returnRequiredCount,
				defaultCharacter, wasDefaultCharacterUsed);
			if (requiredCodeUnitCount_includingNullTerminator != 0)
			{

			}
			else
			{
				std::cout << "Windows Error: Invalid conversion" << std::endl;
			}
		}
		// Allocate space
		if (requiredCodeUnitCount_includingNullTerminator > 1)
		{
			std::string o_string_utf8(requiredCodeUnitCount_includingNullTerminator, '\0');
			// Convert the string
			{

				const auto convertedCodeUnitCount = WideCharToMultiByte(CP_UTF8, flags, i_string_utf16,
					processEntireString, &o_string_utf8[0], requiredCodeUnitCount_includingNullTerminator,
					defaultCharacter, wasDefaultCharacterUsed);
				if (convertedCodeUnitCount != 0)
				{

					// std::string automatically manages NULL terminators
					o_string_utf8.resize(requiredCodeUnitCount_includingNullTerminator - 1);
				}
				else
				{
					std::cout << "Windows Error: Invalid conversion" << std::endl;
				}
			}

			return o_string_utf8;
		}
		else
		{
			// The string is empty
			return std::string();
		}
	}

}



namespace Engine {
	static std::vector<SmartPointer<GameObject2D> *> AllBlockObjects;
	static std::vector<SmartPointer<GameObject2D> *> BorderObjects;
	
	GLib::Sprites::Sprite * introSprite;
	GLib::Sprites::Sprite * loseSprite;
	GLib::Sprites::Sprite * winSprite;
	int currentKills = 0;
	int totalBlocks = 30;
	GLib::Sprites::Sprite * currentSprite;
	static bool bQuitGame = false;
	static bool inPlayMode = false;

	//This is where it all gets started
	bool Engine::Init()
	{
		
		pBall = CreateGameObject("Ball.lua");
		pPlayerPlatform = CreateGameObject("Platform.lua");
		//Collider that detects end game
		char * bName = new char[2];
		bName[0] = 'Z';
		bName[1] = 'B';
		Point2D lowerPos = Point2D(0, -320);
		pEndCollider = CreateGameObjectAtPosition("UpperBorder.lua", bName, lowerPos, 0);
		
		//Create border first
		CreateBorders();
		//Create Blocks
		CreateBlocks();
		//Create Different screen sprites
		CreateScreenSprites();
		
		return true;
	}

	

	//Border generation
	void CreateBorders()
	{
		Point2D leftPos = Point2D(-400, -300);
		Point2D rightPos = Point2D(400, -300);
		Point2D upperPos = Point2D(0, 290);
		char * lName = new char[2];
		lName[0] = 'L';
		lName[1] = 'B';
		BorderObjects.push_back(CreateGameObjectAtPosition("Border.lua", lName, leftPos, 0));
		char * rName = new char[2];
		rName[0] = 'R';
		rName[1] = 'B';
		BorderObjects.push_back(CreateGameObjectAtPosition("Border.lua", rName, rightPos, 0));
		char * uName = new char[2];
		uName[0] = 'U';
		uName[1] = 'B';
		BorderObjects.push_back(CreateGameObjectAtPosition("UpperBorder.lua", uName, upperPos, 0));
	}

	//Block generation
	void CreateBlocks()
	{
		//Create blocks
		int  step = 10;
		for (int i = 0; i < totalBlocks; i++) {
			char digit = '0' + i;

			char * name = new char[2];
			name[0] = 'B';
			name[1] = digit;
			Point2D pos = Point2D(0, 0);
			if (i == 0) {
				pos = Point2D(-360, 265);
			}
			else {
				pos = Point2D(-360.0f + ((i%step) * 80), 265.0f - ((i / step) * 30));
			}
			AllBlockObjects.push_back(CreateGameObjectAtPosition("Block.lua", name, pos, 0));
		}
	}

	//Sprites for win, lose and start screen
	void CreateScreenSprites()
	{
		introSprite = RenderSystem::CreateSprite("data\\IntroSprite.dds");
		loseSprite = RenderSystem::CreateSprite("data\\Lose.dds");
		winSprite = RenderSystem::CreateSprite("data\\Won.dds");
		currentSprite = introSprite;
	}

	void InitTimer()
	{
		TimerSystem::GetCPUFrequency();
	}

	void Run()
	{
		float dt = TimerSystem::GetElapsedTimeinMS();
		CheckInput();
		RenderSystem::BeginRendering();
		//If playing we want to update physics
		if (inPlayMode) {
			
			PhysicsSystem::Run(dt);
			RenderSystem::Draw();
			
		}
		//else show the current screen
		else {

			RenderSystem::DrawSprite(*currentSprite,Point2D(0, 0));
		}
		RenderSystem::StopRendering();

	}
	void Game(bool bSuccess)
	{
		if (bSuccess)
		{
			//Starts the Timer
			InitTimer();
			// Input system call backs init
			InputSystem::Init();
			bool bQuit = false;

			do
			{
				// IMPORTANT: We need to let GLib do it's thing. 
				GLib::Service(bQuit);

				if (!bQuit)
				{
					
					Engine::Run();
					bQuit = QuitCallback();
				}
			} while (bQuit == false);
			if (bQuit) {
				Cleanup();
			}
		}
	}

	bool QuitCallback()
	{
		return bQuitGame;
	}


	void Cleanup()
	{
		//Release the screen sprites
		GLib::Sprites::Release(introSprite);
		GLib::Sprites::Release(loseSprite);
		GLib::Sprites::Release(winSprite);
		
		//Render system cleanup
		RenderSystem::CleanUp();
		//Physics System cleanup
		PhysicsSystem::CleanUp();

		//Border objects cleanup
		for (unsigned i = 0; i < BorderObjects.size(); i++) {

			delete BorderObjects.at(i);
		}
		BorderObjects.clear();
		BorderObjects.shrink_to_fit();

		std::vector<SmartPointer<GameObject2D> *>().swap(BorderObjects);
		BorderObjects.~vector();

		//Block objects cleanup
		for (unsigned i = 0; i < AllBlockObjects.size(); i++) {

			delete AllBlockObjects.at(i);
		}
		AllBlockObjects.clear();
		AllBlockObjects.shrink_to_fit();

		std::vector<SmartPointer<GameObject2D> *>().swap(AllBlockObjects);
		AllBlockObjects.~vector();


		//Other gameobjects
		delete pEndCollider;
		delete pPlayerPlatform;
		delete pBall;

		//Shutdown Input system
		InputSystem::ShutDown();
		
		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
		GLib::Shutdown();
		
	}

	void CheckInput()
	{
		float force = 0.25f;
		if (InputSystem::CheckIfKeyDown((int)'A')) {
			//DEBUG_PRINT("Pressed A");
			PhysicsSystem::AddForce(-force, 1, *pPlayerPlatform);
			
		}
		if (InputSystem::CheckIfKeyUp((int)'A')) {
			//DEBUG_PRINT("Pressed A");
			PhysicsSystem::RemoveForce(force, 1, *pPlayerPlatform);
		}
		if (InputSystem::CheckIfKeyDown((int)'D')) {
			//DEBUG_PRINT("Pressed D");
			PhysicsSystem::AddForce(force, 1, *pPlayerPlatform);
			
		}
		if (InputSystem::CheckIfKeyUp((int)'D')) {
			//DEBUG_PRINT("Pressed D");
			PhysicsSystem::RemoveForce(-force, 1, *pPlayerPlatform);
		}

		//Starts the game
		if (InputSystem::CheckIfKeyDown((int)'J')) {
			inPlayMode = true;
			PhysicsSystem::AddVelocity(Point2D(0.2f, 0.4f));
		}
		if (InputSystem::CheckIfKeyDown((int)'Q')) {
			DEBUG_PRINT("Quit game requested");
			bQuitGame = true;
		}

	}

	void GameOver()
	{
		inPlayMode = false;
		currentSprite = loseSprite;
	}

	void CheckForGameWin()
	{
		if (currentKills >= totalBlocks) {
			inPlayMode = false;
			currentSprite = winSprite;
		}
	}
	
	//Destroys a block
	void KillBlock(SmartPointer<GameObject2D> * i_KillableGO) {
		for (size_t i = 0; i < AllBlockObjects.size();i++) {
			auto killableGO = AllBlockObjects.at(i);
			//Found the block
			if (*i_KillableGO == *killableGO) {
				delete killableGO;
				AllBlockObjects.erase(AllBlockObjects.begin() + i);
				AllBlockObjects.shrink_to_fit();
				currentKills++;
				CheckForGameWin();
				break;
			}
		}
		
	}

	//Creates Game object from lua file
	SmartPointer<GameObject2D>* CreateGameObject(const char * i_pFileName)
	{
		lua_State * pLuaState = luaL_newstate();
		assert(pLuaState);
		luaL_openlibs(pLuaState);

		// Append The data path and file name
		char str_Result[100];
		strcpy_s(str_Result, "data\\");
		strcat_s(str_Result, i_pFileName);

		size_t 		sizeFile = 0;
		uint8_t * 	pFileContents = reinterpret_cast<uint8_t *>(RenderSystem::LoadFile(str_Result, sizeFile));

		if (pFileContents  && sizeFile)
		{
			int 		result = 0;

			// Necessary stuff to process our data
			result = luaL_loadbuffer(
				pLuaState, reinterpret_cast<char *>(pFileContents), sizeFile, nullptr);
			assert(result == 0);

			result = lua_pcall(pLuaState, 0, 0, 0);
			assert(result == 0);
		}
		// Read Data
		int result = lua_getglobal(pLuaState, "Player");
		assert(str_Result == LUA_TNIL || result == LUA_TTABLE);

		// Get name
		lua_pushstring(pLuaState, "name");
		int type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TSTRING);

		const char* pName = _strdup(lua_tostring(pLuaState, -1));
		lua_pop(pLuaState, 1);	// Table on 1

		//DEBUG_PRINT("Name - %s", pName);

		// Get Initial Position
		lua_pushstring(pLuaState, "m_Position");	// Table on 2
		type = lua_gettable(pLuaState, -2);
		assert(str_Result == LUA_TNIL || result == LUA_TTABLE);
		lua_pushnil(pLuaState);

		float initPosition[2] = { 0.0 };
		int index = 0;
		while (lua_next(pLuaState, -2) != 0)
		{
			assert(lua_type(pLuaState, -2) == LUA_TNUMBER);
			assert(lua_type(pLuaState, -1) == LUA_TNUMBER);

			initPosition[index] = static_cast<float>(lua_tonumber(pLuaState, -1));
			// pop the value
			lua_pop(pLuaState, 1);
			index++;
		}
		lua_pop(pLuaState, 1);
		// Create Vector2
		Point2D playerPos(initPosition[0], initPosition[1]);

		//DEBUG_PRINT("Position - %f..%f", playerPos.x(), playerPos.y());

		lua_pushstring(pLuaState, "m_Orientation");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TNUMBER);

		float playerRot = static_cast<float>(lua_tonumber(pLuaState, -1));
		lua_pop(pLuaState, 1);	// Table on 1

		//DEBUG_PRINT("Player rotation - %f", playerRot);



		SmartPointer<GameObject2D> * m_Object = new SmartPointer<GameObject2D>(GameObject2D::Create(pName, playerPos, playerRot));
		// Render stuff
		lua_pushstring(pLuaState, "render_info");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TTABLE);

		lua_pushstring(pLuaState, "playerSprite");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TSTRING);
		const char* m_SpriteFilePath = _strdup(static_cast<const char*>(lua_tostring(pLuaState, -1)));
		
		//DEBUG_PRINT("sprite path -%s", m_SpriteFilePath);

		lua_pop(pLuaState, 2);
		// Add to Render Component
		RenderSystem::AddRenderable(new RenderSystem::Renderable(*m_Object, RenderSystem::CreateSprite(m_SpriteFilePath)));


		// Physics stuff
		lua_pushstring(pLuaState, "physics_info");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TTABLE);

		lua_pushstring(pLuaState, "mass");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TNUMBER);
		float m_PlayerMass = static_cast<float>(lua_tonumber(pLuaState, -1));
		lua_pop(pLuaState, 1);
		//DEBUG_PRINT("Mass -%f", m_PlayerMass);
		lua_pushstring(pLuaState, "coeffOfFriction");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TNUMBER);
		float m_GOCoeffOfFriction = static_cast<float>(lua_tonumber(pLuaState, -1));
		lua_pop(pLuaState, 1);
		//DEBUG_PRINT("k -%f", m_GOCoeffOfFriction);
		lua_pushstring(pLuaState, "static");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TBOOLEAN);
		bool isStatic = static_cast<bool>(lua_toboolean(pLuaState, -1));
		lua_pop(pLuaState, 2);
		
		lua_pushstring(pLuaState, "ExtentsX");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TNUMBER);
		float extentsX = static_cast<float>(lua_tonumber(pLuaState, -1));
		lua_pop(pLuaState, 1);
		lua_pushstring(pLuaState, "ExtentsY");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TNUMBER);
		float extentsY = static_cast<float>(lua_tonumber(pLuaState, -1));
		lua_pop(pLuaState, 1);

		Point2D m_Extents = Point2D(extentsX, extentsY);
		PhysicsSystem::AddPhysicsObject(new PhysicsSystem::PhysicsInfo(*m_Object, m_PlayerMass, m_Extents, isStatic));


		
		delete m_SpriteFilePath;
		delete pFileContents;
		lua_close(pLuaState);
		return m_Object;
	}

	//Comfy way to create a game object at a specified position (Used for blocks)
	SmartPointer<GameObject2D>* CreateGameObjectAtPosition(const char * i_pFileName, const char * ip_Name, Point2D i_Pos, float i_Rot)
	{
		lua_State * pLuaState = luaL_newstate();
		assert(pLuaState);
		luaL_openlibs(pLuaState);

		// Append The data path and file name
		char str_Result[100];
		strcpy_s(str_Result, "data\\");
		strcat_s(str_Result, i_pFileName);

		size_t 		sizeFile = 0;
		uint8_t * 	pFileContents = reinterpret_cast<uint8_t *>(RenderSystem::LoadFile(str_Result, sizeFile));

		if (pFileContents  && sizeFile)
		{
			int 		result = 0;

			// Necessary stuff to process our data
			result = luaL_loadbuffer(
				pLuaState, reinterpret_cast<char *>(pFileContents), sizeFile, nullptr);
			assert(result == 0);

			result = lua_pcall(pLuaState, 0, 0, 0);
			assert(result == 0);
		}
		// Read Data
		int result = lua_getglobal(pLuaState, "Player");
		assert(str_Result == LUA_TNIL || result == LUA_TTABLE);


		SmartPointer<GameObject2D> * m_Object = new SmartPointer<GameObject2D>(GameObject2D::Create(ip_Name, i_Pos, i_Rot));
		// Render stuff
		lua_pushstring(pLuaState, "render_info");
		int type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TTABLE);

		lua_pushstring(pLuaState, "playerSprite");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TSTRING);
		const char* m_SpriteFilePath = _strdup(static_cast<const char*>(lua_tostring(pLuaState, -1)));
		//lua_pop(pLuaState, 1);	
		//DEBUG_PRINT("sprite path -%s", m_SpriteFilePath);

		lua_pop(pLuaState, 2);
		// Add to Render Component
		RenderSystem::AddRenderable(new RenderSystem::Renderable(*m_Object, RenderSystem::CreateSprite(m_SpriteFilePath)));


		// Physics stuff
		lua_pushstring(pLuaState, "physics_info");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TTABLE);

		lua_pushstring(pLuaState, "mass");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TNUMBER);
		float m_PlayerMass = static_cast<float>(lua_tonumber(pLuaState, -1));
		lua_pop(pLuaState, 1);
		//DEBUG_PRINT("Mass -%f", m_PlayerMass);
		lua_pushstring(pLuaState, "coeffOfFriction");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TNUMBER);
		float m_GOCoeffOfFriction = static_cast<float>(lua_tonumber(pLuaState, -1));
		lua_pop(pLuaState, 1);
		//DEBUG_PRINT("k -%f", m_GOCoeffOfFriction);

		lua_pushstring(pLuaState, "static");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TBOOLEAN);
		bool isStatic = static_cast<bool>(lua_toboolean(pLuaState, -1));
		lua_pop(pLuaState, 2);
		if (isStatic) {
			//DEBUG_PRINT("static object");
		}
		else {
			//DEBUG_PRINT("non-static object");
		}

		lua_pushstring(pLuaState, "ExtentsX");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TNUMBER);
		float extentsX = static_cast<float>(lua_tonumber(pLuaState, -1));
		lua_pop(pLuaState, 1);
		lua_pushstring(pLuaState, "ExtentsY");
		type = lua_gettable(pLuaState, -2);
		assert(type == LUA_TNUMBER);
		float extentsY = static_cast<float>(lua_tonumber(pLuaState, -1));
		lua_pop(pLuaState, 1);

		Point2D m_Extents = Point2D(extentsX, extentsY);
		PhysicsSystem::AddPhysicsObject(new PhysicsSystem::PhysicsInfo(*m_Object, m_PlayerMass, m_Extents, isStatic));


		
		delete m_SpriteFilePath;
		delete pFileContents;
		lua_close(pLuaState);
		return m_Object;
	}
}