#pragma once
/* 
GameObject class for creating objects to be placed in the game world.
*/

/* Ogre Includes */
#include <OgreString.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

/* Bullet Includes */
#include <btBulletDynamicsCommon.h>

#include "Simulator.h"

// Needed for forward declearation
class Simulator;

class GameObject {
	protected:
		Ogre::String name;
		Ogre::SceneManager* sceneManager;
		Simulator* simulator;
		Ogre::SceneNode* rootNode;
		Ogre::Entity* entity;
		btCollisionShape* shape;
		btScalar mass;
		btRigidBody* body;
		btTransform tr;
		btVector3 inertia;

	public:
		GameObject() = default;
		~GameObject() = default;

};