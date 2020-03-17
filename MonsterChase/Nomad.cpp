#include "Nomad.h"
#include <string.h>
#include <assert.h>
#include <cstdlib>
#include <iostream>
using namespace std;


Nomad::Nomad()
{
	
	m_GameObject = nullptr;
}

Nomad::Nomad(const SmartPointer<GameObject2D> & ip_Object)
{
	
	m_GameObject = SmartPointer<GameObject2D>(ip_Object);
	//nomadSprite = RenderSystem::CreateSprite("data\\BadGuy.dds");
}

void Nomad::Move()
{
	updateGameObject();
}

void Nomad::printInfo()
{
	Point2D printPosition = m_GameObject->GetPosition();
	//cout << "Nomad name : " << this->m_GameObject->m_Name << " is at position " << printPosition.x() << "," << printPosition.y() << endl;

}

Nomad::~Nomad()
{
	
	//delete m_GameObject;
}

void Nomad::updateGameObject()
{
	float x =static_cast<float>( rand() % 11 + (-5));
	float y = static_cast<float>(rand() % 11 + (-5));
	Point2D newPosition = m_GameObject->GetPosition();
	newPosition += Point2D(x,y);
	m_GameObject->SetPosition(newPosition);

}

void Nomad::setupGameObject(SmartPointer<GameObject2D> ip_Object)
{
	m_GameObject = ip_Object;
}

void Nomad::RenderSprite()
{
	static float			moveDist = .02f;
	static float			moveDir = -moveDist;

	static GLib::Point2D	Offset = { 180.0f, -100.0f };

	/*if (Offset.x > 200.0f)
		moveDir = -moveDist;
	else if (Offset.x < 160.0f)
		moveDir = moveDist;*/

	Point2D engineOffset = getPosition();
	//Offset.x = engineOffset.x();
	//Offset.y = engineOffset.y();

	// Tell GLib to render this sprite at our calculated location
	GLib::Sprites::RenderSprite(*nomadSprite, Offset, 0.0f);
}

void Nomad::ReleaseSprite()
{
	if (nomadSprite) {
		GLib::Sprites::Release(nomadSprite);
	}
}
