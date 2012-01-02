//============================================================================
// Name        : RTT_Ogre_3D.cpp
// Author      : Nysomin
// Copyright   : 2011, GNU GPLv3
// Description : Ogre 3D rendering engine for RealTimeTactics
//============================================================================

#include "RTT_Ogre_3D.h"
#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <OgreStringConverter.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <string>

#include <vector>


using namespace RTT;
using namespace Ogre;
using namespace std;
using namespace OIS;

//-------------------------------------------------------------------------------------
RTT_Ogre_3D::RTT_Ogre_3D(void)
	: rttRoot(0),
	rttResourcesCfg(StringUtil::BLANK),
	rttPluginsCfg(StringUtil::BLANK)
{
}
//-------------------------------------------------------------------------------------
RTT_Ogre_3D::~RTT_Ogre_3D(void)
{
	//Remove ourself as a Window listener
	WindowEventUtilities::removeWindowEventListener(rttWindow, this);
	windowClosed(rttWindow);
	//Kill Ogre
	delete rttRoot;
}

bool RTT_Ogre_3D::go(void)
{
#ifdef _DEBUG
	rttResourcesCfg = "resources_d.cfg";
    rttPluginsCfg = "plugins_d.cfg";
#else
    rttResourcesCfg = "resources.cfg";
    rttPluginsCfg = "plugins.cfg";
#endif

    // construct Ogre::Root root node
    rttRoot = new Root(rttPluginsCfg);


    // set up resources
    // Load resource paths from config file
    ConfigFile cf;
    cf.load(rttResourcesCfg);
    // Parse resource config file
    ConfigFile::SectionIterator seci = cf.getSectionIterator();

    String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }

    // configure
    // Show the configuration dialog and initialise the system
    if(!(rttRoot->restoreConfig() || rttRoot->showConfigDialog()))  // Test to see if the render window can/should be launched
    {
        return false;
    }
    rttWindow = rttRoot->initialise(true, "Real Time Tactics Render Window");

    // Set default mipmap level (note: some APIs ignore this)
    TextureManager::getSingleton().setDefaultNumMipmaps(5);
    // initialise all resource groups
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    rttSceneManager = rttRoot->createSceneManager("DefaultSceneManager"); //Create a generic screen manager

    rttCamera = rttSceneManager->createCamera("PrimaryCamera"); //Create our primary camera in our screen manager
    //The camera needs positioning
    rttCamera->setPosition(Ogre::Vector3(2.25,10.5,6.5)); // Position it at 80 in Z direction
    rttCamera->lookAt(Ogre::Vector3(2.25,0,-4)); // Look back along -Z
    rttCamera->setNearClipDistance(5); // This is how close an object can be to the camera before it is "clipped", or not rendered

    // Create one viewport, entire window, this is where the camera view is rendered
    Viewport* vp = rttWindow->addViewport(rttCamera);
    vp->setBackgroundColour(ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    rttCamera->setAspectRatio(
    Real(vp->getActualWidth()) / Real(vp->getActualHeight()));

    //START ADDING OBJECTS TO RENDER          Time for some objects for testing ***************************************

    // Set ambient light and shadows
    rttSceneManager->setAmbientLight(ColourValue(0, 0, 0));
    rttSceneManager->setShadowTechnique(SHADOWTYPE_TEXTURE_ADDITIVE);
    //Shadowmaps	EXPERIMENTAL  **********BROKEN************
    /*
    rttSceneManager->setShadowTexturePixelFormat();
    rttSceneManager->setShadowTextureSelfShadow(true);
    rttSceneManager->setShadowTextureCasterMaterial("ShadowCaster");

    rttSceneManager->setShadowTextureReceiverMaterial("ShadowReceiver");
    */

    //HACKED  Proof of concept/scratchboard

    int tileSize = 1;
    float posX = 0;
    float posY = 0;
    float posZ = 0;
    Entity* tileVector[4][4];
    string tileType = "DirtTile";
    SceneNode* nodeVector[4][4];
    Entity* blueMarine = rttSceneManager->createEntity("BlueMarine", "BlueMarine.mesh");
    blueMarine->setCastShadows(true);
    SceneNode* blueMarineNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("BlueMarine");
    blueMarineNode->attachObject(blueMarine);
    blueMarineNode->yaw(Degree(90));
    Entity* redMarine = rttSceneManager->createEntity("RedMarine", "RedMarine.mesh");
    redMarine->setCastShadows(true);
    SceneNode* redMarineNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("RedMarine", Ogre::Vector3(3*1.5,0,-3*1.732 -.866));
    redMarineNode->attachObject(redMarine);
    redMarineNode->yaw(Degree(-90));

    for(int i=0;i < 4*tileSize; i+=tileSize)//build our columns
    {
    	for(int n=0; n<4*tileSize;n+=tileSize)//build our rows
    	{
    		posZ = -n *1.732;
    		if(i%2 != 0)//test for odd
    		{
    			posZ -= .866; //steps up
    		}
    		tileVector[i][n] = rttSceneManager->createEntity(tileType + Ogre::StringConverter::toString(i) + Ogre::StringConverter::toString(n), "DirtTile.mesh", "RTT");
    		tileVector[i][n]->setCastShadows(true);
    		nodeVector[i][n] = rttSceneManager->getRootSceneNode()->createChildSceneNode(tileType + Ogre::StringConverter::toString(i) + Ogre::StringConverter::toString(n), Ogre::Vector3(i*1.5, posY,posZ));
    		nodeVector[i][n]->attachObject(tileVector[i][n]);
    	}
    }

/*
    Entity* dirtTile = rttSceneManager->createEntity("DirtTile1", "DirtTile.mesh");
    dirtTile->setCastShadows(true);
    SceneNode* dirtTileNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("DirtTile1");
    dirtTileNode->attachObject(dirtTile);

    Entity* dirtTile2 = rttSceneManager->createEntity("DirtTile2", "DirtTile.mesh");
    dirtTile2->setCastShadows(true);
    SceneNode* dirtTile2Node = rttSceneManager->getRootSceneNode()->createChildSceneNode("DirtTile2", Ogre::Vector3(1.5,0,-.866));
    dirtTile2Node->attachObject(dirtTile2);

    Entity* dirtTile3 = rttSceneManager->createEntity("DirtTile3", "DirtTile.mesh");
    dirtTile3->setCastShadows(true);
    SceneNode* dirtTile3Node = rttSceneManager->getRootSceneNode()->createChildSceneNode("DirtTile3", Ogre::Vector3(3,0,0));
    dirtTile3Node->attachObject(dirtTile3);

    Entity* blueMarine = rttSceneManager->createEntity("BlueMarine", "BlueMarine.mesh");
    blueMarine->setCastShadows(true);
    SceneNode* blueMarineNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("BlueMarine");
    blueMarineNode->attachObject(blueMarine);
*/

    //end HACK
    Entity* groundPlane = rttSceneManager->createEntity("Ground", "Plane.mesh");
    groundPlane->setMaterialName("Claygreen");
    groundPlane->setCastShadows(false);
    SceneNode* groundPlaneNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("Ground", Ogre::Vector3(2.25,0,0));
    groundPlaneNode->attachObject(groundPlane);
    //groundPlaneNode->scale(25,25,25);


    // Create a light
    Light* mainLight = rttSceneManager->createLight("MainLight");
    mainLight->setType(Light::LT_POINT);
    //mainLight->mCastShadows=true;
    mainLight->setPosition(20,30,15);
    mainLight->setCastShadows(true);

    rttSceneManager->setSkyDome(true, "Examples/CloudySky", 2, 3);

    //END OBJECTS       ************************************************************************************************

    //OIS Input system startup
    LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    ParamList pl;
    size_t windowHnd = 0;
    ostringstream windowHndStr;

    rttWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(make_pair(string("WINDOW"), windowHndStr.str()));

    rttInputManager = InputManager::createInputSystem( pl );
    rttKeyboard = static_cast<Keyboard*>(rttInputManager->createInputObject(OISKeyboard, false ));
    rttMouse = static_cast<Mouse*>(rttInputManager->createInputObject(OISMouse, false ));

    windowResized(rttWindow);    //Set initial mouse clipping size
    WindowEventUtilities::addWindowEventListener(rttWindow, this);    //Register as a Window listener

    //where the magic happens:  Render loop!!!
    /*
    while(true)
    {
        // Pump window messages for nice behaviour
        WindowEventUtilities::messagePump();

        if(rttWindow->isClosed())
        {
            return false;
        }

        // Render a frame
        if(!rttRoot->renderOneFrame()) return false;
    }
    */

    rttRoot->addFrameListener(this);

    rttRoot->startRendering();

    return true;
}

