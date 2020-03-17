#pragma once
#include "PhysicsSystem.h"
using namespace PhysicsSystem;
static std::vector<PhysicsSystem::PhysicsInfo *> m_CollisionObjects;
namespace CollisionCheck {
	struct CollisionPair {
		PhysicsInfo * m_pObjects[2];
		float m_CollisionTime;

	};
	CollisionPair FindCollision(float i_dt)
	{
		CollisionPair CurrentCollision = { { NULL,NULL }, 0.0f };

		const size_t count = m_CollisionObjects.size();

		for (size_t i = 0; i < (count - 1); i++)
		{
			for (size_t j = i + 1; j < count; j++)
			{
				assert(m_CollisionObjects[i]);
				assert(m_CollisionObjects[j]);

				float tCollision = 0.0f;

				if (CheckForCollisionBetweenObjects(*m_CollisionObjects[i], *m_CollisionObjects[j], i_dt))
				{
					if (CurrentCollision.m_pObjects[0])
					{
						if (tCollision < CurrentCollision.m_CollisionTime)
						{
							CurrentCollision.m_pObjects[0] = m_CollisionObjects[i];
							CurrentCollision.m_pObjects[1] = m_CollisionObjects[j];
							CurrentCollision.m_CollisionTime = tCollision;
						}
					}
					else
					{
						CurrentCollision.m_pObjects[0] = m_CollisionObjects[i];
						CurrentCollision.m_pObjects[1] = m_CollisionObjects[j];
						CurrentCollision.m_CollisionTime = m_CollisionObjects[i]->collisionTime;
					}
				}
			}
		}
		return CurrentCollision;
	}
	static void CollisionPoolCheck()
	{


		const float AreaExtent = 10.0f;
		Point2D PositionMin(-AreaExtent, -AreaExtent);
		Point2D PositionMax(AreaExtent, AreaExtent);

		Point2D VelocityMin(-1.0f, -1.0f);
		Point2D VelocityMax(1.0f, 1.0f);

		const size_t numObjects = 20;

		for (size_t i = 0; i < numObjects; i++)
		{
			PhysicsInfo	*pObj = new PhysicsInfo();

			pObj->currentPosition = GenerateRandomVector(PositionMin, PositionMax);
			pObj->velocity = GenerateRandomVector(VelocityMin, VelocityMax);

			pObj->zRotation = 0.0f;

			pObj->m_BB.m_center = Point2D(0.0f, 0.0f);
			pObj->m_BB.m_extents = Point2D(0.5f, 0.5f);

			m_CollisionObjects.push_back(pObj);
		}

		while (1)
			CollisionPair Pair = FindCollision(RandInRange(0.1f, 1.0f));
	}

	
}