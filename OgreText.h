#pragma once

#include <Overlay/OgreTextAreaOverlayElement.h>
#include <OgreStringConverter.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

class OgreText {
public:
	OgreText();
	~OgreText();
	void setPosition(float x, float y);
	void setText(Ogre::String textString);
	void setColor(float R,float G,float B,float A);
	void hideText();
	void showText();
	void resize(float size);
private:
	Ogre::TextAreaOverlayElement *textArea;
	Ogre::OverlayManager *olm;
	static int init;
	Ogre::Overlay *overlay;
	Ogre::OverlayContainer *panel ;
	Ogre::String textString;
};
