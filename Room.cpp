#include "Room.h"

Room::Room(Ogre::SceneManager* sceneManager, Simulator *sim) {
	// Build Ground Wall
	
	btScalar mass(0);
	btScalar rest(1);
	btScalar frict(.5);

	walls.push_back(new Wall(Ogre::String("ground"),
					   sceneManager,
					   sim,
					   mass,
					   rest,
					   frict,
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
					   mass,
					   rest,
					   frict,
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
					   mass,
					   rest,
					   frict,
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
					   mass,
					   rest,
					   frict,
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
					   mass,
					   rest,
					   frict,
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
					   mass,
					   rest,
					   frict,
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

