#include "Wall.h"

Wall::Wall (Ogre::String name,
			Ogre::SceneManager* sceneMgr,
			Simulator* sim,
			btScalar mass,
			btScalar restit,
			btScalar fric,
			Ogre::Real length,
			Ogre::Real height,
			Ogre::Real x_pos,
			Ogre::Real y_pos,
			Ogre::Real z_pos,
			Ogre::Degree roll,
			Ogre::Degree pitch,
			Ogre::Degree yaw) : GameObject(name, sceneMgr, sim, mass, restit, fric) {

	_active = true;

	// Build Plane and create mesh
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"wall",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		length, height,
		20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);
	
	// Build entity and node to go into root
	_entity = sceneMgr->createEntity("wall");
	_rootNode = sceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(x_pos, 
																					  y_pos, 
																					  z_pos));

	// Create Transform
	_tr.setIdentity();
	_tr.setOrigin(btVector3(x_pos, y_pos, z_pos));
	// _tr.setRotation(btQuaternion(yaw, pitch, roll, 0));

	// Set Motion State
	_motionState = new OgreMotionState(_tr, _rootNode);
	// Set origin (both in Ogre and in Bullet)

	_rootNode->pitch(pitch);
	_rootNode->roll(roll);
	_rootNode->yaw(yaw);

	// Create enitty for plane
	_rootNode->attachObject(_entity);

	addToSimulator();

}

Wall::~Wall () {
	delete _motionState;	
}

void Wall::update () {
	// Not sure if we need to do anything because wall is not doing anything
	_simulator->getWorld()->contactTest(_body, *_cCallBack);

	if (_context->hit && _active) {
		// Add point

		// Deactivate wall
		_active = false;
	}

	_context->hit = false;
}
