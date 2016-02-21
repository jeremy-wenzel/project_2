#include "Simulator.h"

Simulator::Simulator() {
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
												overlappingPairCache,
												solver,
												collisionConfiguration);
}

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

void Simulator::addObject(GameObject* o) {
	objectList.push_back(o);
	dynamicsWorld->addRigidBody(o->getBody());
}

bool Simulator::removeObject(GameObject* o) {
	return false;
}
void Simulator::stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps,
							   Ogre::Real fixedTimeStep) {
	dynamicsWorld->stepSimulation(elapsedTime, maxSubSteps, fixedTimeStep);
}

int main() {
	return 0;
}
