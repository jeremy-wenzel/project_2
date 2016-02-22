#pragma once



/* Ogre Includes */
#include <OgreString.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <Ogre.h>

#include "GameObject.h"

using namespace Ogre;

class ball: public GameObject {
private:
	Real radius;
public:
	ball(Ogre::String name, Ogre::SceneManager *sceneManager, 
		 Simulator* simulator, btScalar mass,
		 btScalar restitution, btScalar friction,
		 Real radius);
	~ball();
	String material;
	void update();
};