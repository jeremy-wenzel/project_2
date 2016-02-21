#include "Wall.h"

Wall::Wall (Ogre::String name,
			Ogre::SceneManager* sceneMgr,
			Simulator* sim,
			btScalar mass,
			btScalar restit,
			btScalar fric) 
	: GameObject(name, sceneMgr, sim, mass, restit, fric) {

}

Wall::~Wall () {

}

void Wall::update () {

}
