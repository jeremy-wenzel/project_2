/* Motion state to provide interface between simulation and rendering */
/* Used for moving objects */

#pragma once

/* Bullet Includes */
#include <btBulletDynamicsCommon.h>

/* Ogre Includes */
#include <OgreSceneManager.h>

class OgreMotionState : public btMotionState {
protected:
	Ogre::SceneNode* mVisibleobj;
	btTransform mPosl;

public:
	OgreMotionState(const btTransform intialpos, Ogre::SceneNode* node) {
		mVisibleobj = node;
		mPosl = intialpos;
	}

	virtual ~OgreMotionState();

	void setNode(Ogre::SceneNode* node);
	void updateTransform(btTransform& newpos);

	/* Initialize object position when it enters simulation */
	virtual void getWorldTransform(btTransform& worldTrans) const {
		worldTrans = mPosl;
	}

	/* Call motion state during simulation to move body in rendering world */
	virtual void setWorldTransform(const btTransform& worldTrans) {
		if (NULL == mVisibleobj)
			return;

		btQuaternion rot = worldTrans.getRotation();
		mVisibleobj->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
		btVector3 pos = worldTrans.getOrigin();
		mVisibleobj->setPosition(pos.x(), pos.y(), pos.z());
	}
};

