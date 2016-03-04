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
			PointSystem *ps,
			Ogre::String material) : GameObject(name, sceneMgr, sim, mass, restit, fric), lastTime(0){

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

	_entity->setMaterialName(material);

	_tr.setIdentity();
	_tr.setOrigin(btVector3(x_pos, y_pos, z_pos));

	//_tr.setRotation(btQuaternion(btScalar(yaw), btScalar(pitch), btScalar(roll), 0));
	_shape = new btBoxShape(btVector3(btScalar(length)/2.f, btScalar(5.f), btScalar(height)/2.f));
	_motionState = new OgreMotionState(_tr, _rootNode);

	// Set Motion State
	
	// Set origin (both in Ogre and in Bullet)
	gScratch = Mix_LoadWAV( "bat_hit_ball.wav" );
	this->_ps = ps;
	if (_name == "ground")
	{
		text = new OgreText();

    	std::string Score("total score: " + std::to_string(this->_ps->getScore()));
    	text->setText(Ogre::String(Score));
    	text->setColor(1.0, 1.0, 1.0, 1.0);
    	text->setPosition(0, 0);
	}

	timer = new Ogre::Timer();
	addToSimulator();
}

Wall::~Wall () {
	// std::cout << "Deleting Wall" << std::endl;
	Mix_FreeChunk( gScratch );
	if (_motionState)
		delete _motionState;
	if (text)
    {
        delete text;
    }	
}

void Wall::update (float elapsedTime) {

		lastTime += elapsedTime;
		
		if (_context->hit && _context->theObject->getName() == "sphere.mesh"
			&& timer->getMilliseconds() > 200 ) {

			if (_context->theObject->getKinematic() == false)
			{

				if(_name == "ground")
				{
					// Ground bounce twice
					if (_ps->getCurrentScore() == 0) {
						_ps->updateHighScore();
						std::string Score("total score: " + std::to_string(_ps->getHighScore()));
						text->setText(Ogre::String(Score));
						Room::reset();
						_ps->resetTotal();
					}
					else {
						_ps->resetCurrent();
					}
					
				}
				else if (_name != "ground")
				{
					_entity->setMaterialName("Examples/RockwallDarker");
					_ps->updateCurrentScore();
				}
			}
			_active = false;
			std::cout << "timer " << timer->getMilliseconds() << std::endl;
			if (Room::isSoundOn() && timer->getMilliseconds() > 500)
				Mix_PlayChannel( -1, gScratch, 0 );
			lastTime = 0.0f;
			timer->reset();
		}
		_context->hit = false;
	
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


Ogre::String Wall::getName() {
	return _name;
}