#include "ball.h"
#include <iostream>

ball::ball(Ogre::String name,
			Ogre::SceneManager* sceneMgr,
			Simulator* sim,
			btScalar mass,
			btScalar restit,
			btScalar fric,
			Ogre::Vector3 initialPosition,
			Ogre::String material)
			:GameObject(name, sceneMgr, sim, mass, restit, fric), lastTime(0.0)
	{
		Ogre::Entity *entity = sceneMgr->createEntity(name);
		this->_entity = entity;
		if (!material.empty())
			this->_entity->setMaterialName(material);
		this->_rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode("sphereNode", initialPosition);
		this->_rootNode->attachObject(this->_entity);
		this->_rootNode->setScale(Ogre::Vector3(0.1, 0.1, 0.1));
		this->_entity->setCastShadows(true);
		this->radius = entity->getBoundingRadius() * 0.1;
		_tr.setIdentity();
		_tr.setOrigin(convertVectorToBtVector(initialPosition));
		this->_shape = new btSphereShape(radius);
		this->_motionState = new OgreMotionState(this->_tr, this->_rootNode);
    	_ps = sceneMgr->createParticleSystem("Tail", "Examples/JetEngine1");
		_rootNode->attachObject(_ps);
		addToSimulator();
		setKinematic(true);
	}


void ball::changeSpeed(Ogre::Real speed)
{
	this->speed = speed;
}

void ball::moveAround(Ogre::Vector3 vector)
{
	Ogre::Vector3 transform = this->_rootNode->getPosition();
	transform += vector;
	this->_rootNode->setPosition(transform);
	updateTransform();
}

// void ball::update(){
// 	if (_cCallBack)
// 	{
// 		_simulator->getWorld()->contactTest(_body, *_cCallBack);
// 		if (_context->hit && (_context->velNorm > 2.0 || _context->velNorm < -2.0) 
// 			&& (lastTime > 0.5 || (_context->lastBody != _context->body && lastTime > 0.1))) {
// 			//Handle the hit
// 		}
// 		_context->hit = false;
// 	}
// }

void ball::update(float elapsedTime) {
	if (_cCallBack)
	{
		lastTime += elapsedTime;
		_simulator->getWorld()->contactTest(_body, *_cCallBack);
		if (_context->hit && (_context->velNorm > 2.0 || _context->velNorm < -2.0) 
			&& (lastTime > 0.5 || (_context->lastBody != _context->body && lastTime > 0.1))) {
			//Handle the hit
			lastTime = 0.0f;
		}
		_context->hit = false;
	}

	btVector3 speed = _body->getLinearVelocity();
	if (speed.length() > 1000) {
		speed = speed.normalized() * 1000;
		_body->setLinearVelocity(speed);
	}
}

Ogre::SceneNode* ball::getSceneNode() {
	return this->_rootNode;
}

OgreMotionState* ball::getMotionState() {
	return _motionState;
}

ball::~ball() {

}