#include "OgreText.h"


int OgreText::init = 0;
OgreText::OgreText()
{
	olm=Ogre::OverlayManager::getSingletonPtr();
	if (init == 0) 
	{
		panel = static_cast<Ogre::OverlayContainer*>(olm->createOverlayElement("Panel","GUI"));
		panel->setMetricsMode(Ogre::GMM_PIXELS);
        panel->setPosition(0,0);
        panel->setDimensions(1.0f,1.0f);
        overlay=olm->create("GUI_OVERLAY");
        overlay->add2D(panel);
	}
	init ++;
	textString = "element_" + Ogre::StringConverter::toString(init);
    overlay = olm->getByName("GUI_OVERLAY");
    panel = static_cast<Ogre::OverlayContainer*>(olm->getOverlayElement("GUI"));
    textArea = static_cast<Ogre::TextAreaOverlayElement*>(olm->createOverlayElement("TextArea", textString));
    panel->addChild(textArea);
    overlay->show();
}


OgreText::~OgreText()
{
	textString = "element_" + Ogre::StringConverter::toString(init);
	olm->destroyOverlayElement(textString);
    init --;
    if(init == 0)
    {
        olm->destroyOverlayElement("GUI");
        olm->destroy("GUI_OVERLAY");
    }
}

void OgreText::setPosition(float x, float y)
{
	textArea->setPosition(x, y);
}

void OgreText::setText(Ogre::String string)
{
	textArea->setCaption(string);
    textArea->setDimensions(1.0f,1.0f);
    textArea->setMetricsMode(Ogre::GMM_RELATIVE);
    textArea->setFontName("MyFont");
    textArea->setCharHeight(0.3f);
}

void OgreText::setColor(float R,float G,float B,float A)
{
    textArea->setColour(Ogre::ColourValue(R, G, B, A));
}
