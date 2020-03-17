#include "PhysicsSystem.h"
#include "Engine.h"
#include <cmath>
#include <iostream>
using namespace Math;
#define PI 3.14159265
#define	Deg2Rad ( PI / 180.0 )	
static std::vector<PhysicsSystem::PhysicsInfo *> AllPhysicsObjects;
namespace PhysicsSystem {
	
	void PhysicsSystem::Run(float i_dt) {
		//calculate the velocity of all objects
		CalculateVelocity(i_dt);
		//Compute and resolve collisions
		ComputeCollisions(i_dt);

		//Set the positions of the objects
		for (size_t i = 0; i < AllPhysicsObjects.size(); i++) {
			
			auto physicsObj = AllPhysicsObjects.at(i);

			if (physicsObj->needsUpdate) {
				if (physicsObj->m_GameObject.AquireOwnership() != nullptr) {
					SmartPointer<GameObject2D> tempSmartObj = physicsObj->m_GameObject.AquireOwnership();
					Point2D newPosition = (physicsObj->currentPosition) + (((physicsObj->velocity + physicsObj->prevVelocity)*0.5)* i_dt);
					//If it is player platform lock the position to the borders
					if (physicsObj == AllPhysicsObjects.at(1)) {
						float newX = newPosition.x(), newY = newPosition.y();
						if (newPosition.x() >= 330) {
							newX = 330;
						}
						else if (newPosition.x() <= -330) {
							newX = -330;
						}
						newPosition = Point2D(newX, newY);
					}
					
					physicsObj->prevPosition = physicsObj->currentPosition;

					physicsObj->currentPosition = newPosition;
					

					tempSmartObj->SetPosition(newPosition);
				}
				else {
					//This object needs no further update
					physicsObj->m_GameObject.ReleaseReference();
					physicsObj->needsUpdate = false;;
					
				}
			}
			
		}
	}
	void PhysicsSystem::AddVelocity(Point2D i_Velocity) {

		AllPhysicsObjects.at(0)->velocity = i_Velocity;
		AllPhysicsObjects.at(0)->prevVelocity = i_Velocity;


	}

	float PhysicsSystem::RandInRange(float a, float b)
	{
		float returnVal = ((b - a) * ((float)rand() / RAND_MAX)) + a;
		
		return returnVal;

	}

	Point2D PhysicsSystem::GenerateRandomVector(Point2D min, Point2D max) {
		return Point2D(RandInRange(min.x(), max.x()), RandInRange(min.y(), max.y()));
	}

	void PhysicsSystem::CalculateVelocity(float i_dt) {
		

		for (auto physicsObj : AllPhysicsObjects) {
			//We need to apply drag for every other object except the ball
			if (physicsObj != AllPhysicsObjects.at(0)) {
				Point2D currentFrameForce = physicsObj->force;
				Point2D dragForce = physicsObj->velocity * -coeffOfFriction;
				currentFrameForce += dragForce;
				
				Point2D acceleration = currentFrameForce / physicsObj->mass;
				Point2D velocity = physicsObj->velocity + (acceleration * i_dt);
				
				physicsObj->prevVelocity = physicsObj->velocity;

				physicsObj->velocity = (velocity);

				float minVelocity = 0.2f;

				float velocityX = physicsObj->velocity.x(), velocityY = physicsObj->velocity.y();
				if (physicsObj->force.x() < 0.25 && physicsObj->force.x() > -0.25) {
					physicsObj->force.SetXY(0, physicsObj->force.y());
					if (velocityX < minVelocity && velocityX > -minVelocity) {
						velocityX = 0;
					}
					physicsObj->velocity = Point2D(velocityX, velocityY);


				}
				
			}
			
		}
	}





	void PhysicsSystem::ComputeCollisions(float i_dt)
	{
		//Check For  Collision Between Objects
		for (unsigned i = 1; i < AllPhysicsObjects.size(); i++) {
			if (AllPhysicsObjects.at(i)->needsUpdate) {
				CheckForCollisionBetweenObjects(*AllPhysicsObjects.at(0), *AllPhysicsObjects.at(i), i_dt);
				
			}
		}
	}

