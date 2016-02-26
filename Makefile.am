noinst_HEADERS = BaseApplication.h BulletContactCallback.h GameObject.h OgreMotionState.h Room.h Simulator.h TutorialApplication.h Wall.h ball.h userInterface.h

bin_PROGRAMS = assignment2
assignment2_CPPFLAGS = -I$(top_srcdir) -std=c++11 -I/usr/include/SDL 
assignment2_SOURCES = BaseApplication.cpp GameObject.cpp OgreMotionState.cpp Room.cpp Simulator.cpp TutorialApplication.cpp Wall.cpp ball.cpp
assignment2_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(CEGUI_LIBS)  $(CEGUI_OGRE_LIBS)
assignment2_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(CEGUI_LIBS) $(CEGUI_OGRE_LIBS)
assignment2_LDFLAGS = -lOgreOverlay -lboost_system
assignment2_LDFLAGS += -lSDL -lSDL_mixer

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign

