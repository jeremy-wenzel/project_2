#include "paddle.h"

Paddle::Paddle (Ogre::SceneManager* sceneMgr,
				Simulator* sim,
				btScalar mass,
				btScalar restit,
				btScalar fric,
				Ogre::Real height, Ogre::Real width, Ogre::Real depth,
				Ogre::Real x_pos,
				Ogre::Real y_pos,
				Ogre::Real z_pos,
				Ogre::Real roll,
				Ogre::Real pitch,
				Ogre::Real yaw)
				: GameObject("paddle", sceneMgr, sim, mass, restit, fric) {
	_active = true;
	_moveSpeed = 200.f;

	// Build entity and node to go into root
	_entity = sceneMgr->createEntity("cube.mesh");
	_entity->setCastShadows(true);
	_parentNode = sceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(x_pos, y_pos, z_pos));
	_rootNode = _parentNode->createChildSceneNode();
	//_rootNode->translate(0, Ogre::Real(height), 0);
	//_rootNode->pitch(Ogre::Degree(45));

	// Create Transform
	_tr.setIdentity();
	_tr.setOrigin(btVector3(x_pos, y_pos, z_pos));
	//_tr.setRotation(btQuaternion(yaw, pitch, roll, 0));

	// Set Motion State
	_shape = new btBoxShape(btVector3(btScalar(height/2.f), btScalar(width/2.f), btScalar(depth/2.f)));
	_motionState = new OgreMotionState(_tr, _rootNode);
	// Set origin (both in Ogre and in Bullet)

	_rootNode->scale(Ogre::Vector3(height/100.f, width/100.f, depth/100.f));

	_rootNode->pitch(Ogre::Degree(pitch));
	_rootNode->roll(Ogre::Degree(roll));
	_rootNode->yaw(Ogre::Degree(yaw));

	// Create entity for plane
	_rootNode->attachObject(_entity);

	addToSimulator();
	setKinematic(true);
}

Paddle::~Paddle () {
	delete _motionState;	
}

void Paddle::update () {

}

Ogre::SceneNode* Paddle::getParentNode() {
	return _parentNode;
}

void Paddle::updateTransform() {
	if (_parentNode) {
		Ogre::Vector3 position = _parentNode->getPosition();
		_tr.setOrigin(btVector3(position.x, position.y, position.z));
		Ogre::Quaternion quat = _rootNode->getOrientation();
		_tr.setRotation(btQuaternion(quat.x, quat.y, quat.z, quat.w));
	}
	if (_motionState) {
		_motionState->updateTransform(_tr);	
	}
}