	bool PhysicsSystem::CheckForCollisionBetweenObjects(PhysicsSystem::PhysicsInfo & m_A, PhysicsSystem::PhysicsInfo & m_B, float i_dt) {
		//Values that help in determining when to stop
		m_A.collidedInThisFrame = false;
		m_B.collidedInThisFrame = false;
		//When the collision occurs in this frame. Set to negative 100 (which means didn't happen in this frame yet)
		m_A.collisionTime = -100;
		m_B.collisionTime = -100;
		//A in B's system
		CollisionCheckInDestinationCoordinateSystem(m_A, m_B, i_dt);
		
		if (m_A.collidedInThisFrame && m_B.collidedInThisFrame)
			return true;
		else
			return false;

	}



	void PhysicsSystem::CollisionCheckInDestinationCoordinateSystem(PhysicsSystem::PhysicsInfo & m_A, PhysicsSystem::PhysicsInfo & m_B, float i_dt)
	{
		//Get the necessary matrices
		Matrix_4x4 mATrans = Matrix_4x4::CreateTranslation(Vector3d(m_A.currentPosition));
		Matrix_4x4 mARot = Matrix_4x4::CreateZRotation(m_A.zRotation );

		Matrix_4x4 mBTrans = Matrix_4x4::CreateTranslation(Vector3d(m_B.currentPosition));
		Matrix_4x4 mBRot = Matrix_4x4::CreateZRotation(m_B.zRotation );

		Matrix_4x4 mAToWorld;
		mATrans.MultiplySSE(mARot, mAToWorld);

		Matrix_4x4 mBToWorld ;
		mBTrans.MultiplySSE(mBRot, mBToWorld);

		Matrix_4x4 mWorldToA ;
		Matrix_4x4 mWorldToB ;
		mAToWorld.InverseSSE(mWorldToA);
		mBToWorld.InverseSSE(mWorldToB);

		
		Matrix_4x4 mAToB ;
		Matrix_4x4 mBToA ;
		mWorldToB.MultiplySSE(mAToWorld, mAToB);
		mWorldToA.MultiplySSE(mBToWorld, mBToA);
		
		 // A in B's Coordinate - System
		Vector4d mBCenterInB = mBToWorld * Vector4d((Vector3d(m_B.m_BB.m_center)), 1);
		Vector4d mACenterInB = mAToB * Vector4d(Vector3d(m_A.m_BB.m_center), 1.0f);
		Vector3d mAVelRelToB = Vector3d(m_A.velocity) - Vector3d(m_B.velocity);
		Vector4d mAVelInB = mWorldToB * Vector4d(mAVelRelToB, 0.0);

		
		Vector4d AExtentsXInB = mAToB * Vector4d(m_A.m_BB.m_extents.x(), 0, 0, 0);
		Vector4d AExtentsYInB = mAToB * Vector4d(0, m_A.m_BB.m_extents.y(), 0, 0);

		bool checkForYAxisCollision = true;

		//Axis checks
		//X-Axis Check

		float 	AProjectionOntoB_x = fabs(AExtentsXInB.x()) + fabs(AExtentsYInB.x());
		float BExtentsXAfterAddingA = m_B.m_BB.m_extents.x() + AProjectionOntoB_x;

		float BLeftEdgeX = m_B.m_BB.m_center.x() - BExtentsXAfterAddingA;
		float BRightEdgeX = m_B.m_BB.m_center.x() + BExtentsXAfterAddingA;
		float DCloseX = BLeftEdgeX - mACenterInB.x();
		float DOpenX = BRightEdgeX - mACenterInB.x();
		float tOpenX, tCloseX;
		bool isXSeperated = !(mACenterInB.x() > BLeftEdgeX && mACenterInB.x() < BRightEdgeX);

		//If the velocity is zero for the whole frame then no collision
		if (mAVelInB.x() == 0) {
			if (isXSeperated) {
				//No collision so move on
				checkForYAxisCollision = false;
				return;
			}
			else {
				checkForYAxisCollision = true;
			}
		}
		//There is velocity -- check for tclose and topen
		else {
			tOpenX = DOpenX / mAVelInB.x();
			tCloseX = DCloseX / mAVelInB.x();
			//Between the edges there is no seperation
			if (!isXSeperated) {
				if (tCloseX < 0 && tOpenX > 0) {
					
					checkForYAxisCollision = true;
				}
			}
			//Moving in reverse direction than what we thought
			if (tCloseX > tOpenX) {
				//swap topen and tclose
				float temp = tCloseX;
				tCloseX = tOpenX;
				tOpenX = temp;
			}
			//tclose greater than this frame's time - seperation exists for the entire frame so no colision
			if (tCloseX > i_dt) {
				//No collision

				checkForYAxisCollision = false;

				return;
			}
			else {
				//Check in y axis to determine if all separations were closed before any new separations opened.

				checkForYAxisCollision = true;
			}
			//if opening is done in past then we are moving away, so no collision again
			if (tOpenX < 0) {
				//No collision

				checkForYAxisCollision = false;
				//DEBUG_PRINT("moving away in x")
				return;
			}

		}

		if (checkForYAxisCollision) {
			//Y-Axis Check
			float 	AProjectionOntoB_y = fabs(AExtentsXInB.y()) + fabs(AExtentsYInB.y());
			float BExtentsYAfterAddingA = m_B.m_BB.m_extents.y() + AProjectionOntoB_y;
			bool noCollision = false;
			float BTopEdgeY = m_B.m_BB.m_center.y() + BExtentsYAfterAddingA;
			float BBottomEdgeY = m_B.m_BB.m_center.y() - BExtentsYAfterAddingA;
			bool  isYSeperated = !(mACenterInB.y() > BBottomEdgeY && mACenterInB.y() < BTopEdgeY);
			float DCloseY = BTopEdgeY - mACenterInB.y();
			float DOpenY = BBottomEdgeY - mACenterInB.y();
			float tOpenY, tCloseY;
			if (mAVelInB.y() == 0) {
				if (isYSeperated) {
					//No Collision

					noCollision = true;
					return;
				}
				else {
					if (!isXSeperated && mAVelInB.x() == 0) {
						m_A.collidedInThisFrame = true;
						m_B.collidedInThisFrame = true;
						m_A.collisionTime = 0;
						m_B.collisionTime = 0;
						DEBUG_PRINT("Collision occured in x stationary y stationary");
					}
					if (isXSeperated && mAVelInB.x() != 0) {
						DEBUG_PRINT("Collision occured in x moving y stationary");
						m_A.collidedInThisFrame = true;
						m_B.collidedInThisFrame = true;
						m_A.collisionTime = tCloseX;
						m_B.collisionTime = tCloseX;
						CollisionResolutionUsingMomentumAndReflection(m_A, m_B, tCloseX, 0, i_dt);
						return;
					}

				}
			}
			else {
				if (!noCollision) {
					tOpenY = DOpenY / mAVelInB.y();
					tCloseY = DCloseY / mAVelInB.y();
					//Moving in reverse direction than what we thought
					if (tCloseY > tOpenY) {
						//swap topen and tclose
						float temp = tCloseY;
						tCloseY = tOpenY;
						tOpenY = temp;
					}
					//if opening is done in past then we are moving away, so no collision again
					if (tOpenY < 0) {
						//No collision
						noCollision = true;
						
						return;
					}
					//tclose greater than this frame's time - seperation exists for the entire frame so no colision
					if (tCloseY > i_dt) {
						//No collision
						noCollision = true;
						return;
					}
					//We already know tcloseX, so compare it with tOpenY -- if topenY is less than tcloseX then Y gap opened before x closed so no collision other wise collided
					else {
						if (!noCollision) {
							//No collision occured so far
							if (mAVelInB.x() == 0) {
								//If it is not moving in x then we dont have tCloseX(it is not initialized) so collision occurs no matter what
								m_A.collidedInThisFrame = true;
								m_B.collidedInThisFrame = true;
								m_A.collisionTime = tCloseY;
								m_B.collisionTime = tCloseY;
								DEBUG_PRINT("Collision occured in x stationary y moving");
								CollisionResolutionUsingMomentumAndReflection(m_A, m_B, tCloseY, 1, i_dt);
								return;
								//We know the tCloseY that is when the collision will occur. Move the object forward up until that time and then reverse the direction?
							}
							else {

								//If it is moving in x then check for tclosex time, tclosex happened before an opening occured in Y => which means collision occured at tCloseX
								if (tCloseX > 0) {
									if (tCloseX < tOpenY) {
										m_A.collidedInThisFrame = true;
										m_B.collidedInThisFrame = true;
										m_A.collisionTime = tCloseX;
										m_B.collisionTime = tCloseX;
										DEBUG_PRINT("Collision occured in x moving and y moving");
										CollisionResolutionUsingMomentumAndReflection(m_A, m_B, tCloseX, 0, i_dt);
										return;
										//Same resolution as above
										//conservation of momentum - m1v1 + m2v2 = m1v1'+ m2v2'
									}
								}
								// It is also moving in Y then check if X opened before Y closed
								if (tCloseY < tOpenX) {
									m_A.collidedInThisFrame = true;
									m_B.collidedInThisFrame = true;
									m_A.collisionTime = tCloseY;
									m_B.collisionTime = tCloseY;
									DEBUG_PRINT("Collision occured in x moving and y moving");
									CollisionResolutionUsingMomentumAndReflection(m_A, m_B, tCloseY, 1, i_dt);
									return;
								}
							}
						}


					}

				}


			}

		}


	}

