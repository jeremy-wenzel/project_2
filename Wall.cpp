#include "Wall.h"
#include <iostream>
#include "Room.h"

Wall::Wall (Ogre::String name,
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
			PointSystem *ps) : GameObject(name, sceneMgr, sim, mass, restit, fric), lastTime(0){

	_active = true;

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
	_entity = sceneMgr->createEntity("wall");
	_rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(x_pos, 
																			     y_pos, 
																				 z_pos));
	_rootNode->pitch(Ogre::Degree(pitch));
	_rootNode->roll(Ogre::Degree(roll));
	_rootNode->yaw(Ogre::Degree(yaw));

	_rootNode->attachObject(_entity);

	_entity->setMaterialName("Examples/Rockwall");

	_tr.setIdentity();
	_tr.setOrigin(btVector3(x_pos, y_pos, z_pos));

	//_tr.setRotation(btQuaternion(btScalar(yaw), btScalar(pitch), btScalar(roll), 0));
	_shape = new btBoxShape(btVector3(btScalar(length), btScalar(5.f), btScalar(height)));
	_motionState = new OgreMotionState(_tr, _rootNode);

	// Set Motion State
	
	// Set origin (both in Ogre and in Bullet)
	gScratch = Mix_LoadWAV( "bat_hit_ball.wav" );
	this->_ps = ps;
	addToSimulator();
}

Wall::~Wall () {
	// std::cout << "Deleting Wall" << std::endl;
	Mix_FreeChunk( gScratch );
	delete _motionState;	
}

void Wall::update (float elapsedTime) {
	// Not sure if we need to do anything because wall is not doing anything
		lastTime += elapsedTime;
		if (_context->hit 
			&& (lastTime > 0.5 || (_context->lastBody != _context->body && lastTime > 0.1))) {
			// Add point
			// Deactivate wall
			if(_name == "ground")
			{
				_ps->updateTotalScore();
				Room::reset();
			}
			else if (_active && _name != "ground")
			{
				_entity->setMaterialName("Examples/RockwallDarker");
				_ps->updateCurrentScore();
			}
			_active = false;
			Mix_PlayChannel( -1, gScratch, 0 );
			lastTime = 0.0f;
		}
		_context->hit = false;
	// std::cout << "Collision" << std::endl;
	
}

void Wall::setKinematic() {
	_body->setCollisionFlags(_body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	_body->setActivationState(DISABLE_DEACTIVATION);
}

OgreMotionState* Wall::getMotionState() {
	return _motionState;
}

Ogre::Entity* Wall::getEntity() {
	return this->_entity;
}