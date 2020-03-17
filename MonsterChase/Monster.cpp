#include "Monster.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Engine/ConsolePrint.h"

using namespace std;
using namespace Engine;



Monster:: Monster()
{
	
	next = nullptr;
	m_GameObject = nullptr;
}

Monster::Monster(const SmartPointer<GameObject2D> & ip_Object)
{
	
	m_GameObject = SmartPointer<GameObject2D>(ip_Object);
	

	this->next = nullptr;

}
void Monster:: move() {

	updateGameObject();

}

void Monster::printInfo()
{
	Point2D printPosition = m_GameObject->GetPosition();
	//cout << "Monster name : " << this->m_GameObject->m_Name << " is at position " << printPosition.x() << "," << printPosition.y()<<endl;

}

void Monster::updateGameObject()
{
	Point2D movementDirection;
	
		movementDirection = getMovementTowards(m_focus);
	
	Point2D newPosition = m_GameObject->GetPosition();
	newPosition += movementDirection;
	m_GameObject->SetPosition(newPosition);
}

void Monster::setupGameObject(SmartPointer<GameObject2D> ip_Object)
{
	m_GameObject = ip_Object;
}

Point2D Monster::getMovementTowards(Point2D  focusDirection)
{
	Point2D returnMovement;
	returnMovement = focusDirection;
	returnMovement -= m_GameObject->GetPosition();
	returnMovement.Normalize();

	return returnMovement;
}

Monster ::~Monster()
{
	Point2D printPosition = m_GameObject->GetPosition();
	//DEBUG_PRINT("Deleting Monster name %s at position %f,%f", this->m_GameObject->m_Name, printPosition.x(), printPosition.y());

	
	
}

	

