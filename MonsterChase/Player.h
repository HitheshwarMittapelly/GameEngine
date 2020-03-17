#pragma once

#include "Engine/IGameObject2DController.h"
#include "Engine/GameObject2D.h"
#include "Engine/SmartPointer.h"
#include "GLib/GLib.h"


	class Player : public IGameObject2DController
	{
	public:
		Player();
		
		
		Player(const SmartPointer<GameObject2D> & ip_Object);
		void Move(char option,float i_dt);
		void printInfo();
		~Player();
		
		Point2D getPosition() {
			
			return m_GameObject->GetPosition();;
		}
		void updateGameObject() override;
		void setupGameObject(SmartPointer<GameObject2D> ip_Object) override;
		void UpdateForce(Point2D newValue,float i_dt);
		void UpdatePhysics(float i_dt);
		void ApplyDrag(float i_dt);
		void CheckInput(float i_dt);
		void RenderSprite();
		void ReleaseSprite();
		//GLib::KeyStateChange TestKeyCallback;
	private:
		
		Point2D movementDirection;
		SmartPointer<GameObject2D>  m_GameObject;
		GLib::Sprites::Sprite * playerSprite;
		//PhysicsInfo * playerPhysics;

		
	};


