#pragma once

/* Ogre Includes */
#include <OgreMeshManager.h>

/* Game Includes */
#include "GameObject.h"

class Wall : public GameObject {
private:
	bool _active;
public:
	Wall (Ogre::String name,
		  Ogre::SceneManager* sceneMgr,
		  Simulator* sim,
		  btScalar mass,
		  btScalar restit,
		  btScalar fric,
		  Ogre::Real length,
			Ogre::Real height,
			Ogre::Real x_pos,
			Ogre::Real y_pos,
			Ogre::Real z_pos,
			Ogre::Real roll,
			Ogre::Real pitch,
			Ogre::Real yaw);
	~Wall();
	void update();
	void setKinematic();
	OgreMotionState* getMotionState();
};
