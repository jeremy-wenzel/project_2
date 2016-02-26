#include "paddle.h"

Paddle::Paddle (Ogre::SceneManager* sceneMgr,
				Simulator* sim,
				btScalar mass,
				btScalar restit,
				btScalar fric,
				Ogre::Real height, Ogre::Real width, Ogre::Real depth,
				Ogre::Real x_pos,
				Ogre::Real y_pos,
				Ogre::Real z_pos,
				Ogre::Real roll,
				Ogre::Real pitch,
				Ogre::Real yaw)
				: GameObject("paddle", sceneMgr, sim, mass, restit, fric) {
	_active = true;
	_moveSpeed = 5.f;

	// Build entity and node to go into root
	_entity = sceneMgr->createEntity("cube.mesh");
	_rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(x_pos, y_pos, z_pos));

	// Create Transform
	_tr.setIdentity();
	_tr.setOrigin(btVector3(x_pos, y_pos, z_pos));
	//_tr.setRotation(btQuaternion(yaw, pitch, roll, 0));

	// Set Motion State
	_shape = new btBoxShape(btVector3(btScalar(height), btScalar(width), btScalar(depth)));
	_motionState = new OgreMotionState(_tr, _rootNode);
	// Set origin (both in Ogre and in Bullet)

	_rootNode->scale(Ogre::Vector3(height/100.f, width/100.f, depth/100.f));

	_rootNode->pitch(Ogre::Degree(pitch));
	_rootNode->roll(Ogre::Degree(roll));
	_rootNode->yaw(Ogre::Degree(yaw));

	// Create entity for plane
	_rootNode->attachObject(_entity);

	// setKinematic(true);

	addToSimulator();
}

Paddle::~Paddle () {
	delete _motionState;	
}

void Paddle::update () {

}