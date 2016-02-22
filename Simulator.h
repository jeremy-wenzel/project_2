#pragma once
/* 
Simulator Class for simulating game world
*/

/* Ogre Includes */
#include <OgreString.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

/* Bullet Includes */
#include <btBulletDynamicsCommon.h>

/* C++ inlcudes */
#include <deque>

/* Game Includes */
#include "Simulator.h"
#include "GameObject.h"

class Simulator {
	protected:
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btBroadphaseInterface* overlappingPairCache;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicsWorld;
		btAlignedObjectArray<btCollisionShape*> collisionShapes;
		std::deque<GameObject*> objectList;

	public:
		Simulator();
		~Simulator();
		void addObject(GameObject* o);
		bool removeObject(GameObject* o);
		btDiscreteDynamicsWorld* getWorld();
		void stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps = 1,
							Ogre::Real fixedTimeStep = 1.0f/60.0f);
};

