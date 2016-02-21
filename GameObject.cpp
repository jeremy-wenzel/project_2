#include "GameObject.h"

GameObject::GameObject (Ogre::String name,
						Ogre::SceneManager* sceneManager,
						Simulator* simulator,
						btScalar mass,
						btScalar restitution,
						btScalar friction) 
{
	_name = name;
	_sceneManager = sceneManager;
	_simulator = simulator;
	_mass = mass;
	_restitution = restitution;
	_friction = friction;
}

GameObject::~GameObject() {

}

btRigidBody* GameObject::getBody() {
	return _body;
}

