#pragma once
#include "SmartPointer.h"
#include "GameObject2D.h"
namespace Engine {
	static SmartPointer<GameObject2D> * pPlayerPlatform;
	static SmartPointer<GameObject2D> * pBall;
	static SmartPointer<GameObject2D> * pEndCollider;
	bool Init();
	void CopyFilesToDestination();
	void CreateBorders();
	void CreateBlocks();
	void CreateScreenSprites();
	void InitTimer();
	void Run();
	void Game(bool bSuccess);
	bool QuitCallback();
	void Cleanup();
	void CheckInput();
	void GameOver();
	void CheckForGameWin();
	SmartPointer<GameObject2D> * CreateGameObject(const char * i_pFileName);
	SmartPointer<GameObject2D> * CreateGameObjectAtPosition( const char * i_pFileName, const char * ip_Name, Point2D i_Pos, float i_Rot);
	void KillBlock(SmartPointer<GameObject2D> * i_KillableGO);

}