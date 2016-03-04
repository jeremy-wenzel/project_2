#include "Room.h"


std::vector<Wall*> Room::walls;
bool Room::playSounds;

Room::Room(Ogre::SceneManager* sceneManager, Simulator *sim, PointSystem *ps) {
	// Build Ground Wall
	btScalar mass(0.f);
	btScalar rest(1.f);
	btScalar frict(0.5f);

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
					   Ogre::Real(0),
					   ps,
					   "Ogre/Tusks"));

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
					   Ogre::Real(0),
					   ps,
					   "Examples/Rockwall"));

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
					   Ogre::Real(0),
					   ps,
					   "Examples/Rockwall"));

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
					   Ogre::Real(0),
					   ps,
					   "Examples/Rockwall"));

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
					   Ogre::Real(0),
					   ps,
					   "Examples/Rockwall"));

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
					   Ogre::Real(0),
					   ps,
					   "Examples/Rockwall"));
}

Room::~Room() {

}

/* walls[0] = ground
   walls[1] = northwall
   walls[2] = southwall
   walls[3] = eastwall
   walls[4] = westwall
   walls[5] = ceiling
*/


bool Room::isOutsideRoom(Ogre::Vector3 pos) {
	// Check floor
	if (pos.y < walls[0]->getNode()->getPosition().y)
		return true;
	// Check cieling
	if (pos.y > walls[5]->getNode()->getPosition().y)
		return true;
	// Check 
	if (pos.z > walls[1]->getNode()->getPosition().z)
		return true;
	if (pos.z < walls[2]->getNode()->getPosition().z)
		return true;
	if (pos.x > walls[3]->getNode()->getPosition().x)
		return true;
	if (pos.x < walls[4]->getNode()->getPosition().x)
		return true;
	return false;
}

