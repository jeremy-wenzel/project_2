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


using namespace std;


//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void): score(0), gameStarts(false)
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

    if (music)
        Mix_FreeMusic( music );
    // mTrayMgr->destroyWidget("Pause");
    // mTrayMgr->destroyWidget("Score");
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

// mouse event
bool TutorialApplication::mousePressed(
  const OIS::MouseEvent& me, OIS::MouseButtonID id) 
{
    if (id == OIS::MB_Left)
    {
        b->setKinematic(false);
        gameStarts = true;
    }

  return true; 
}


void TutorialApplication::createFrameListener(void)
{
    BaseApplication::createFrameListener();
    mTrayMgr->showCursor();
    std::string Score("score: " + std::to_string(score));
    mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "Score: ", Ogre::String(Score), 150);
    mTrayMgr->createButton(OgreBites::TL_BOTTOMLEFT, "Pause", "Pause", 150);
}
 
//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    music = NULL;
    // Create your scene here :)
    if (!soundInit()) {
        Ogre::LogManager::getSingleton().logMessage ("init failed");
    }
    mCameraMan->getCamera()->setPosition(0, 0, 0);
    mCameraMan->getCamera()->lookAt(0, 0, 0);
    mCameraMan->setStyle(OgreBites::CS_MANUAL);
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    mSceneMgr->setSkyBox(true, "Examples/EveningSkyBox");
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


    
    ps = new PointSystem();

    room = new Room(mSceneMgr, sim, ps);
    
    b = new ball("sphere.mesh", mSceneMgr, sim, mass * .25f, 
                resist, friction, initialPoint, "OceanHLSL_GLSL");


    //p = new Paddle(mSceneMgr, sim, btScalar(0), btScalar(1), btScalar(.5f), 
    p = new Paddle(mSceneMgr, sim, btScalar(10.f), btScalar(5.0f), btScalar(0.25f), 
        Ogre::Real(160), Ogre::Real(20), Ogre::Real(160), 
        Ogre::Real(0), Ogre::Real(90), Ogre::Real(0), 
        Ogre::Real(0), Ogre::Real(90), Ogre::Real(0));

    doMoveForward = false;
    doMoveBackward = false;
    doMoveLeft = false;
    doMoveRight = false;

    //Experimental
    doMoveUp = false;
    doMoveDown = false;
    doMoveFast = false;


    ///////////
    camNode = p->getNode()->createChildSceneNode(Ogre::Vector3(0,1000.f,500.f));
    camNode->attachObject(mCamera);
    music = Mix_LoadMUS( "halo.wav" );
    Mix_PlayMusic( music, -1 );
    musicPlaying = true;
    Room::setPlayingSounds(true);
}


bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

    sim->stepSimulation(evt.timeSinceLastEvent, 1);
    b->update(evt.timeSinceLastEvent);
    Ogre::Real temp_move_speed = p->_moveSpeed * evt.timeSinceLastFrame;

    // Paddle Movement
    if (gameStarts) {
        

        if (doMoveFast) {
            temp_move_speed *= 4.0f;
        }
        
        if (doMoveForward) {
            Ogre::Quaternion ori = p->getParentNode()->getOrientation();
            Ogre::Vector3 dir = ori * Ogre::Vector3::NEGATIVE_UNIT_Z;
            Ogre::Vector3 moveVector = (temp_move_speed * dir);
            if (!room->isOutsideRoom(moveVector + (p->getParentNode()->getPosition())))
                p->getParentNode()->translate(moveVector);
        }
        else if (doMoveBackward) {
            Ogre::Quaternion ori = p->getParentNode()->getOrientation();
            Ogre::Vector3 dir = ori * Ogre::Vector3::UNIT_Z;
            Ogre::Vector3 moveVector = (temp_move_speed * dir);
            if (!room->isOutsideRoom(moveVector + (p->getParentNode()->getPosition())))
                p->getParentNode()->translate(moveVector);
        }

        if (doMoveLeft) {
            Ogre::Quaternion ori = p->getParentNode()->getOrientation();
            Ogre::Vector3 dir = ori * Ogre::Vector3::NEGATIVE_UNIT_X;
            Ogre::Vector3 moveVector = (temp_move_speed * dir);
            if (!room->isOutsideRoom(moveVector + (p->getParentNode()->getPosition())))
                p->getParentNode()->translate(moveVector);
        }
        else if (doMoveRight) {
            Ogre::Quaternion ori = p->getParentNode()->getOrientation();
            Ogre::Vector3 dir = ori * Ogre::Vector3::UNIT_X;
            Ogre::Vector3 moveVector = (temp_move_speed * dir);
            if (!room->isOutsideRoom(moveVector + (p->getParentNode()->getPosition())))
                p->getParentNode()->translate(moveVector);
        }
    }

    //Ball Movement
    else {

        Ogre::SceneNode *node = b->getSceneNode();

        if (doMoveUp) {
            Ogre::Vector3 mvVector = 
            room->checkBoundary(node, Ogre::Vector3(0, temp_move_speed, 0), 5);
            b->moveAround(mvVector);
        }
        else if (doMoveDown) {
            Ogre::Vector3 mvVector = 
            room->checkBoundary(node, Ogre::Vector3(0, -temp_move_speed, 0), 0);
            b->moveAround(mvVector);
        }
        
        if (doMoveLeft) {
            Ogre::Vector3 mvVector = 
            room->checkBoundary(node, Ogre::Vector3(-temp_move_speed, 0, 0), 4);
            b->moveAround(mvVector);
        }
        else if (doMoveRight) {
            Ogre::Vector3 mvVector = 
            room->checkBoundary(node, Ogre::Vector3(temp_move_speed, 0, 0), 3);
            b->moveAround(mvVector);
        }
        
        if (doMoveForward) {
            Ogre::Vector3 mvVector = 
            room->checkBoundary(node, Ogre::Vector3(0, 0, temp_move_speed), 2);
            b->moveAround(mvVector);
        }
        else if (doMoveBackward) {
            Ogre::Vector3 mvVector = 
            room->checkBoundary(node, Ogre::Vector3(0, 0, -temp_move_speed), 1);
            b->moveAround(mvVector);
        }

        ///

        if (room->isOutsideRoom(b->getNode()->getPosition())) {
            gameStarts = false;
            b->getNode()->setPosition(Ogre::Vector3(0, 200, 0));
        }
    }

    Ogre::Vector3 lookPoint = b->getNode()->getPosition() + p->getParentNode()->getPosition();
    lookPoint *= .5f;
    mCamera->lookAt(lookPoint);

    p->updateTransform();

    bool ret = BaseApplication::frameRenderingQueued(evt);
    return ret;
}
//---------------------------------------------------------------------------

