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

//---------------------------------------------------------------------------

class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);

protected:
    virtual void createScene(void);
    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    bool soundInit(void);
    virtual void createFrameListener(void);
    virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);

private:
	ball *b;
	Paddle *p;
  Ogre::SceneNode *camNode;
	Simulator *sim;
  Room *room;
  int score;
  bool gameStarts;
  PointSystem *ps;

  bool doMoveForward;
  bool doMoveBackward;
  bool doMoveLeft;
  bool doMoveRight;

  bool doMoveUp;
  bool doMoveDown;

  //Experimental
  bool doMoveFast;

  Mix_Music *music;
  bool musicPlaying;
};

//---------------------------------------------------------------------------

#endif // #ifndef __TutorialApplication_h_

//---------------------------------------------------------------------------
