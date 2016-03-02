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
#include "BulletContactCallback.h"
#include "OgreMotionState.h"
#include "Simulator.h"


// Needed for forward declearation
class Simulator;

class GameObject {
protected:
	Ogre::String _name;
	Ogre::SceneManager* _sceneManager;
	Ogre::SceneNode* _rootNode;
	Ogre::Entity* _entity;
	OgreMotionState* _motionState;

	Simulator* _simulator;
	btCollisionShape* _shape;
	btRigidBody* _body;
	btScalar _mass;
	btScalar _restitution;
	
	btScalar _friction;
	btTransform _tr;
	btVector3 _inertia;

	CollisionContext* _context;
		

public:
	GameObject (Ogre::String name,
				Ogre::SceneManager* sceneManager,
				Simulator* simulator,
				btScalar mass,
				btScalar restitution,
				btScalar friction);

	virtual ~GameObject();
	virtual Ogre::SceneNode* getNode();
	virtual btRigidBody* getBody();
	virtual void addToSimulator();
	virtual void updateTransform();
	// This method checks if there is a collision or not
	virtual void update(float elapsedTime) {}
	virtual void setKinematic(bool flag);
	BulletContactCallback* _cCallBack;	
};

