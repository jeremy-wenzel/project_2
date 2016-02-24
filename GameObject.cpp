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

	// Not sure what to set these to
	_context = NULL;
	_cCallBack = NULL;
}

// Destructor that isn't really doing anything
GameObject::~GameObject() {
	std::cout << "Destorying game object" << std::endl;
}

// Add object to the Simulator as well as doing some
// Bullet Physics stuff
void GameObject::addToSimulator() {
	updateTransform();

	if (_mass != 0.0f)
		_shape->calculateLocalInertia(_mass, _inertia);

	std::cout << _mass << std::endl;
	btRigidBody::btRigidBodyConstructionInfo rbInfo(_mass, _motionState, _shape, _inertia);
	rbInfo.m_restitution = _restitution;
	rbInfo.m_friction = _friction;
	_body = new btRigidBody(rbInfo);
	_body->setUserPointer(this);


	// _context = new CollisionContext();
	// _cCallBack = new BulletContactCallback(*_body, *_context);

	_simulator->addObject(this);	
}

// Get the Bullet Physics body pointer
btRigidBody* GameObject::getBody() {
	return _body;
}

// Transform the object from the Bullet World to the Ogre World
void GameObject::updateTransform() {
	if (_rootNode) {
		Ogre::Vector3 position = _rootNode->getPosition();
		_tr.setOrigin(btVector3(position.x, position.y, position.z));
		Ogre::Quaternion quat = _rootNode->getOrientation();
		_tr.setRotation(btQuaternion(quat.x, quat.y, quat.z, quat.w));
	}
	if (_motionState) {
		_motionState->updateTransform(_tr);	
	}
}

void GameObject::setKinematic(bool flag) {
	if (flag) {
		_body->setCollisionFlags(_body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		_body->setActivationState(DISABLE_DEACTIVATION);
	}
}