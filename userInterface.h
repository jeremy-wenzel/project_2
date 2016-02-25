#pragma once


#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

struct MyUserInterface {
	CEGUI::OgreRenderer* mRenderer;
	MyUserInterface();
};

MyUserInterface::MyUserInterface() 
{
	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
	CEGUI::Imageset::setDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
}