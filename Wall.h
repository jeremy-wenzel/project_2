#pragma once

/* Ogre Includes */
#include <OgreMeshManager.h>
// #include <OgreTimerImp.h>

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
	Ogre::Timer* timer;
	Ogre::Timer* materialTimer;
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
			Ogre::Real yaw,
			PointSystem *ps,
			Ogre::String material);
	~Wall();
	void update(float elapsedTime);
	void setKinematic();
	OgreMotionState* getMotionState();
	Ogre::Entity* getEntity();
	Ogre::String getName();
	// void update() {}
};
