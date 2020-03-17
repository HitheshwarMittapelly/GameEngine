#pragma once
#include "WeakPointer.h"
#include "GameObject2D.h"
#include "Vector3d.h"
#include "Vector4d.h"
#include "Matrix_4x4.h"
#include <vector>
namespace PhysicsSystem {
	struct BoundingBox {
		Point2D m_center;
		Point2D m_extents;
		BoundingBox(const Point2D & i_center, const Point2D & i_extents)
			:m_extents(i_extents)
		{
			m_center = Point2D(0, i_extents.y());
		}
		BoundingBox() {

		}
	};
	struct PhysicsInfo {
	
		WeakPointer<GameObject2D> m_GameObject;
	
		BoundingBox  m_BB;
		Point2D prevPosition;
		Point2D currentPosition;
		Point2D velocity;
		Point2D prevVelocity;
		Point2D force;
		bool collidedInThisFrame;
		float zRotation;
		float mass;
		float collisionTime;
		bool isStatic;
		bool needsUpdate;
		PhysicsInfo(const SmartPointer<GameObject2D> & i_Other, float i_Mass,const Point2D & i_extents,bool i_isStatic) :
			m_GameObject(i_Other),
			mass(i_Mass),
			isStatic(i_isStatic){
			velocity = Point2D(0, 0);
			prevVelocity = Point2D(0, 0);
			currentPosition = i_Other->GetPosition();
			zRotation = i_Other->GetZRotation();
			m_BB =  BoundingBox(currentPosition, i_extents);
			force = Point2D(0, 0);
			collidedInThisFrame = false;
			needsUpdate = true;
			collisionTime = -100;
		}
		PhysicsInfo() {

		}
	};

	

	
	const float coeffOfFriction = 0.7f;
	const float maxVelocity = 0.15f;
	
	void Run(float i_dt);
	void CalculateVelocity(float i_dt);
	void ComputeCollisions(float i_dt);
	bool CheckForCollisionBetweenObjects( PhysicsSystem::PhysicsInfo & m_A,  PhysicsSystem::PhysicsInfo & m_B, float i_dt);
	
	Point2D CapToMaxVelocity(Point2D i_Velocity);
	Point2D ApplyDragToVelocity(Point2D i_Velocity);
	void AddForce(float i_newForceVal, int i_direction, const SmartPointer<GameObject2D> & i_OtherObj);
	void RemoveForce(float i_newForceVal, int i_direction, const SmartPointer<GameObject2D> & i_OtherObj);
	float RandInRange(float a, float b);
	

	void AddPhysicsObject(PhysicsInfo * i_PhysicsObject);
	Point2D GenerateRandomVector(Point2D min, Point2D max); 

	void AddVelocity(Point2D i_Velocity);
	Point2D GetPosition( const SmartPointer<GameObject2D> & i_OtherObj);
	Point2D GetVelocity( const SmartPointer<GameObject2D> & i_OtherObj);
	void CollisionCheckInDestinationCoordinateSystem( PhysicsSystem::PhysicsInfo & m_Source,  PhysicsSystem::PhysicsInfo & m_Destination, float i_dt);
	void CollisionResolutionUsingMomentumAndReflection(PhysicsSystem::PhysicsInfo & m_A, PhysicsSystem::PhysicsInfo & m_B, float i_timeOfCollision,int i_MirrorAxis,float i_dt);
	
	void CollisionResolutionUsingMomentumAndReflectionForStaticObjects(PhysicsSystem::PhysicsInfo & m_A, PhysicsSystem::PhysicsInfo & m_B, float i_timeOfCollision,int i_MirrorAxis,float i_dt);
	
	void CleanUp();
}


