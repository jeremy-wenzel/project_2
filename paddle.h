#pragma once

/* Ogre Includes */
#include <OgreMeshManager.h>

/* Game Includes */
#include "GameObject.h"

class Paddle : public GameObject {
private:
	bool _active;
	int _moveSpeed;
public:
	Paddle (Ogre::SceneManager* sceneMgr,
		  	Simulator* sim,
			btScalar mass,
			btScalar restit,
			btScalar fric,
			Ogre::Real length,
			Ogre::Real height,
			Ogre::Real x_pos,
			Ogre::Real y_pos,
			Ogre::Real z_pos,
			Ogre::Degree roll,
			Ogre::Degree pitch,
			Ogre::Degree yaw);
	~Paddle();
	void update();
};
