#pragma once

#include "Wall.h"
#include <vector>
#include "PointSystem.h"

class Room {
private:
	static std::vector<Wall*> walls;
	int wallLength = 500;

public:
	Room(Ogre::SceneManager* sceneManager, Simulator *sim, PointSystem *ps);
	~Room();
	Ogre::Vector3 checkBoundary(Ogre::SceneNode *node, Ogre::Vector3 move, int index);
	static void reset() {
		for(std::vector<Wall*>::iterator it = walls.begin(); it != walls.end(); ++it)
		{
			(*it)->_active = true;
			(*it)->getEntity()->setMaterialName("Examples/Rockwall");
		}
	}
};