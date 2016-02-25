#pragma once



/* Ogre Includes */
#include <OgreString.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <Ogre.h>

#include "GameObject.h"


class ball: public GameObject {
private:
	Ogre::Real radius;
	Ogre::Real speed;
	double lastTime;
public:
	ball(Ogre::String name, Ogre::SceneManager *sceneManager, 
		 Simulator* simulator, btScalar mass,
		 btScalar restitution, btScalar friction,
		 Ogre::Vector3 initialPosition, Ogre::String material);
	~ball();
	Ogre::String material;
	virtual void update();
	void changeSpeed(Ogre::Real speed);
	void moveAround(Ogre::Vector3 vector);
	void update(float elapsedTime);
	OgreMotionState* getMotionState();


	inline btVector3 convertVectorToBtVector(const Ogre::Vector3 &V)
	{
    	return btVector3(V.x, V.y, V.z);
	}

	inline Ogre::Vector3 convertBtVectorToVector(const btVector3 &V)
	{
		return Ogre::Vector3(V.x(), V.y(), V.z());
	}



};