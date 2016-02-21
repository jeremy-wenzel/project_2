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

/* Game Includes */
#include "OgreMotionState.h"
#include "Simulator.h"

// Needed for forward declearation
class Simulator;

class GameObject {
protected:
	Ogre::String name;
	Ogre::SceneManager* sceneManager;
	Ogre::SceneNode* rootNode;
	Ogre::Entity* entity;
	OgreMotionState* motionState;

	Simulator* simulator;
	btCollisionShape* shape;
	btRigidBody* body;
	btScalar mass;
	btScalar restitution;
	
	btScalar friction;
	btTransform tr;
	btVector3 inertia;		

public:
	GameObject();
	virtual ~GameObject();
	virtual btRigidBody* getBody();

};

btRigidBody* GameObject::getBody() {
	return body;
}