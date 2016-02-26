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
#include <OgreLogManager.h>
//#include "userInterface.h"

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

    if (room)
    {
        delete room;
    }
}

bool TutorialApplication::soundInit(void)
{
    if( SDL_Init( SDL_INIT_AUDIO ) < 0 ) {
        /* Failed, exit. */
        return false;
    }
      //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        return false;
    }
    return true;

}


bool TutorialApplication::mousePressed(
  const OIS::MouseEvent& me, OIS::MouseButtonID id) 
{
    if (id == OIS::MB_Left)
    {
       sim->setGravityManual(btVector3(0, -100, 0));
    }

  return true; 
}
 
//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // Create your scene here :)

    if (!soundInit()) {
        Ogre::LogManager::getSingleton().logMessage ("init failed");
    }

    mCameraMan->getCamera()->setPosition(0, 300, 500);
    mCameraMan->getCamera()->lookAt(0, 0, 0);
    //mCameraMan->setStyle(OgreBites::CS_MANUAL);
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
    Ogre::Light *diffuseLight = mSceneMgr->createLight("diffuse light");
    // make this light a point light
    diffuseLight->setType(Ogre::Light::LT_POINT);            
    diffuseLight->setDiffuseColour(20.0, 20.0, 20.0);
    diffuseLight->setPosition(0, 1000, 0);

    sim = new Simulator();
    sim->setGravityManual(btVector3(0, 0, 0));
    btScalar mass = 10.0;
    btScalar resist = 1.5;
    btScalar friction = 0.50;
    Ogre::Vector3 initialPoint (0, 100, 0);

    
    b = new ball("sphere.mesh", mSceneMgr, sim, mass, 
                resist, friction, initialPoint, "OceanHLSL_GLSL");

<<<<<<< HEAD
    room = new Room(mSceneMgr, sim);
=======
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

    p = new Paddle(mSceneMgr, sim, btScalar(1), btScalar(1), btScalar(.5f), 
        Ogre::Real(40), Ogre::Real(20), Ogre::Real(5), 
        Ogre::Real(0), Ogre::Real(0), Ogre::Real(0), 
        Ogre::Real(0), Ogre::Real(0), Ogre::Real(0));
>>>>>>> Paddle
}


bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    sim->stepSimulation(evt.timeSinceLastEvent, 1);
    b->update(evt.timeSinceLastEvent);
    bool ret = BaseApplication::frameRenderingQueued(evt);
    return ret;
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
