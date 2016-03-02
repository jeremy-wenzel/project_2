#pragma once

/* Ogre Includes */
#include <OgreMeshManager.h>
#include <OgreParticleSystem.h>

/* Game Includes */
#include "GameObject.h"

class Paddle : public GameObject {
private:
	bool _active;
	Ogre::SceneNode* _parentNode;

public:
	Ogre::Real _moveSpeed;
	
	Paddle (Ogre::SceneManager* sceneMgr,
		  	Simulator* sim,
			btScalar mass, btScalar restit, btScalar fric,
			Ogre::Real length,
			Ogre::Real height,
			Ogre::Real depth,
			Ogre::Real x_pos,
			Ogre::Real y_pos,
			Ogre::Real z_pos,
			Ogre::Real roll,
			Ogre::Real pitch,
			Ogre::Real yaw);
	~Paddle();
	void update();
	Ogre::SceneNode* getParentNode();
	void updateTransform();
};
