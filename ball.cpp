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

		btTransform initPosition(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0));

		_shape = new btSphereShape(radius);
		_motionState = new OgreMotionState(initPosition, this->node);


	}

void ball::update()
{
	
}

void ball::changeVelocity(Vector3 velocity)
{
	this->velocity = velocity;
}

void ball::changeSpeed(Real speed)
{
	this->speed = speed;
}

ball::~ball()
{

}

