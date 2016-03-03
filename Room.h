#pragma once

#include "Wall.h"
#include <vector>
#include "PointSystem.h"

class Room {
private:
	static std::vector<Wall*> walls;
	static bool playSounds;
	int wallLength = 1000;

public:
	Room(Ogre::SceneManager* sceneManager, Simulator *sim, PointSystem *ps);
	~Room();
	// Ogre::Vector3 checkBoundary(Ogre::SceneNode *node, Ogre::Vector3 move, int index);
	bool isOutsideRoom(Ogre::Vector3 pos);
	static void reset() {
		for(std::vector<Wall*>::iterator it = walls.begin(); it != walls.end(); ++it)
		{
			(*it)->_active = true;
			if((*it)->getName() != "ground") {
				(*it)->getEntity()->setMaterialName("Examples/Rockwall");
			}
		}
	}
	static void setPlayingSounds(bool input) {playSounds = input;}
	static bool isSoundOn() {return playSounds;}
};