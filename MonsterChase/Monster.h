#pragma once
#include "Engine/Point2D.h"
#include "Engine/GameObject2D.h"
#include "Engine/SmartPointer.h"
#include "Engine/IGameObject2DController.h"
using namespace Engine;
class Monster : IGameObject2DController
{
	public:
		Monster();
		Monster(const SmartPointer<GameObject2D> & ip_Object);
		void move();
		void printInfo();
		void updateGameObject() override;
		void setupGameObject(SmartPointer<GameObject2D>) override;
		void setFocus(Point2D ipFocus) 
		{
			m_focus = ipFocus;
		}

		Point2D getMovementTowards(Point2D focusDirection);
		~Monster();

		
		Monster * next;
	private:
	
	
		Point2D  m_focus;
		SmartPointer<GameObject2D> m_GameObject;
		
};


