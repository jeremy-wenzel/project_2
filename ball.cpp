#include "ball.h"

ball::ball(Ogre::String name,
			Ogre::SceneManager* sceneMgr,
			Simulator* sim,
			btScalar mass,
			btScalar restit,
			btScalar fric,
			Real radius,
			Vector3 initialPosition)
	:GameObject(name, sceneMgr, sim, mass, restit, fric)
	{
		this->radius = radius;
		Entity *entity = sceneMgr->createEntity(name + "Node", name);
		this->_entity = entity;
		this->node = _rootNode->createChildSceneNode("sphereNode");
		this->node->attachObject(_entity);
		this->node->setPosition(initialPosition);
		this->_entity->setCastShadows(true);
		this->radius = entity->getBoundingRadius();
		this->velocity = Vector3(0, 0, 0);
	}

void ball::update(const FrameEvent &evt)
{
	Vector3 position = this->node->getPosition();
	this->node->translate(speed * evt.timeSinceLastFrame * velocity);
}

void ball::changeVelocity(Vector3 velocity)
{
	this->velocity = velocity;
}

ball::~ball()
{

}

