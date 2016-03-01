#include "Simulator.h"

/* Constructor for the simulation world. Creates all the objects needed for simulation*/
Simulator::Simulator() {
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
												overlappingPairCache,
												solver,
												collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -100, 0));
}

/* Destructor for Simulation world. Frees all pointers*/
Simulator::~Simulator() {
	if (collisionConfiguration)
		delete collisionConfiguration;
	if (dispatcher)
		delete dispatcher;
	if (overlappingPairCache)
		delete overlappingPairCache;
	if (solver)
		delete solver;
	if (dynamicsWorld)
		delete dynamicsWorld;

	// Also need to go thorugh collision objects to delete them as well
	// Probably have to go thorugh object list to delete objects
}

// Adds object to simulation world as well as to the total object list
void Simulator::addObject(GameObject* o) {
	objectList.push_back(o);
	dynamicsWorld->addRigidBody(o->getBody());
}

// Removes an object from the simulation world. 
// Not sure if wee need it not
bool Simulator::removeObject(GameObject* o) {
	return false;
}

btDiscreteDynamicsWorld* Simulator::getWorld() {
	return dynamicsWorld;
}
// Does a step of the simulation world.
// After stpe is done, goes through all objects and checks if there are any collisions
void Simulator::stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps,
							   Ogre::Real fixedTimeStep) {
	dynamicsWorld->stepSimulation(elapsedTime, maxSubSteps, fixedTimeStep);

	// go through each object and do updates
	for (int i = 0; i < objectList.size(); ++i) {
		dynamicsWorld->contactTest(objectList[i]->getBody(), *(objectList[i]->_cCallBack));
	}

	for (int i = 0; i < objectList.size(); ++i) {
		objectList[i]->update();
	}
}
