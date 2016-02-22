#include "GameObject.h"

/* 

Constructor for the GameObject.
The necessary information to create a GameObject is as follows:
- A name for the Object that should easily idenfity the object
- Ogre SceneManager pointer so that the object can add nodes to the sceneManager
	without having to constantly send in the sceneManager
- Simulator pointer so that the object can easily add objects to the simulation world
- A mass of the GameObject. If 0, then we can assume that the object is static
- Restitution (Yeah still trying to figure it out)
- Friction (Still trying to figure it out) 

*/
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

// Destructor that isn't really doing anything
GameObject::~GameObject() {

}

// Add object to the Simulator as well as doing some
// Bullet Physics stuff
void GameObject::addToSimulator() {

}

// Get the Bullet Physics body pointer
btRigidBody* GameObject::getBody() {
	return _body;
}

// Transform the object from the Bullet World to the Ogre World
void GameObject::updateTransform() {

}
