#pragma once

#include "Wall.h"
#include <vector>

class Room {
private:
	std::vector<Wall*> walls;
	int wallLength = 500;

public:
	Room(Ogre::SceneManager* sceneManager, Simulator *sim);
	~Room();
	Ogre::Vector3 checkBoundary(Ogre::SceneNode *node, Ogre::Vector3 move, int index);

};