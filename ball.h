#pragma once



/* Ogre Includes */
#include <OgreString.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <Ogre.h>

#include "GameObject.h"

using namespace Ogre;

class ball: public GameObject {
private:
	Real radius;
	Vector3 velocity;
public:
	ball(Ogre::String name, Ogre::SceneManager *sceneManager, 
		 Simulator* simulator, btScalar mass,
		 btScalar restitution, btScalar friction,
		 Real radius, Vector3 initialPosition);
	~ball();
	void changeVelocity(Vector3 velocity);
	String material;
	virtual void update(const FrameEvent &evt);
	SceneNode *node;
	Real speed;

	inline btVector3 convertVectorToBtVector(const Vector3 &V)
	{
    	return btVector3(V.x, V.y, V.z);
	}

	inline Vector3 convertBtVectorToVector(const btVector3 &v)
	{
		return Vector3(V.x(), V.y(), V.z());
	}



};