	void PhysicsSystem::CollisionResolutionUsingMomentumAndReflection(PhysicsSystem::PhysicsInfo & m_A, PhysicsSystem::PhysicsInfo & m_B, float i_timeOfCollision, int i_MirrorAxis, float i_dt)
	{
		// If one of them is static we have other means to resolve it
		if (m_A.isStatic || m_B.isStatic) {
			CollisionResolutionUsingMomentumAndReflectionForStaticObjects(m_A, m_B, i_timeOfCollision, i_MirrorAxis, i_dt);
			return;
		}
		
		//Make the A velocity relative to B that way we can use the momentum equations
		float V_XInitial_A = m_A.velocity.x() - m_B.velocity.x();
		float V_YInitial_A = m_A.velocity.y() - m_B.velocity.y();

		float V_XFinal_A;
		float V_YFinal_A;

		float V_XFinal_B;
		float V_YFinal_B;
		float totalMass = m_A.mass + m_B.mass;

		// Momentum equations -- v1f = (m1-m2) *v1i/ m1 + m2  --- v2f = 2m1m2/(m1 + m2)
		//X axis
		V_XFinal_A = ((m_A.mass - m_B.mass) * V_XInitial_A) / (totalMass);

		V_XFinal_B = (2 * m_A.mass * V_XInitial_A) / totalMass;

		//Y axis
		V_YFinal_A = ((m_A.mass - m_B.mass) * V_YInitial_A) / (totalMass);

		V_YFinal_B = (2 * m_A.mass * V_YInitial_A) / totalMass;

		//Add the velocities (which are subtracted for relative velocities)
		V_XFinal_A += m_B.velocity.x();
		V_XFinal_B += m_B.velocity.x();

		V_YFinal_A += m_B.velocity.y();
		V_YFinal_B += m_B.velocity.y();
		//For Object A
		//Set the position to at the time of collision
		Point2D newAPosition = m_A.currentPosition + (((m_A.velocity + m_A.prevVelocity)*0.5)* i_timeOfCollision);
		//Now we have the final velocities. Assuming we are at the collision point - calculate the newPositions based on the new velocities
		m_A.prevVelocity = Point2D(0, 0);
		m_A.velocity = Point2D(V_XFinal_A, V_YFinal_A);
		//calculate newposition based on new velocities
		Point2D finalAPosition = newAPosition + ((m_A.velocity * 0.5) * (i_dt - i_timeOfCollision));
		SmartPointer<GameObject2D> tempSmartObjForA = m_A.m_GameObject.AquireOwnership();
		if (tempSmartObjForA != nullptr) {

			m_A.prevPosition = newAPosition;
			m_A.currentPosition = finalAPosition;

			tempSmartObjForA->SetPosition(finalAPosition);
		}


		//For Object B
		//Set the position to at the time of collision
		Point2D newBPosition = m_B.currentPosition + (((m_B.velocity + m_B.prevVelocity)*0.5)* i_timeOfCollision);
		//Now we have the final velocities. Assuming we are at the collision point - calculate the newPositions based on the new velocities
		m_B.prevVelocity = Point2D(0, 0);
		m_B.velocity = Point2D(V_XFinal_B, V_YFinal_B);
		//calculate newposition based on new velocities
		Point2D finalBPosition = newBPosition + ((m_B.velocity * 0.5) * (i_dt - i_timeOfCollision));
		SmartPointer<GameObject2D> tempSmartObjForB = m_B.m_GameObject.AquireOwnership();
		if (tempSmartObjForB != nullptr) {
			m_B.prevPosition = newBPosition;
			m_B.currentPosition = finalBPosition;
			tempSmartObjForB->SetPosition(finalBPosition);
		}




	}

	


