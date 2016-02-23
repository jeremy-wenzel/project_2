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
	Real speed;
	double lastTime;
public:
	ball(Ogre::String name, Ogre::SceneManager *sceneManager, 
		 Simulator* simulator, btScalar mass,
		 btScalar restitution, btScalar friction,
		 Vector3 initialPosition, String material);
	~ball();
	String material;
	virtual void update();
	SceneNode *node;
	void changeSpeed(Real speed);
	void moveAround(Vector3 vector);
	void update(float elapsedTime);


	inline btVector3 convertVectorToBtVector(const Vector3 &V)
	{
    	return btVector3(V.x, V.y, V.z);
	}

	inline Vector3 convertBtVectorToVector(const btVector3 &V)
	{
		return Vector3(V.x(), V.y(), V.z());
	}



};