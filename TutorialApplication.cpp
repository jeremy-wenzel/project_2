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
#include <iostream>
#include <SDL_mixer.h>
#include <SDL.h>

using namespace std;

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
    if (b)
    {
        delete b;
    }

    for (std::vector<Wall *>::iterator it = wall.begin(); it != wall.end(); ++it)
    {
        delete (*it);
    } 
}

bool TutorialApplication::soundInit(void)
{
    if( SDL_Init( SDL_INIT_AUDIO ) < 0 ) {
        /* Failed, exit. */
        return false;
    }
    return true;

}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // Create your scene here :)

    soundInit();
    mCameraMan->getCamera()->setPosition(0, 300, 500);
    mCameraMan->getCamera()->lookAt(0, 0, 0);
    mCameraMan->setStyle(OgreBites::CS_MANUAL);
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
    Ogre::Light *diffuseLight = mSceneMgr->createLight("diffuse light");
    
    // make this light a point light
    diffuseLight->setType(Ogre::Light::LT_POINT);            
    diffuseLight->setDiffuseColour(20.0, 20.0, 20.0);
    diffuseLight->setPosition(0, 1000, 0);

    sim = new Simulator();
    btScalar mass = 10.0;
    btScalar resist = 1.0;
    btScalar friction = 0.50;
    Ogre::Vector3 initialPoint (0, 200, 0);

    
    b = new ball("sphere.mesh", mSceneMgr, sim, mass, 
                resist, friction, initialPoint, "OceanHLSL_GLSL");

    Wall *floor = new Wall("floor", mSceneMgr, sim, btScalar(0), resist, friction,
        Ogre::Real(1000),
            Ogre::Real(1000),
            Ogre::Real(-10),
            Ogre::Real(-100),
            Ogre::Real(-10),
            Ogre::Real(0),
            Ogre::Real(0),
            Ogre::Real(0));
    wall.push_back(floor);

    //p = new Paddle(mSceneMgr, sim, btScalar(0), btScalar(1), btScalar(.5f), 
    p = new Paddle(mSceneMgr, sim, btScalar(1), btScalar(1), btScalar(.5f), 
        Ogre::Real(80), Ogre::Real(10), Ogre::Real(40), 
        Ogre::Real(0), Ogre::Real(0), Ogre::Real(0), 
        Ogre::Real(0), Ogre::Real(0), Ogre::Real(0));

    doMoveForward = false;
    doMoveBackward = false;
    doMoveLeft = false;
    doMoveRight = false;

    camNode = p->getNode()->createChildSceneNode(Ogre::Vector3(0,5.f,0));
    camNode->attachObject(mCamera);
}


bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    sim->stepSimulation(evt.timeSinceLastEvent, 1);
    b->update(evt.timeSinceLastEvent);
    for (std::vector<Wall *>::iterator it = wall.begin(); it != wall.end(); ++it)
    {
        if (*it != NULL)
        {
            (*it)->update();
        }
    }

    Ogre::Real temp_move_speed= p->_moveSpeed * evt.timeSinceLastFrame;

    if (doMoveForward) {
        Ogre::Quaternion ori = p->getParentNode()->getOrientation();
        Ogre::Vector3 dir = ori * Ogre::Vector3::NEGATIVE_UNIT_Z;//p->_moveSpeed * Ogre::Vector3(ori * Ogre::Vector3::UNIT_X, 0, ori * Ogre::Vector3::UNIT_Z);
        p->getParentNode()->translate(temp_move_speed * dir);
        cout << "forward : " << p->getParentNode()->getPosition() << endl;
    }
    else if (doMoveBackward) {
        Ogre::Quaternion ori = p->getParentNode()->getOrientation();
        Ogre::Vector3 dir = ori * Ogre::Vector3::UNIT_Z;//p->_moveSpeed * Ogre::Vector3(ori * Ogre::Vector3::UNIT_X, 0, ori * Ogre::Vector3::UNIT_Z);
        p->getParentNode()->translate(temp_move_speed * dir);
        cout << "back : " << p->getParentNode()->getPosition() << endl;
    }

    if (doMoveLeft) {
        Ogre::Quaternion ori = p->getParentNode()->getOrientation();
        Ogre::Vector3 dir = ori * Ogre::Vector3::NEGATIVE_UNIT_X;//p->_moveSpeed * Ogre::Vector3(ori * Ogre::Vector3::UNIT_X, 0, ori * Ogre::Vector3::UNIT_Z);
        p->getParentNode()->translate(temp_move_speed * dir);
        cout << "left : " << p->getParentNode()->getPosition() << endl;
    }
    else if (doMoveRight) {
        Ogre::Quaternion ori = p->getParentNode()->getOrientation();
        Ogre::Vector3 dir = ori * Ogre::Vector3::UNIT_X;//p->_moveSpeed * Ogre::Vector3(ori * Ogre::Vector3::UNIT_X, 0, ori * Ogre::Vector3::UNIT_Z);
        p->getParentNode()->translate(temp_move_speed * dir);
        cout << "right : " << p->getParentNode()->getPosition() << endl;
    }

    p->updateTransform();

    bool ret = BaseApplication::frameRenderingQueued(evt);
    return ret;
}
//---------------------------------------------------------------------------

