#include "Room.h"

Room::Room(Ogre::SceneManager* sceneManager, Simulator *sim) {
	// Build Ground Wall
	walls.push_back(new Wall(Ogre::String("ground"),
					   sceneManager,
					   sim,
					   btScalar(0),
					   btScalar(0),
					   btScalar(0),
					   wallLength,
					   wallLength,
					   Ogre::Real(0),
					   Ogre::Real(0),
					   Ogre::Real(0),
					   Ogre::Real(0),
					   Ogre::Real(0),
					   Ogre::Real(0)));

	walls.push_back(new Wall(Ogre::String("northWall"),
					   sceneManager,
					   sim,
					   btScalar(0),
					   btScalar(0),
					   btScalar(0),
					   wallLength,
					   wallLength,
					   Ogre::Real(0),
					   Ogre::Real(wallLength/2),
					   Ogre::Real(wallLength/2),
					   Ogre::Real(0),
					   Ogre::Real(-90),
					   Ogre::Real(0)));

	walls.push_back(new Wall(Ogre::String("southWall"),
					   sceneManager,
					   sim,
					   btScalar(0),
					   btScalar(0),
					   btScalar(0),
					   wallLength,
					   wallLength,
					   Ogre::Real(0),
					   Ogre::Real(wallLength/2),
					   Ogre::Real(-wallLength/2),
					   Ogre::Real(0),
					   Ogre::Real(90),
					   Ogre::Real(0)));

	walls.push_back(new Wall(Ogre::String("eastWall"),
					   sceneManager,
					   sim,
					   btScalar(0),
					   btScalar(0),
					   btScalar(0),
					   wallLength,
					   wallLength,
					   Ogre::Real(wallLength/2),
					   Ogre::Real(wallLength/2),
					   Ogre::Real(0),
					   Ogre::Real(90),
					   Ogre::Real(0),
					   Ogre::Real(0)));

	walls.push_back(new Wall(Ogre::String("westWall"),
					   sceneManager,
					   sim,
					   btScalar(0),
					   btScalar(0),
					   btScalar(0),
					   wallLength,
					   wallLength,
					   Ogre::Real(-wallLength/2),
					   Ogre::Real(wallLength/2),
					   Ogre::Real(0),
					   Ogre::Real(-90),
					   Ogre::Real(0),
					   Ogre::Real(0)));

	walls.push_back(new Wall(Ogre::String("ceiling"),
					   sceneManager,
					   sim,
					   btScalar(0),
					   btScalar(0),
					   btScalar(0),
					   wallLength,
					   wallLength,
					   Ogre::Real(0),
					   Ogre::Real(wallLength),
					   Ogre::Real(0),
					   Ogre::Real(0),
					   Ogre::Real(180),
					   Ogre::Real(0)));
}

Room::~Room() {

}