bool TutorialApplication::keyPressed(const OIS::KeyEvent &arg) {
    //BaseApplication::keyPressed(arg);

    switch (arg.key) {
        case OIS::KC_W      : doMoveForward  = true; break;
        case OIS::KC_S      : doMoveBackward = true; break;
        case OIS::KC_A      : doMoveLeft     = true; break;
        case OIS::KC_D      : doMoveRight    = true; break;
        case OIS::KC_E      : doMoveUp       = true; break;
        case OIS::KC_Q      : doMoveDown     = true; break;
        case OIS::KC_LSHIFT : doMoveFast     = true; break;

        case OIS::KC_ESCAPE : mShutDown      = true; break;
    }
    
    // Mute Music
    if (arg.key == OIS::KC_M) {
        // Stop Music
        if (musicPlaying) {
            musicPlaying = false;
            Mix_HaltMusic();
            Room::setPlayingSounds(false);
        }
        else {
            musicPlaying = true;
            Mix_PlayMusic(music, -1 );
            Room::setPlayingSounds(true);
        }
    }

    return true;
}

bool TutorialApplication::keyReleased(const OIS::KeyEvent &arg) {
    BaseApplication::keyReleased(arg);

    switch (arg.key) {
        case OIS::KC_W      : doMoveForward  = false; break;
        case OIS::KC_S      : doMoveBackward = false; break;
        case OIS::KC_A      : doMoveLeft     = false; break;
        case OIS::KC_D      : doMoveRight    = false; break;
        case OIS::KC_E      : doMoveUp       = false; break;
        case OIS::KC_Q      : doMoveDown     = false; break;
        case OIS::KC_LSHIFT : doMoveFast     = false; break;
    }

    return true;
}

bool TutorialApplication::mouseMoved(const OIS::MouseEvent &arg)
{
    if (gameStarts) {
        //p->getNode()->yaw(Ogre::Degree(-arg.state.X.rel * .25f));
        
        p->getParentNode()->yaw(Ogre::Degree(arg.state.X.rel * .5f));
        p->getNode()->pitch(Ogre::Degree(-arg.state.Y.rel * .25f));

        while (p->getNode()->getOrientation().getPitch().valueDegrees() > 15) {
            p->getNode()->pitch(Ogre::Radian(-0.01f));
        }
        while (p->getNode()->getOrientation().getPitch().valueDegrees() < -75) {
            p->getNode()->pitch(Ogre::Radian(0.01f));
        }

        cout << "Pitch : " << p->getNode()->getOrientation().getPitch().valueRadians() << ", Yaw : " << p->getParentNode()->getOrientation().getYaw().valueRadians() << endl;
    }

    return true; //BaseApplication::mouseMoved(arg);
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