bool TutorialApplication::keyPressed(const OIS::KeyEvent &arg) {
    BaseApplication::keyPressed(arg);

    // Paddle Movement

    if (arg.key == OIS::KC_W) {
        // Ogre::Quaternion ori = p->getParentNode()->getOrientation();
        // Ogre::Vector3 dir = ori * Ogre::Vector3::NEGATIVE_UNIT_Z;//p->_moveSpeed * Ogre::Vector3(ori * Ogre::Vector3::UNIT_X, 0, ori * Ogre::Vector3::UNIT_Z);
        // p->getParentNode()->translate(p->_moveSpeed * dir);
        // cout << "forward : " << p->getParentNode()->getPosition() << endl;
        doMoveForward = true;
    }
    if (arg.key == OIS::KC_S) {
        // Ogre::Quaternion ori = p->getParentNode()->getOrientation();
        // Ogre::Vector3 dir = ori * Ogre::Vector3::UNIT_Z;//p->_moveSpeed * Ogre::Vector3(ori * Ogre::Vector3::UNIT_X, 0, ori * Ogre::Vector3::UNIT_Z);
        // p->getParentNode()->translate(p->_moveSpeed * dir);
        // cout << "back : " << p->getParentNode()->getPosition() << endl;
        doMoveBackward = true;
    }
    if (arg.key == OIS::KC_A) {
        // Ogre::Quaternion ori = p->getParentNode()->getOrientation();
        // Ogre::Vector3 dir = ori * Ogre::Vector3::NEGATIVE_UNIT_X;//p->_moveSpeed * Ogre::Vector3(ori * Ogre::Vector3::UNIT_X, 0, ori * Ogre::Vector3::UNIT_Z);
        // p->getParentNode()->translate(p->_moveSpeed * dir);
        // cout << "left : " << p->getParentNode()->getPosition() << endl;
        doMoveLeft = true;
    }
    if (arg.key == OIS::KC_D) {
        // Ogre::Quaternion ori = p->getParentNode()->getOrientation();
        // Ogre::Vector3 dir = ori * Ogre::Vector3::UNIT_X;//p->_moveSpeed * Ogre::Vector3(ori * Ogre::Vector3::UNIT_X, 0, ori * Ogre::Vector3::UNIT_Z);
        // p->getParentNode()->translate(p->_moveSpeed * dir);
        // cout << "right : " << p->getParentNode()->getPosition() << endl;
        doMoveRight = true;
    }

    ////////////////////////////////////


    if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }

    return true;
}

bool TutorialApplication::keyReleased(const OIS::KeyEvent &arg) {
    BaseApplication::keyReleased(arg);

    // Paddle Movement

    if (arg.key == OIS::KC_W) {
        doMoveForward = false;
    }
    if (arg.key == OIS::KC_S) {
        doMoveBackward = false;
    }
    if (arg.key == OIS::KC_A) {
        doMoveLeft = false;
    }
    if (arg.key == OIS::KC_D) {
        doMoveRight = false;
    }

    return true;
}

bool TutorialApplication::mouseMoved(const OIS::MouseEvent &arg)
{
    //p->getNode()->yaw(Ogre::Degree(-arg.state.X.rel * .25f));
    p->getParentNode()->yaw(Ogre::Degree(arg.state.X.rel * .5f));
    p->getParentNode()->pitch(Ogre::Degree(-arg.state.Y.rel * .25f));

    cout << p->getNode()->getOrientation() << ", " << p->getParentNode()->getOrientation() << endl;

    return true;//BaseApplication::mouseMoved(arg);
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
