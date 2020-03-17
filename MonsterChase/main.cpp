


#include "MonsterChase.h"
//#include "CollisionPoolCheck.h"
int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
#if defined _DEBUG
		_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
#endif	
		
	// IMPORTANT: first we need to initialize GLib
	bool bSuccess = Monsterchase::InitializeGLib(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
	if (Monsterchase::Initialize()) {
		Monsterchase::game(bSuccess);
	}
	
	

#if defined _DEBUG

	_CrtDumpMemoryLeaks();

#endif // _DEBUG
	return 0;

}




























////#include <assert.h>
////#include <stdio.h>
////#include <stdint.h>
////#include <Windows.h>
////#include "MemorySystem.h"
////#if defined _DEBUG
////#define _CRTDBG_MAP_ALLOC
////#include <crtdbg.h>
////#endif // _DEBUG
////
////#include "GLib.h"
////
////void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
////GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);
////
////void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
////{
////#ifdef _DEBUG
////	const size_t	lenBuffer = 65;
////	char			Buffer[lenBuffer];
////
////	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
////	OutputDebugStringA(Buffer);
////#endif // __DEBUG
////}
////
////int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
////{
////	const size_t 		sizeHeap = 1024 * 1024;
////
////	// you may not need this if you don't use a descriptor pool
////	const unsigned int 	numDescriptors = 2048;
////
////	// Allocate memory for my test heap.
////	void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
////	assert(pHeapMemory);
////
////	// Create your HeapManager and FixedSizeAllocators.
////	InitializeMemorySystem(pHeapMemory, sizeHeap, numDescriptors);
////	// IMPORTANT: first we need to initialize GLib
////	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
////
////	if (bSuccess)
////	{
////		// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
////		GLib::SetKeyStateChangeCallback(TestKeyCallback);
////
////		// Create a couple of sprites using our own helper routine CreateSprite
////		GLib::Sprites::Sprite * pGoodGuy = CreateSprite("data\\GoodGuy.dds");
////		GLib::Sprites::Sprite * pBadGuy = CreateSprite("data\\BadGuy.dds");
////
////		bool bQuit = false;
////
////		do
////		{
////			// IMPORTANT: We need to let GLib do it's thing. 
////			GLib::Service(bQuit);
////
////			if (!bQuit)
////			{
////				// IMPORTANT: Tell GLib that we want to start rendering
////				GLib::BeginRendering();
////				// Tell GLib that we want to render some sprites
////				GLib::Sprites::BeginRendering();
////
////				if (pGoodGuy)
////				{
////					static float			moveDist = .01f;
////					static float			moveDir = moveDist;
////
////					static GLib::Point2D	Offset = { -180.0f, -100.0f };
////
////					if (Offset.x < -220.0f)
////						moveDir = moveDist;
////					else if (Offset.x > -140.0f)
////						moveDir = -moveDist;
////
////					Offset.x += moveDir;
////
////					// Tell GLib to render this sprite at our calculated location
////					GLib::Sprites::RenderSprite(*pGoodGuy, Offset, 0.0f);
////				}
////				if (pBadGuy)
////				{
////					static float			moveDist = .02f;
////					static float			moveDir = -moveDist;
////
////					static GLib::Point2D	Offset = { 180.0f, -100.0f };
////
////					if (Offset.x > 200.0f)
////						moveDir = -moveDist;
////					else if (Offset.x < 160.0f)
////						moveDir = moveDist;
////
////					Offset.x += moveDir;
////
////					// Tell GLib to render this sprite at our calculated location
////					GLib::Sprites::RenderSprite(*pBadGuy, Offset, 0.0f);
////				}
////
////				// Tell GLib we're done rendering sprites
////				GLib::Sprites::EndRendering();
////				// IMPORTANT: Tell GLib we're done rendering
////				GLib::EndRendering();
////			}
////		} while (bQuit == false);
////
////		if (pGoodGuy)
////			GLib::Sprites::Release(pGoodGuy);
////		if (pBadGuy)
////			GLib::Sprites::Release(pBadGuy);
////
////		// IMPORTANT:  Tell GLib to shutdown, releasing resources.
////		GLib::Shutdown();
////	}
////
////#if defined _DEBUG
////	_CrtDumpMemoryLeaks();
////#endif // _DEBUG
////
////}
////
////GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename)
////{
////	assert(i_pFilename);
////
////	size_t sizeTextureFile = 0;
////
////	// Load the source file (texture data)
////	void * pTextureFile = LoadFile(i_pFilename, sizeTextureFile);
////
////	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
////	GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;
////
////	// exit if something didn't work
////	// probably need some debug logging in here!!!!
////	if (pTextureFile)
////		delete[] pTextureFile;
////
////	if (pTexture == nullptr)
////		return NULL;
////
////	unsigned int width = 0;
////	unsigned int height = 0;
////	unsigned int depth = 0;
////
////	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
////	bool result = GLib::GetDimensions(pTexture, width, height, depth);
////	assert(result == true);
////	assert((width > 0) && (height > 0));
////
////	// Define the sprite edges
////	GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
////	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
////	GLib::RGBA							Color = { 255, 255, 255, 255 };
////
////	// Create the sprite
////	GLib::Sprites::Sprite * pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
////	if (pSprite == nullptr)
////	{
////		GLib::Release(pTexture);
////		return nullptr;
////	}
////
////	// Bind the texture to sprite
////	GLib::Sprites::SetTexture(*pSprite, *pTexture);
////
////	return pSprite;
////}
////
////void * LoadFile(const char * i_pFilename, size_t & o_sizeFile)
////{
////	assert(i_pFilename != NULL);
////
////	FILE * pFile = NULL;
////
////	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
////	if (fopenError != 0)
////		return NULL;
////
////	assert(pFile != NULL);
////
////	int FileIOError = fseek(pFile, 0, SEEK_END);
////	assert(FileIOError == 0);
////
////	long FileSize = ftell(pFile);
////	assert(FileSize >= 0);
////
////	FileIOError = fseek(pFile, 0, SEEK_SET);
////	assert(FileIOError == 0);
////
////	uint8_t * pBuffer = new uint8_t[FileSize];
////	assert(pBuffer);
////
////	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
////	assert(FileRead == FileSize);
////
////	fclose(pFile);
////
////	o_sizeFile = FileSize;
////
////	return pBuffer;
////}
//
//
////#include<stdio.h>
////#include<iostream>
////#include<string>
////#include<conio.h>
////#include "Monster.h"
////#include "Player.h"
////#include "Nomad.h"
////#include "MonsterList.h"
//
//
////using namespace std;
////
////void getInput();
////void printVillains();
////void moveVillains();
////
////void destroyMonster();
////void addNewMonster();
////
////int numOfMonsters;
////
////MonsterList * monsterList;
////Player * player;
////GameObject2D * G1; 
////
////
////int main()
////{
////	/*HeapManagerUnitTest();
////	cout << "Press any key to exit" << endl;
////	getchar();*/
////	monsterList = new MonsterList();
////	int counter = 0;
////	
////	char * inputString = new char[128];
////	{
////		getInput();
////
////		cout << "Enter name for a nomad (He just wanders aimlessly) : " ;
////		cin >> inputString;
////		GameObject2D * G2 = new GameObject2D(10, 10);
////		Nomad * nomad = new Nomad(inputString, G2);
////		
////		cout << "Enter the name of the player : " ;
////		cin >> inputString;
////		//create a gameobject assign it to player controller for now.. This way when a monster bites the player we can just delete the player controller class and use the same gameobject to create a new monster class.
////		G1 = new GameObject2D(0,0);
////		
////		player = new Player(inputString, G1);
////		
////
////
////		player->printInfo();
////		printVillains();
////		while (1)
////		{
////
////			int asciiValue;
////			char inputDirection;
////			cout << "press W,A,S and D to move the player in UP,LEFT,DOWN and RIGHT directions respectively----press q to exit\n";
////
////			inputDirection = _getch();
////			
////			asciiValue = inputDirection;
////			if (asciiValue == 113)
////				break;
////			else
////				player->Move(inputDirection);
////
////			player->printInfo();
////			nomad->Move();
////			nomad->printInfo();
////			moveVillains();
////			printVillains();
////			counter++;
////			if (counter % 20 == 0)
////			{
////				int choice = rand() % 2;
////				if (choice == 0)
////					destroyMonster();
////				else
////					addNewMonster();
////			}
////		}
////
////		delete [] inputString;
////		delete monsterList;
////		delete player;
////		delete G1;
////		delete G2;
////		delete nomad;
////	}
////
////#if defined(_DEBUG)
////	_CrtDumpMemoryLeaks();
////#endif
////	return 0;
////}
////
////void getInput()
////{
////	
////	char * monsterName = new char[128];
////	
////	cout << "Enter the number of monsters to begin with : ";
////	cin >> numOfMonsters;
////	while (cin.fail())
////	{
////		cout << "Is that a number? try again \n";
////		cin.clear();
////		cin.ignore(256, '\n');
////		cin >> numOfMonsters;
////	}
////	cin.ignore();
////	
////	for (int i = 0; i < numOfMonsters; i++)
////	{
////		
////		cout << "Enter the name of the monster: ";
////		cin >> monsterName;
////		float xpos = static_cast<float>((rand() % 50));
////		float ypos = static_cast<float>((rand() % 50));
////		GameObject2D * newMonster = new GameObject2D(Point2D(xpos, ypos));
////		
////		monsterList->addMonster(monsterName , newMonster);
////		
////	}
////	delete [] monsterName;
////}
////
////void printVillains()
////{
////	monsterList->printAllMonstersInfo();
////}
////
////void moveVillains()
////{
////	Point2D playerPosition = player->getPosition();
////	monsterList->setFocusForMonsters(playerPosition);
////	monsterList->moveAllMonsters();
////
////}
////
////
////
////void destroyMonster()
////{
////	monsterList->deleteMonster();
////	
////}
////
////void addNewMonster()
////{
////	char * monsterName = new char[128];
////	cout << "Enter the name of the new monster: ";
////	cin >> monsterName;
////	float xpos = static_cast<float>((rand() % 50));
////	float ypos = static_cast<float>((rand() % 50));
////	GameObject2D * newMonster = new GameObject2D(Point2D(xpos, ypos));
////	
////	monsterList->addMonster(monsterName, newMonster);
////	delete[] monsterName;
////}
////
//
//
//////Game code
//////#include "MonsterChase.h"
//////using namespace std;
//////using namespace HeapManagerProxy;
//////int main()
//////{
//////	MonsterChase monsterChaseGame;
//////	monsterChaseGame.game();
//////	return 0;
//////}
//////
//////
//////
//////	void  MonsterChase::game()
//////	{
//const size_t 		sizeHeap = 1024 * 1024;
//
//// you may not need this if you don't use a descriptor pool
//const unsigned int 	numDescriptors = 2048;
//
//// Allocate memory for my test heap.
//void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
//assert(pHeapMemory);
//
//// Create your HeapManager and FixedSizeAllocators.
//InitializeMemorySystem(pHeapMemory, sizeHeap, numDescriptors);
//// IMPORTANT: first we need to initialize GLib
//bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
//if (bSuccess)
//{
//	// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
//	GLib::SetKeyStateChangeCallback(TestKeyCallback);
//
//	// Create a couple of sprites using our own helper routine CreateSprite
//	GLib::Sprites::Sprite * pGoodGuy = CreateSprite("data\\GoodGuy.dds");
//	GLib::Sprites::Sprite * pBadGuy = CreateSprite("data\\BadGuy.dds");
//
//	bool bQuit = false;
//
//	do
//	{
//		// IMPORTANT: We need to let GLib do it's thing. 
//		GLib::Service(bQuit);
//
//		if (!bQuit)
//		{
//			// IMPORTANT: Tell GLib that we want to start rendering
//			GLib::BeginRendering();
//			// Tell GLib that we want to render some sprites
//			GLib::Sprites::BeginRendering();
//
//			if (pGoodGuy)
//			{
//				static float			moveDist = .01f;
//				static float			moveDir = moveDist;
//
//				static GLib::Point2D	Offset = { -180.0f, -100.0f };
//
//				if (Offset.x < -220.0f)
//					moveDir = moveDist;
//				else if (Offset.x > -140.0f)
//					moveDir = -moveDist;
//
//				Offset.x += moveDir;
//
//				// Tell GLib to render this sprite at our calculated location
//				GLib::Sprites::RenderSprite(*pGoodGuy, Offset, 0.0f);
//			}
//			if (pBadGuy)
//			{
//				static float			moveDist = .02f;
//				static float			moveDir = -moveDist;
//
//				static GLib::Point2D	Offset = { 180.0f, -100.0f };
//
//				if (Offset.x > 200.0f)
//					moveDir = -moveDist;
//				else if (Offset.x < 160.0f)
//					moveDir = moveDist;
//
//				Offset.x += moveDir;
//
//				// Tell GLib to render this sprite at our calculated location
//				GLib::Sprites::RenderSprite(*pBadGuy, Offset, 0.0f);
//			}
//
//			// Tell GLib we're done rendering sprites
//			GLib::Sprites::EndRendering();
//			// IMPORTANT: Tell GLib we're done rendering
//			GLib::EndRendering();
//		}
//	} while (bQuit == false);
//
//	if (pGoodGuy)
//		GLib::Sprites::Release(pGoodGuy);
//	if (pBadGuy)
//		GLib::Sprites::Release(pBadGuy);
//
//	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
//	GLib::Shutdown();
//}
//
//
//		
//
//			while (1)
//			{
//
//				int asciiValue;
//				char inputDirection;
//				cout << "press W,A,S and D to move the player in UP,LEFT,DOWN and RIGHT directions respectively----press q to exit\n";
//
//				inputDirection = _getch();
//
//				asciiValue = inputDirection;
//				if (asciiValue == 113)
//					break;
//				else
//					player->Move(inputDirection);
//
//				player->printInfo();
//				nomad->Move();
//				nomad->printInfo();
//				moveVillains();
//				printVillains();
//				counter++;
//				if (counter % 20 == 0)
//				{
//					int choice = rand() % 2;
//					if (choice == 0)
//						destroyMonster();
//					else
//						addNewMonster();
//				}
//			}
//
//			
//		}
//////
//////#if defined(_DEBUG)
//////		_CrtDumpMemoryLeaks();
//////#endif
//////		
//////	}
//////
//////	void  MonsterChase::getInput()
//////	{
//////
//////		char * monsterName = new char[128];
//////
//////		cout << "Enter the number of monsters to begin with : ";
//////		cin >> numOfMonsters;
//////		while (cin.fail())
//////		{
//////			cout << "Is that a number? try again \n";
//////			cin.clear();
//////			cin.ignore(256, '\n');
//////			cin >> numOfMonsters;
//////		}
//////		cin.ignore();
//////
//////		for (int i = 0; i < numOfMonsters; i++)
//////		{
//////
//////			cout << "Enter the name of the monster: ";
//////			cin >> monsterName;
//////			float xpos = static_cast<float>((rand() % 50));
//////			float ypos = static_cast<float>((rand() % 50));
//////			GameObject2D * newMonster = new GameObject2D(Point2D(xpos, ypos));
//////
//////			monsterList->addMonster(monsterName, newMonster);
//////
//////		}
//////		delete[] monsterName;
//////	}
//////
//////	void  MonsterChase::printVillains()
//////	{
//////		monsterList->printAllMonstersInfo();
//////	}
//////
//////	void  MonsterChase::moveVillains()
//////	{
//////		Point2D playerPosition = player->getPosition();
//////		monsterList->setFocusForMonsters(playerPosition);
//////		monsterList->moveAllMonsters();
//////
//////	}
//////
//////
//////
//////	void  MonsterChase::destroyMonster()
//////	{
//////		monsterList->deleteMonster();
//////
//////	}
//////
//////	void  MonsterChase::addNewMonster()
//////	{
//////		char * monsterName = new char[128];
//////		cout << "Enter the name of the new monster: ";
//////		cin >> monsterName;
//////		float xpos = static_cast<float>((rand() % 50));
//////		float ypos = static_cast<float>((rand() % 50));
//////		GameObject2D * newMonster = new GameObject2D(Point2D(xpos, ypos));
//////
//////		monsterList->addMonster(monsterName, newMonster);
//////		delete[] monsterName;
//////	}
//////
//