	void PhysicsSystem::CollisionResolutionUsingMomentumAndReflectionForStaticObjects(PhysicsSystem::PhysicsInfo & m_A, PhysicsSystem::PhysicsInfo & m_B, float i_timeOfCollision, int i_MirrorAxis, float i_dt)
	{

		
		//If both are static then no need to resolve, coz they stay there
		if (m_A.isStatic && m_B.isStatic) {
			return;
		}
		//If it is colliding with the end collider the game is over
		if (&m_B == AllPhysicsObjects.at(2)) {
			Engine::GameOver();
			return;
		}

		//Relative velocity
		float V_XInitial_A = m_A.velocity.x() - m_B.velocity.x();

		float V_YInitial_A = m_A.velocity.y() - m_B.velocity.y();


		float V_XFinal_A;
		float V_YFinal_A;

		
		
		//Collision with a static object just mirrors the colliding object's velocity 
		//X axis is the mirror axis
		if (i_MirrorAxis == 0) {
			V_XFinal_A = -V_XInitial_A;
			V_YFinal_A = V_YInitial_A;
			if (&m_B == AllPhysicsObjects.at(1) ) {
				V_XFinal_A = -V_XInitial_A;
				V_YFinal_A = V_YInitial_A;
			}
		}
		//Y axis
		if (i_MirrorAxis == 1) {
			V_XFinal_A = V_XInitial_A;
		
			V_YFinal_A = -V_YInitial_A;//((m_A.mass - m_B.mass) * V_YInitial_A) / (totalMass);
			if (&m_B == AllPhysicsObjects.at(1) ) {
				V_XFinal_A = (m_A.currentPosition.x() - m_B.currentPosition.x()) > 0 ? (V_XFinal_A > 0 ? V_XFinal_A : -V_XFinal_A) : (V_XFinal_A > 0 ? -V_XFinal_A : V_XFinal_A);
				V_XFinal_A = V_XFinal_A * (1 + 0.05f *(fabs(m_A.currentPosition.x() - m_B.currentPosition.x()) * fabs(m_A.currentPosition.x() - m_B.currentPosition.x())));
				float maxX = 0.225f;
				float maxY = 0.5f;
					//Game tends to be slow in Debug mode
					#if defined _DEBUG
						maxX *= 2;
						maxY *= 2;
					#endif
				
				V_XFinal_A = (V_XFinal_A > maxX) ? maxX : (V_XFinal_A < -maxX ? -maxX : V_XFinal_A);
				
				V_YFinal_A = (V_YFinal_A > 0 && V_YFinal_A < maxY) ? V_YFinal_A + 0.3f : (V_YFinal_A < 0 && V_YFinal_A>-maxY ? V_YFinal_A - 0.3f : maxY);
			}
		}


		//Add the velocities (which are subtracted for relative velocities)
		V_XFinal_A += m_B.velocity.x();
		

		V_YFinal_A += m_B.velocity.y();
		
		//For Object A
		//Set the position to at the time of collision
		Point2D newAPosition = m_A.currentPosition + (((m_A.velocity + m_A.prevVelocity)*0.5)* i_timeOfCollision);
		//Now we have the final velocities. Assuming we are at the collision point - calculate the newPositions based on the new velocities
		m_A.prevVelocity = Point2D(0, 0);
		m_A.velocity = Point2D(V_XFinal_A, V_YFinal_A);
		//calculate newposition based on new velocities
		Point2D finalAPosition = newAPosition + ((m_A.velocity * 0.5) * (i_dt - i_timeOfCollision));
		SmartPointer<GameObject2D> tempSmartObjForA = m_A.m_GameObject.AquireOwnership();
		if (tempSmartObjForA != nullptr) {

			m_A.prevPosition = newAPosition;
			m_A.currentPosition = finalAPosition;

			tempSmartObjForA->SetPosition(finalAPosition);
		}

		//Block's death
		SmartPointer<GameObject2D> tempSmartObjForB = m_B.m_GameObject.AquireOwnership();
		if (tempSmartObjForB != nullptr) {
			KillBlock(&tempSmartObjForB);
		}

		



	}
	
	
	//Handy function
	Point2D PhysicsSystem::CapToMaxVelocity(Point2D i_Velocity) {
		float VelocityX = i_Velocity.x();
		float VelocityY = i_Velocity.y();
		if (VelocityX < 0 && VelocityX < maxVelocity) {
			VelocityX = -maxVelocity;
		}
		else if (VelocityX > 0 && VelocityX > maxVelocity) {
			VelocityX = maxVelocity;
		}
		if (VelocityY < 0 && VelocityY < maxVelocity) {
			VelocityY = -maxVelocity;
		}
		else if (VelocityY > 0 && VelocityY > maxVelocity) {
			VelocityY = maxVelocity;
		}
		return Point2D(VelocityX, VelocityY);
	}

