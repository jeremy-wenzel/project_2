#include "ball.h"

ball::ball(Ogre::String name,
			Ogre::SceneManager* sceneMgr,
			Simulator* sim,
			btScalar mass,
			btScalar restit,
			btScalar fric,
			Vector3 initialPosition)
	:GameObject(name, sceneMgr, sim, mass, restit, fric)
	{
		this->radius = radius;
		Entity *entity = sceneMgr->createEntity(name);
		this->_entity = entity;
		this->_rootNode = sceneMgr->getRootSceneNode();
		this->node = this->_rootNode->createChildSceneNode("sphereNode");
		this->node->attachObject(this->_entity);
		this->node->setPosition(initialPosition);
		this->_entity->setCastShadows(true);
		this->radius = entity->getBoundingRadius();

		btTransform initPosition(btQuaternion(0, 0, 0, 1), convertVectorToBtVector(initialPosition));

		_shape = new btSphereShape(radius);
		_motionState = new OgreMotionState(initPosition, this->node);
		addToSimulator();
	}


void ball::changeSpeed(Real speed)
{
	this->speed = speed;
}

void ball::moveAround(Vector3 vector)
{
	Vector3 transform = this->node->getPosition();
	transform += vector;
	this->node->setPosition(transform);
}

void ball::update(){}

void ball::update(float elapsedTime) {
	lastTime += elapsedTime;
	_simulator->getWorld()->contactTest(_body, *_cCallBack);
	if (_context->hit && (_context->velNorm > 2.0 || _context->velNorm < -2.0) 
		&& (lastTime > 0.5 || (_context->lastBody != _context->body && lastTime > 0.1))) {
		//Handle the hit
		lastTime = 0.0f;
	}
	_context->hit = false;
}

ball::~ball()
{

}

