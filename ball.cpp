#include "ball.h"

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
		this->radius = radius;
		Ogre::Entity *entity = sceneMgr->createEntity(name);
		this->_entity = entity;
		if (!material.empty())
			this->_entity->setMaterialName(material);
		this->_rootNode = sceneMgr->getRootSceneNode();
		this->node = this->_rootNode->createChildSceneNode("sphereNode");
		this->node->attachObject(this->_entity);
		this->node->setPosition(initialPosition);
		this->node->setScale(Ogre::Vector3(0.1, 0.1, 0.1));
		this->_entity->setCastShadows(true);
		this->radius = entity->getBoundingRadius() * 0.1;

		btTransform initPosition(btQuaternion(0, 0, 0, 1), convertVectorToBtVector(initialPosition));
		_tr = initPosition;
		_shape = new btSphereShape(radius);
		_motionState = new OgreMotionState(_tr, this->node);
		addToSimulator();
	}


void ball::changeSpeed(Ogre::Real speed)
{
	this->speed = speed;
}

void ball::moveAround(Ogre::Vector3 vector)
{
	Ogre::Vector3 transform = this->node->getPosition();
	transform += vector;
	this->node->setPosition(transform);
}

void ball::update(){}

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
}

OgreMotionState* ball::getMotionState(){
	return _motionState;
}

ball::~ball()
{

}

