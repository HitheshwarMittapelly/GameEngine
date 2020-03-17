#pragma once
#include "Engine/IGameObject2DController.h"
#include "Engine/GameObject2D.h"
#include "Engine/SmartPointer.h"
#include "GLib/GLib.h"

class Nomad : IGameObject2DController
{
public:
	Nomad();


	Nomad(const SmartPointer<GameObject2D> & ip_Object);
	void Move();
	void printInfo();
	Point2D getPosition() {

		return m_GameObject->GetPosition();;
	}
	~Nomad();
	
	void updateGameObject() override;
	void setupGameObject(SmartPointer<GameObject2D> ip_Object) override;
	void RenderSprite();
	void ReleaseSprite();

private:
	
	
	SmartPointer<GameObject2D> m_GameObject;
	GLib::Sprites::Sprite * nomadSprite;
};
