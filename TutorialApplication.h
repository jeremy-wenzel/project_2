/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
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

#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"
#include "ball.h"
#include "Wall.h"
#include "paddle.h"
#include "Room.h"
#include "Simulator.h"
#include <vector>

class TutorialApplication : public BaseApplication {
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

protected:
    virtual void createScene(void);
    virtual void createFrameListener(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
    bool soundInit(void);
    void pause(void);
    void reset(void);
    void gameOver(void);
    void mute(void);

private:
	ball *b;
	Paddle *p;
  Ogre::SceneNode *camNode;
	Simulator *sim;
  Room *room;
  bool gameStarts;
  PointSystem *ps;
  bool muteSound;

  bool doMoveForward;
  bool doMoveBackward;
  bool doMoveLeft;
  bool doMoveRight;
  bool doMoveDown;
  bool doMoveUp;
  bool doMoveFast;

  OgreText *totalText;
  OgreText *currentText;
  OgreText *pauseText;
  OgreText *endText;
  OgreText *highScore;

  Mix_Music *music;
  Mix_Chunk *winnerSound;
  Mix_Chunk *paddleSound;
  bool musicPlaying;
};

#endif