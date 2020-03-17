#include "Player.h"
#include <assert.h>
#include "Engine/ConsolePrint.h"
#include <iostream>
#include "Engine/InputSystem.h"

using namespace Engine;
using namespace std;

	Player::Player() {
		
		m_GameObject = nullptr;
	}
	Player::Player(const SmartPointer<GameObject2D> & ip_Object) {
		
		m_GameObject = SmartPointer<GameObject2D>(ip_Object);
		//setupGameObject(ip_Object);
		//playerSprite = RenderSystem::CreateSprite("data\\GoodGuy.dds");
		

	}
	/*void Player::Move(char option,float i_dt) {
		Point2D movement;
		switch (option)
		{
		case 'a':
		case 'A':
			UpdateForce(Point2D(-2, 0), i_dt);

			break;
		case 'd':
		case 'D':
			UpdateForce(Point2D(2, 0), i_dt);
			break;
		case 'w':
		case 'W':
			UpdateForce(Point2D(0, 2), i_dt);
			break;
		case 's':
		case 'S':
			UpdateForce(Point2D(0,-2), i_dt);
			break;
		
		default:
			break;
			
		}

		movementDirection = movement;
		updateGameObject();

	}*/
	void Player::printInfo() {
		Point2D printPosition = m_GameObject->GetPosition();
		cout << "Player name : " << this->m_GameObject << " is at position " << printPosition.x() <<","<<printPosition.y()<< endl;


	}
	

	void Player::updateGameObject()
	{
		if (m_GameObject) 
		{
			Point2D newPosition = m_GameObject->GetPosition();
			newPosition += movementDirection;
			m_GameObject->SetPosition(newPosition);

		}
	}

	void Player::setupGameObject(SmartPointer<GameObject2D> ip_Object)
	{
		
	}

	//void Player::RenderSprite()
	//{
	//	if (playerSprite) {
	//		

	//		 GLib::Point2D	Offset = {getPosition().x(),getPosition().y()};

	//		
	//		// Tell GLib to render this sprite at our calculated location
	//		GLib::Sprites::RenderSprite(*playerSprite, Offset, 0.0f);
	//	}
	//}

	//void Player::ReleaseSprite()
	//{
	//	if (playerSprite) {
	//		GLib::Sprites::Release(playerSprite);
	//	}
	//}
	//void Player::UpdateForce(Point2D newValue,float i_dt) {
	//	playerPhysics->force = newValue;
	//	Point2D acceleration = newValue / playerPhysics->mass;
	//	Point2D velocity = playerPhysics->velocity + acceleration * i_dt;
	//	//playerPhysics->force = newValue;
	//	playerPhysics->velocity = velocity;
	//	DEBUG_PRINT("Force is %f, %f", playerPhysics->force.x(), playerPhysics->force.y());
	//}

	/*void Player::UpdatePhysics(float i_dt)
	{
		
		Point2D newPosition = (playerPhysics->physicsObject->GetPosition()) + (playerPhysics->velocity * i_dt);
		playerPhysics->prevPosition = playerPhysics->physicsObject->GetPosition();
		
		playerPhysics->physicsObject->SetPosition(newPosition);
	}
*/
	void Player::ApplyDrag(float i_dt)
	{
		/*float forceX = 0, forceY = 0;
		float calculatedForceX = playerPhysics->force.x(), calculatedForceY = playerPhysics->force.y();
		if (calculatedForceX == 0) {
			forceX = 0;
		}
		else if (calculatedForceX < 0.1 && calculatedForceX > -0.1) {
			forceX = -calculatedForceX;
		}
		else if (calculatedForceX > 0.1) {
			forceX = -0.1;
		}
		else if (calculatedForceX < -0.1) {
			forceX = 0.1;
		}
		if (calculatedForceY == 0) {
			forceY = 0;
		}
		else if (calculatedForceY < 0.1 && calculatedForceY > -0.1) {
			forceY = -calculatedForceY;
		}
		else if (calculatedForceY > 0.1) {
			forceY = -0.1;
		}
		else if (calculatedForceY < -0.1) {
			forceY = 0.1;
		}*/
		//UpdateForce(Point2D(forceX, forceY),i_dt
		/*Point2D zero = Point2D(0, 0);
		Point2D drag = Point2D(0, 0);
		float vel_X = playerPhysics->velocity.x();
		float vel_Y = playerPhysics->velocity.y();
		if (!(playerPhysics->velocity == zero)) {
			if (vel_X) {
				drag = drag + ((vel_X > 0) ? Point2D(-3.0f, 0) : Point2D(3.0f, 0));
			}
			if (vel_Y) {
				drag = drag + ((vel_Y > 0) ? Point2D(0, -3.0f) : Point2D(0, 3.0f));
			}
			drag = drag / playerPhysics->mass;
			Point2D velocity = playerPhysics->velocity + (drag * i_dt);
			playerPhysics->velocity = velocity;
			DEBUG_PRINT("Applying drag");
		}*/
		
	}

	void Player::CheckInput(float i_dt)
	{
		/*if (i_VKeyID == 0x0057 and !bWentDown) {
			player->Move('w');
			DEBUG_PRINT("Pressed W");
		}
		if (i_VKeyID == 0x0041 and !bWentDown) {
			player->Move('a');
			DEBUG_PRINT("Pressed a");
		}
		if (i_VKeyID == 0x0053 and !bWentDown) {
			player->Move('s')
			DEBUG_PRINT("Pressed s");
		}
		if (i_VKeyID == 0x0044 and !bWentDown) {
			player->Move('d');
			DEBUG_PRINT("Pressed d");
		}*/
		/*if(InputSystem::CheckIfKeyDown((int)'W') ){
			DEBUG_PRINT("Pressed W");
			UpdateForce(Point2D(0,3.0f), i_dt);
		}
		else if (InputSystem::CheckIfKeyDown((int)'S')) {
			DEBUG_PRINT("Pressed S");
			UpdateForce(Point2D(0, -3.0f), i_dt);
		}
		else if (InputSystem::CheckIfKeyDown((int)'A')) {
			DEBUG_PRINT("Pressed A");
			UpdateForce(Point2D(-3.0f,0), i_dt);
		}
		else if (InputSystem::CheckIfKeyDown((int)'D')) {
			DEBUG_PRINT("Pressed D");
			UpdateForce(Point2D(3.0f, 0), i_dt);
		}
		else {
			ApplyDrag(i_dt);
		}*/

	}

	 

	Player::~Player() {

		//delete m_GameObject;
		//delete playerPhysics;

	}

	
	
	


