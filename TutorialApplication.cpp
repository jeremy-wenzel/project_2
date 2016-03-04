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
#include "OgreText.h"



using namespace std;


//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void): muteSound(false)
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

    if (currentText)
    {
        delete currentText;
    }

    if (music)
        Mix_FreeMusic( music );
    if (pauseText)
    {
        delete pauseText;
    }
    if (endText)
    {
        delete endText;
    }
    if (paddleSound)
        Mix_FreeChunk(paddleSound);

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
    if (id == OIS::MB_Left && b->getKinematic())
    {
        b->setKinematic(false);
        ps->gameStarts = true;
        ps->gamePaused = false;
        pauseText->hideText();
        endText->hideText();
        highScore->hideText();
        ps->gameEnds = false;
    }


  return true; 
}


void TutorialApplication::createFrameListener(void)
{
    BaseApplication::createFrameListener();
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
    Ogre::Light *diffuseLight = mSceneMgr->createLight("diffuse light");
    
    // make this light a point light
    diffuseLight->setType(Ogre::Light::LT_POINT);            
    diffuseLight->setDiffuseColour(20.0, 20.0, 20.0);
    diffuseLight->setPosition(0, 1000, 0);

    sim = new Simulator();
    btScalar mass = 10.0;

    btScalar resist = 1;
    btScalar friction = 0.50;
    Ogre::Vector3 initialPoint (0, 250, 0);


    
    ps = new PointSystem();
    ps->gameStarts = false;
    ps->gamePaused = false;
    ps->gameEnds = false;

    room = new Room(mSceneMgr, sim, ps);
    
    b = new ball("sphere.mesh", mSceneMgr, sim, mass * .25f, 
                resist, friction, initialPoint, "Ogre/Tusks");


    //p = new Paddle(mSceneMgr, sim, btScalar(0), btScalar(1), btScalar(.5f), 

    p = new Paddle(mSceneMgr, sim, btScalar(10.f), btScalar(5.0f), btScalar(0.25f), 
        Ogre::Real(160), Ogre::Real(20), Ogre::Real(160), 
        Ogre::Real(0), Ogre::Real(90), Ogre::Real(0), 
        Ogre::Real(0), Ogre::Real(90), Ogre::Real(0));


    doMoveForward = false;
    doMoveBackward = false;
    doMoveLeft     = false;
    doMoveRight    = false;
    doMoveUp       = false;
    doMoveDown     = false;
    doMoveFast     = false;


    ///////////
    camNode = p->getNode()->createChildSceneNode(Ogre::Vector3(0,1000.f,500.f));
    camNode->attachObject(mCamera);


    totalText = new OgreText();

    std::string high("High score: " + std::to_string(ps->getHighScore()));
    totalText->setText(Ogre::String(high));
    totalText->setColor(1.0, 1.0, 1.0, 1.0);
    totalText->setPosition(0, 0);

    currentText = new OgreText();

    std::string currScore("current score: " + std::to_string(ps->getCurrentScore()));
    currentText->setText(Ogre::String(currScore));
    currentText->setColor(1.0, 1.0, 1.0, 1.0);
    currentText->setPosition(0, 0.9);

    pauseText = new OgreText();
    pauseText->setText("paused");
    pauseText->setColor(1.0, 0.0, 0.0, 1.0);
    pauseText->setPosition(0.05, 0.3);
    pauseText->hideText();
    pauseText->resize(0.40f);

    endText = new OgreText();
    endText->setText("Game Over");
    endText->setColor(0.0, 0.0, 0.0, 1.0);
    endText->setPosition(0.2, 0.3);
    endText->hideText();
    endText->resize(0.20f);


    highScore = new OgreText();
    highScore->setText("New HIGH Score!");
    highScore->setColor(0.0, 0.0, 1.0, 1.0);
    highScore->setPosition(0.2, 0.3);
    highScore->hideText();
    highScore->resize(0.10f);

    // Load up music and sounds
    music = Mix_LoadMUS( "halo.wav" );
    winnerSound = Mix_LoadWAV("win.wav");
    paddleSound = Mix_LoadWAV("wind.wav");
    Mix_PlayMusic( music, -1 );
    musicPlaying = true;
    Room::setPlayingSounds(true);

}


bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

    sim->stepSimulation(evt.timeSinceLastEvent, 1);

    std::string Score("Total score: " + std::to_string(ps->getScore()));
    currentText->setText(Ogre::String(Score));

    if (ps->gameEnds)
    {
        gameOver();
    }


    b->update(evt.timeSinceLastEvent);
    Ogre::Real temp_move_speed = p->_moveSpeed * evt.timeSinceLastFrame;

    // Paddle Movement
    if (ps->gameStarts && !ps->gamePaused) {
        if (doMoveFast) {
            temp_move_speed *= 4.0f;
        }
        
        if (doMoveForward) {
            Ogre::Quaternion ori = p->getParentNode()->getOrientation();
            Ogre::Vector3 dir = ori * Ogre::Vector3::NEGATIVE_UNIT_Z;
            Ogre::Vector3 moveVector = (temp_move_speed * dir);
            if (!room->isOutsideRoom(moveVector + (p->getParentNode()->getPosition())))
            {
                Mix_PlayChannel( -1, paddleSound, 0 );
                p->getParentNode()->translate(moveVector);
            }
        }
        else if (doMoveBackward) {
            Ogre::Quaternion ori = p->getParentNode()->getOrientation();
            Ogre::Vector3 dir = ori * Ogre::Vector3::UNIT_Z;
            Ogre::Vector3 moveVector = (temp_move_speed * dir);
            if (!room->isOutsideRoom(moveVector + (p->getParentNode()->getPosition())))
            {
                Mix_PlayChannel( -1, paddleSound, 0 );
                p->getParentNode()->translate(moveVector);
            }
        }

        if (doMoveLeft) {
            Ogre::Quaternion ori = p->getParentNode()->getOrientation();
            Ogre::Vector3 dir = ori * Ogre::Vector3::NEGATIVE_UNIT_X;
            Ogre::Vector3 moveVector = (temp_move_speed * dir);
            if (!room->isOutsideRoom(moveVector + (p->getParentNode()->getPosition())))
            {
                Mix_PlayChannel( -1, paddleSound, 0 );
                p->getParentNode()->translate(moveVector);
            }
        }
        else if (doMoveRight) {
            Ogre::Quaternion ori = p->getParentNode()->getOrientation();
            Ogre::Vector3 dir = ori * Ogre::Vector3::UNIT_X;
            Ogre::Vector3 moveVector = (temp_move_speed * dir);
            if (!room->isOutsideRoom(moveVector + (p->getParentNode()->getPosition())))
            {
                Mix_PlayChannel( -1, paddleSound, 0 );
                p->getParentNode()->translate(moveVector);
            }
        }
    }

    //Ball Movement
    else if(!ps->gamePaused){

        Ogre::SceneNode *node = b->getSceneNode();
        if (doMoveUp)
        {
            if (!room->isOutsideRoom(node->getPosition() + Ogre::Vector3(0, 10, 0)))
                b->moveAround(Ogre::Vector3(0, temp_move_speed, 0));
        }
        if (doMoveDown)
        {
            if(!room->isOutsideRoom(node->getPosition() + Ogre::Vector3(0, -10, 0)))
                b->moveAround(Ogre::Vector3(0, -temp_move_speed, 0));
        }

        if (doMoveLeft)
        {
            if(!room->isOutsideRoom(node->getPosition() + Ogre::Vector3(-10, 0, 0)))
                b->moveAround(Ogre::Vector3(-temp_move_speed, 0, 0));
        }
        if (doMoveRight)
        {
            if(!room->isOutsideRoom(node->getPosition() + Ogre::Vector3(10, 0, 0)))
                b->moveAround(Ogre::Vector3(temp_move_speed, 0, 0));
        }

        if (doMoveForward)
        { 
            if(!room->isOutsideRoom(node->getPosition() + Ogre::Vector3(0, 0, -10)))
                b->moveAround(Ogre::Vector3(0, 0, -temp_move_speed));
        }
        
        if (doMoveBackward)
        {
            if(!room->isOutsideRoom(node->getPosition() + Ogre::Vector3(0, 0, 10)))
                b->moveAround(Ogre::Vector3(0, 0, temp_move_speed));
        }

        ///

        if (room->isOutsideRoom(b->getNode()->getPosition())) {
            reset();
        }
    }

    Ogre::Vector3 lookPoint = b->getNode()->getPosition() + p->getParentNode()->getPosition();
    lookPoint *= .5f;
    mCamera->lookAt(lookPoint);

    p->updateTransform();

    bool ret = BaseApplication::frameRenderingQueued(evt);
    return ret;
}

