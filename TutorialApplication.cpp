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
#include <cmath>

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
    mCamera->setPosition(0, 0, 0);
    mCameraMan->getCamera()->lookAt(0, 0, 0);
    mCameraMan->setStyle(OgreBites::CS_MANUAL);
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
    camNode->attachObject(mCamera);

    mCamera->setAutoTracking(true, p->getNode());

    Ogre::Entity* ballEntity = mSceneMgr->createEntity("ball", "sphere.mesh");
    ballEntity->setCastShadows(true);
    ballEntity->setMaterialName("Examples/GrassFloor");
    Ogre::SceneNode* ballNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ball");
    ballNode->attachObject(ballEntity);
    ballNode->setPosition(0, 0, 0);
}
//---------------------------------------------------------------------------

bool TutorialApplication::keyPressed(const OIS::KeyEvent &arg) {
    BaseApplication::keyPressed(arg);

    if (arg.key == OIS::KC_W) {
        Ogre::Vector3 ori = p->getNode()->getOrientation() * Ogre::Vector3::UNIT_X;
        Ogre::Vector3 dir = p->_moveSpeed * Ogre::Vector3(cos(ori.x), 0, sin(ori.z));
        p->getNode()->translate(dir);
        cout << "forward (" << p->getNode()->getPosition().x << ", " << p->getNode()->getPosition().y << ", " << p->getNode()->getPosition().z << ")" << endl;
    }
    if (arg.key == OIS::KC_S) {
        //Ogre::Quaternion ori = p->getNode()->getOrientation();
        //Ogre::Vector3 dir = p->_moveSpeed * Ogre::Vector3(-cos(ori.x), 0, -sin(ori.z));
        //p->getNode()->translate(dir);
        cout << "back (" << p->getNode()->getPosition().x << ", " << p->getNode()->getPosition().y << ", " << p->getNode()->getPosition().z << ")" << endl;
    }
    if (arg.key == OIS::KC_A) {
        // Ogre::Quaternion ori = p->getNode()->getOrientation();
        // Ogre::Vector3 dir = p->_moveSpeed * Ogre::Vector3(-sin(ori.x), 0, -cos(ori.z));
        // p->getNode()->translate(dir);
        cout << "left (" << p->getNode()->getPosition().x << ", " << p->getNode()->getPosition().y << ", " << p->getNode()->getPosition().z << ")" << endl;
    }
    if (arg.key == OIS::KC_D) {
        // Ogre::Vector3 ori = p->getNode()->getOrientation();
        // Ogre::Vector3 dir = p->_moveSpeed * Ogre::Vector3(sin(ori.x), 0, cos(ori.z));
        // p->getNode()->translate(ori);
        cout << "right (" << p->getNode()->getPosition().x << ", " << p->getNode()->getPosition().y << ", " << p->getNode()->getPosition().z << ")" << endl;
    }

    if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }

    return true;
}

bool TutorialApplication::mouseMoved(const OIS::MouseEvent &arg)
{
    p->getNode()->yaw(Ogre::Degree(-arg.state.X.rel * .5f));
    p->getNode()->pitch(Ogre::Degree(-arg.state.Y.rel * .25f));

    cout << p->getNode()->getOrientation() << endl;

    return true;//BaseApplication::mouseMoved(arg);
}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    return BaseApplication::frameRenderingQueued(evt);
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
