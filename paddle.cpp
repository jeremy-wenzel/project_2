#include "paddle.h"

Paddle::Paddle (Ogre::SceneManager* sceneMgr,
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
				Ogre::Degree yaw)
				: GameObject("paddle", sceneMgr, sim, mass, restit, fric) {
	_active = true;
	_moveSpeed 

	// Build Plane and create mesh
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"wall",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		length, height,
		20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);
	
	// Build entity and node to go into root
	_entity = sceneMgr->createEntity("paddle");
	_rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(x_pos, 
																				 y_pos, 
																				 z_pos));

	// Create Transform
	_tr.setIdentity();
	_tr.setOrigin(btVector3(x_pos, y_pos, z_pos));
	// _tr.setRotation(btQuaternion(yaw, pitch, roll, 0));

	// Set Motion State
	_motionState = new OgreMotionState(_tr, _rootNode);
	// Set origin (both in Ogre and in Bullet)

	_rootNode->pitch(pitch);
	_rootNode->roll(roll);
	_rootNode->yaw(yaw);

	// Create entity for plane
	_rootNode->attachObject(_entity);

	addToSimulator();
}

Paddle::~Paddle () {
	delete _motionState;	
}