#pragma once
#include "GameObject2D.h"
class IGameObject2DController
{
public:
	virtual void setupGameObject(SmartPointer<GameObject2D> i_pGameObject) = 0;
	virtual void updateGameObject() = 0;
	

};