void TutorialApplication::pause(void) {
    b->setKinematic(true);
    pauseText->showText();
    endText->hideText();
    highScore->hideText();
    ps->gamePaused = true;
}


void TutorialApplication::gameOver(void) {
    // See if new High score
    bool isNewHighScore = ps->updateHighScore();

    // Set text and pause game
    std::string Score("High score: " + std::to_string(ps->getHighScore()));
    totalText->setText(Ogre::String(Score));
    ps->resetTotal();
    ps->gamePaused = true;

    // Play music
    if (isNewHighScore) {
        highScore->showText();
        endText->hideText();
        Mix_PlayChannel( -1, winnerSound, 0 );
    }
    else {
        highScore->hideText();
        endText->showText();
    }
    
    pauseText->hideText();
    ps->gameEnds = false; 
}


void TutorialApplication::reset(void) {
    b->setKinematic(true);
    b->getNode()->setPosition(Ogre::Vector3(0, 250, 0));
    b->updateTransform();
    p->getParentNode()->setPosition(Ogre::Real(0), Ogre::Real(90), Ogre::Real(0));
    p->updateTransform();
    endText->hideText();
    pauseText->hideText();
    highScore->hideText();
    ps->gameStarts = false;
    ps->gameEnds = false;
}


void TutorialApplication::changeVolume()
{
    if (!muteSound)
    {
        Mix_VolumeChunk(paddleSound, 0);
        Mix_VolumeChunk(winnerSound, 0);
        muteSound = true;
    }
    else
    {
        Mix_VolumeChunk(paddleSound, MIX_MAX_VOLUME / 2);
        Mix_VolumeChunk(winnerSound, MIX_MAX_VOLUME / 2);
        muteSound = false;
    }
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
        case OIS::KC_P      : pause();               break;
        case OIS::KC_R      : reset();               break;
        case OIS::KC_V      : changeVolume();        break;
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
    p->getParentNode()->yaw(Ogre::Degree(arg.state.X.rel * .5f));
    p->getNode()->pitch(Ogre::Degree(-arg.state.Y.rel * .25f));

    while (p->getNode()->getOrientation().getPitch().valueDegrees() > 0) {
        p->getNode()->pitch(Ogre::Radian(-0.01f));
    }
    while (p->getNode()->getOrientation().getPitch().valueDegrees() < -30) {
        p->getNode()->pitch(Ogre::Radian(0.01f));
    }

    //cout << "Pitch : " << p->getNode()->getOrientation().getPitch().valueRadians() << ", Yaw : " << p->getParentNode()->getOrientation().getYaw().valueRadians() << endl;

    camNode->translate(Ogre::Vector3(0,0,arg.state.Z.rel));

    while (camNode->getPosition().z > 800.f) {
        camNode->translate(Ogre::Vector3(0, 0, -1.f));
    }
    while (camNode->getPosition().z < 500.f) {
        camNode->translate(Ogre::Vector3(0, 0, 1.f));
    }


    // cout << "Pitch : " << p->getNode()->getOrientation().getPitch().valueRadians() << ", Yaw : " << p->getParentNode()->getOrientation().getYaw().valueRadians() << endl;


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