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

	// Build Plane and create mesh
	
	// Build entity and node to go into root

	// Set origin (both in Ogre and in Bullet)

	// Set inertia

	// Create enitty for plane

	// Create rigid body for plane

	// Add plane to rigid body world	
}

void Wall::update () {
	// Not sure if we need to do anything because wall is not doing anything
}