//Adjust mouse clipping area
void RTT_Ogre_3D::windowResized(RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const MouseState &ms = rttMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void RTT_Ogre_3D::windowClosed(RenderWindow* rw)
{
    //Only close for window that created OIS
    if( rw == rttWindow )
    {
        if( rttInputManager )
        {
            rttInputManager->destroyInputObject( rttMouse );
            rttInputManager->destroyInputObject( rttKeyboard );

            InputManager::destroyInputSystem(rttInputManager);
            rttInputManager = 0;
        }
    }
}

bool RTT_Ogre_3D::frameRenderingQueued(const FrameEvent& evt)
{
    if(rttWindow->isClosed())
        return false;

    //Need to capture/update each device
    rttKeyboard->capture();
    rttMouse->capture();

    if(rttKeyboard->isKeyDown(KC_ESCAPE))//Quit
    {
        return false;
    }
    if(rttKeyboard->isKeyDown(KC_NUMPAD4))//Move North West
    {
    	LogManager::getSingletonPtr()->logMessage("Move North West");
    }
    if(rttKeyboard->isKeyDown(KC_NUMPAD5))//Move North
    {
    	LogManager::getSingletonPtr()->logMessage("Move North");
    }
    if(rttKeyboard->isKeyDown(KC_NUMPAD6))//Move North East
    {
    	LogManager::getSingletonPtr()->logMessage("Move North East");
    }
    if(rttKeyboard->isKeyDown(KC_NUMPAD1))//Move South West
    {
    	LogManager::getSingletonPtr()->logMessage("Move South West");
    }
    if(rttKeyboard->isKeyDown(KC_NUMPAD2))//Move South
    {
    	LogManager::getSingletonPtr()->logMessage("Move South");
    }
    if(rttKeyboard->isKeyDown(KC_NUMPAD3))//Move South East
    {
    	LogManager::getSingletonPtr()->logMessage("Move South East");
    }
    return true;
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])//*************************************************************************FOUND MAIN!!!************************************************************************
#endif
    {
        // Create application object
        RTT_Ogre_3D app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
