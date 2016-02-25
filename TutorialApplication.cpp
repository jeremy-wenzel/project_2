/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/
#include <iostream>

#include "TutorialApplication.h"

using namespace std;

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // Create your scene here :)
    mCameraMan->getCamera()->setPosition(0, 0, 0);
    //mCameraMan->getCamera()->lookAt(0, 0, 0);
    mCameraMan->setStyle(OgreBites::CS_ORBIT);
    mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
    Light *diffuseLight = mSceneMgr->createLight("diffuse light");
    // make this light a point light
    diffuseLight->setType(Light::LT_POINT);            
    diffuseLight->setDiffuseColour(20.0, 20.0, 20.0);

    sim = new Simulator();
    p = new Paddle(mSceneMgr, sim, btScalar(1), btScalar(1), btScalar(.5f), 
        Ogre::Real(40), Ogre::Real(20), Ogre::Real(5), 
        Ogre::Real(0), Ogre::Real(0), Ogre::Real(0), 
        Ogre::Real(0), Ogre::Real(0), Ogre::Real(0));
    camNode = p->getNode()->createChildSceneNode(Ogre::Vector3(0,5.f,0));
    camNode->attachObject(mCameraMan->getCamera());

    mCameraMan->getCamera()->setAutoTracking(true, p->getNode());
}
//---------------------------------------------------------------------------

bool TutorialApplication::keyPressed(const OIS::KeyEvent &arg) {
    BaseApplication::keyPressed(arg);

    if (arg.key == OIS::KC_W) {
        p->getNode()->translate(p->getNode()->getOrientation() * Ogre::Vector3(0,0,p->_moveSpeed));
        cout << "forward (" << p->getNode()->getPosition().x << ", " << p->getNode()->getPosition().y << ", " << p->getNode()->getPosition().z << ")" << endl;
    }
    if (arg.key == OIS::KC_S) {
        p->getNode()->translate(p->getNode()->getOrientation() * Ogre::Vector3(0,0,-p->_moveSpeed));
        cout << "back (" << p->getNode()->getPosition().x << ", " << p->getNode()->getPosition().y << ", " << p->getNode()->getPosition().z << ")" << endl;
    }
    if (arg.key == OIS::KC_A) {
        p->getNode()->translate(p->getNode()->getOrientation() * Ogre::Vector3(p->_moveSpeed,0,0));
        cout << "left (" << p->getNode()->getPosition().x << ", " << p->getNode()->getPosition().y << ", " << p->getNode()->getPosition().z << ")" << endl;

    }
    if (arg.key == OIS::KC_D) {
        p->getNode()->translate(p->getNode()->getOrientation() * Ogre::Vector3(-p->_moveSpeed,0,0));
        cout << "right (" << p->getNode()->getPosition().x << ", " << p->getNode()->getPosition().y << ", " << p->getNode()->getPosition().z << ")" << endl;
    }


    return true;
}

bool TutorialApplication::mouseMoved(const OIS::MouseEvent &arg)
{
    BaseApplication::mouseMoved(arg);

    p->getNode()->yaw(Ogre::Degree(-arg.state.X.rel * .5f));
    p->getNode()->pitch(Ogre::Degree(-arg.state.Y.rel * .25f));
    //camNode->translate(Ogre::Vector3(arg.state.X.rel * 5.f, arg.state.Y.rel * 5.f, 0.f));

    return true;
}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