	Point2D PhysicsSystem::ApplyDragToVelocity(Point2D i_Velocity) {
		float minVelocity = 0.00000000001f;

		float velocityX = i_Velocity.x(), velocityY = i_Velocity.y();
		velocityX = 0.9f/** i_dt*/ * velocityX;
		velocityY = 0.9f /**i_dt*/ * velocityY;
		if (velocityX < minVelocity && velocityX > -minVelocity) {
			velocityX = 0;
		}
		
		if (velocityY < minVelocity && velocityY > -minVelocity) {
			velocityY = 0;
		}
		
		return Point2D(velocityX, velocityY);

	}




	Point2D PhysicsSystem::GetPosition(const SmartPointer<GameObject2D>& i_OtherObj)
	{

		Point2D pos = Point2D(-9999, -9999);
		for (auto physicsObj : AllPhysicsObjects) {
			if (physicsObj->m_GameObject == i_OtherObj) {
				pos = physicsObj->currentPosition;
			}
		}
		assert(pos != Point2D(-9999, -9999));
		return pos;
	}

	Point2D PhysicsSystem::GetVelocity(const SmartPointer<GameObject2D>& i_OtherObj)
	{
		Point2D vel = Point2D(-9999, -9999);
		for (auto physicsObj : AllPhysicsObjects) {
			if (physicsObj->m_GameObject == i_OtherObj) {
				vel = physicsObj->velocity;
			}
		}
		assert(vel != Point2D(-9999, -9999));
		return vel;
	}

