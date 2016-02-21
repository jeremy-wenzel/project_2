#pragma once


/* Game Includes */
#include "GameObject.h"

class Wall : public GameObject {
public:
	Wall (Ogre::String name,
		  Ogre::SceneManager* sceneMgr,
		  Simulator* sim,
		  btScalar mass,
		  btScalar restit,
		  btScalar fric);
	~Wall();
	void update();
};
