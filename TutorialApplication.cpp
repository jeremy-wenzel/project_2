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

#include "TutorialApplication.h"
#include <iostream>
#include <OgreLogManager.h>
//#include "userInterface.h"

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
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
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

    room = new Room(mSceneMgr, sim);
}


bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    sim->stepSimulation(evt.timeSinceLastEvent, 1);
    b->update(evt.timeSinceLastEvent);
    bool ret = BaseApplication::frameRenderingQueued(evt);
    return ret;
}
//---------------------------------------------------------------------------

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