	void PhysicsSystem::AddForce(float i_forceVal, int i_direction, const SmartPointer<GameObject2D> & i_OtherObj) {
		for (auto physicsObj : AllPhysicsObjects) {
			if (physicsObj->m_GameObject == i_OtherObj) {
				float forceX = physicsObj->force.x();
				float forceY = physicsObj->force.y();
				if (i_direction == 0) {
					forceY += i_forceVal;
				}
				else {
					forceX += i_forceVal;
				}
				float maxForce = 0.75;
				if (fabs(forceX) >= maxForce) {
					forceX = forceX > 0 ? maxForce : -maxForce;
				}
				if (fabs(forceY) >= maxForce) {
					forceY = forceY > 0 ? maxForce : -maxForce;
				}
				Point2D newForce = Point2D(forceX, forceY);
				physicsObj->force = newForce;
				
			}
		}

	}

	void PhysicsSystem::RemoveForce(float i_forceVal, int i_direction, const SmartPointer<GameObject2D> & i_OtherObj) {
		for (auto physicsObj : AllPhysicsObjects) {
			if (physicsObj->m_GameObject == i_OtherObj) {

				float forceX = physicsObj->force.x();
				float forceY = physicsObj->force.y();
				if (i_direction == 0) {
					if (forceY != 0) {
						if (i_forceVal > 0 && forceY < 0) {
							forceY += i_forceVal;
						}
						else if (i_forceVal < 0 && forceY > 0) {
							forceY += i_forceVal;
						}
					}
				}
				else {
					if (forceX != 0) {
						if (i_forceVal > 0 && forceX < 0) {
							forceX += i_forceVal;
						}
						else if (i_forceVal < 0 && forceX > 0) {
							forceX += i_forceVal;
						}
					}

				}
				Point2D newForce = Point2D(forceX, forceY);
				physicsObj->force = newForce;
				

			}
		}

	}

	

	void PhysicsSystem::AddPhysicsObject(PhysicsInfo * i_PhysicsObject)
	{
		AllPhysicsObjects.push_back(i_PhysicsObject);
	}



	void PhysicsSystem::CleanUp() {
		for (unsigned i = 0; i < AllPhysicsObjects.size(); i++) {

			delete AllPhysicsObjects.at(i);
		}
		AllPhysicsObjects.clear();
		AllPhysicsObjects.shrink_to_fit();

		std::vector<PhysicsInfo *>().swap(AllPhysicsObjects);
		AllPhysicsObjects.~vector();
		
	}
}
