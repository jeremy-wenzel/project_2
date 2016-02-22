#include "ball.h"

ball::ball(Ogre::String name,
			Ogre::SceneManager* sceneMgr,
			Simulator* sim,
			btScalar mass,
			btScalar restit,
			btScalar fric,
			Real radius)
	:GameObject(name, sceneMgr, sim, mass, restit, fric)
	{
		this->radius = radius;
		Entity *entity = sceneMgr->createEntity(name);
		this->_entity = entity;
	}

void ball::update()
{

}

ball::~ball()
{

}

