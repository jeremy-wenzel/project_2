#pragma once

/* Ogre Includes */
#include <OgreMeshManager.h>

/* Game Includes */
#include "GameObject.h"

#include <SDL_mixer.h>
#include <SDL.h>
#include "PointSystem.h"
#include "OgreText.h"

class Wall : public GameObject {
private:
	Mix_Chunk *gScratch;
	PointSystem *_ps;
	float lastTime;
	OgreText *text;
public:
	bool _active;
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
			Ogre::Real yaw,
			PointSystem *ps);
	~Wall();
	void update(float elapsedTime);
	void setKinematic();
	OgreMotionState* getMotionState();
	Ogre::Entity* getEntity();
	// void update() {}
};
