noinst_HEADERS = TutorialApplication.h BaseApplication.h BulletContactCallback.h GameObject.h OgreMotionState.h Simulator.h Wall.h ball.h paddle.h

bin_PROGRAMS = assignment2
assignment2_CPPFLAGS = -I$(top_srcdir)
assignment2_SOURCES = TutorialApplication.cpp BaseApplication.cpp GameObject.cpp OgreMotionState.cpp Simulator.cpp Wall.cpp ball.cpp paddle.h
assignment2_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS)
assignment2_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS)
assignment2_LDFLAGS = -lOgreOverlay -lboost_system

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
