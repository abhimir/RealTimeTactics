//============================================================================
// Name        : RTT_Ogre_Game.cpp
// Author      : Nysomin
// Copyright   : 2012, GNU GPLv3
// Description : Ogre 3D rendering engine game file for RealTimeTactics
//               Based on Ogre Tutorial framework
//============================================================================

#include "RTT_Ogre_Game.h"

#include <string>
#include <vector>

using namespace Ogre;
using namespace std;
using namespace OIS;
using namespace RTT;

//-------------------------------------------------------------------------------------
RTT_Ogre_Game::RTT_Ogre_Game(void):
		mainPlayer()
{
}
//-------------------------------------------------------------------------------------
RTT_Ogre_Game::~RTT_Ogre_Game(void)
{
}

//-------------------------------------------------------------------------------------
void RTT_Ogre_Game::moveUnit(const RTT::Direction& moveDirection, RTT_Ogre_Unit& toMove)
{
	Ogre::Vector3 playerLocChange = toMove.unitNode->getPosition();
	int facingDirection = 0;
	switch(moveDirection)
	{
	case EAST:
		LogManager::getSingletonPtr()->logMessage("Moving: East");
		toMove.locationX++;
		facingDirection = 90;
		break;
	case NORTHWEST:
		LogManager::getSingletonPtr()->logMessage("Moving: North West");
		if(toMove.locationY%2 != 0)
			toMove.locationX--;
		toMove.locationY++;
		facingDirection = -150;
		break;
	case NORTHEAST:
		LogManager::getSingletonPtr()->logMessage("Moving: North East");
		if(toMove.locationY%2 == 0)
			toMove.locationX++;
		toMove.locationY++;
		facingDirection = 150;
		break;
	case WEST:
		LogManager::getSingletonPtr()->logMessage("Moving: West");
		toMove.locationX--;
		facingDirection = -90;
		break;
	case SOUTHWEST:
		LogManager::getSingletonPtr()->logMessage("Moving: South West");
		if(toMove.locationY%2 != 0)
			toMove.locationX--;
		toMove.locationY--;
		facingDirection = -30;
		break;
	case SOUTHEAST:
		LogManager::getSingletonPtr()->logMessage("Moving: South East");
		if(toMove.locationY%2 == 0)
			toMove.locationX++;
		toMove.locationY--;
		facingDirection = 30;
		break;
	default:
		break;
	}

	LogManager::getSingletonPtr()->logMessage("Location: " + Ogre::StringConverter::toString(toMove.locationX) +"," + Ogre::StringConverter::toString(toMove.locationY));
	if(toMove.locationY%2 != 0)
	{
		//LogManager::getSingletonPtr()->logMessage("Real Location: " + Ogre::StringConverter::toString(unitX*1.732-.866) +"," + Ogre::StringConverter::toString(-unitY*1.5));
		toMove.unitNode->setPosition(Ogre::Vector3(toMove.locationX*1.732-.866,0,-toMove.locationY*1.5));
	}
	else
	{
		//LogManager::getSingletonPtr()->logMessage("Real Location: " + Ogre::StringConverter::toString(unitX*1.732) +"," + Ogre::StringConverter::toString(-unitY*1.5));
		toMove.unitNode->setPosition(Ogre::Vector3(toMove.locationX*1.732,0,-toMove.locationY*1.5));
	}
	toMove.unitNode->resetOrientation();
	toMove.unitNode->yaw(Degree(facingDirection));//Make sure we are facing the right way

}

//Buffered keyboard input and game keybindings
bool RTT_Ogre_Game::keyPressed( const KeyEvent& evt )
{
	switch (evt.key)
	{
	case KC_ESCAPE:
		LogManager::getSingletonPtr()->logMessage("Quitting!!!");
	    rttShutDown = true;
	    break;
	case KC_NUMPAD7://Move North West
		moveUnit(NORTHWEST, mainPlayer);
		break;
	case KC_NUMPAD4://Move North EDIT::::::::WEST!
		moveUnit(WEST, mainPlayer);
		break;
	case KC_NUMPAD9://Move North East
		moveUnit(NORTHEAST, mainPlayer);
		break;
	case KC_NUMPAD1://Move South West
		moveUnit(SOUTHWEST, mainPlayer);
		break;
	case KC_NUMPAD6://Move South  EDIT:::::::::EAST!
		moveUnit(EAST, mainPlayer);
		break;
	case KC_NUMPAD3://Move South East
		moveUnit(SOUTHEAST, mainPlayer);
		break;
	default:
	    break;
	}
	return true;
}

void RTT_Ogre_Game::buildUnits(void)
{
    mainPlayer.unitEntity = rttSceneManager->createEntity("BlueMarine", "ColorMarine.mesh");
    mainPlayer.unitEntity->setCastShadows(true);
    mainPlayer.unitEntity->setMaterialName("ColorMarine");
    mainPlayer.unitNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("BlueMarine");
    mainPlayer.unitNode->attachObject(mainPlayer.unitEntity);
    mainPlayer.unitNode->yaw(Degree(150));
    mainPlayer.locationX = 0;
    mainPlayer.locationY = 0;
}

void RTT_Ogre_Game::createScene(void)
{
	// Set ambient light and shadows
    rttSceneManager->setAmbientLight(ColourValue(0, 0, 0));
    rttSceneManager->setShadowTechnique(SHADOWTYPE_TEXTURE_ADDITIVE);
    //Shadowmaps	EXPERIMENTAL
    rttSceneManager->setShadowTexturePixelFormat(Ogre::PF_FLOAT32_R);
    rttSceneManager->setShadowTextureSelfShadow(true);
    //rttSceneManager->setShadowCasterRenderBackFaces(false);
    rttSceneManager->setShadowTextureCasterMaterial("Ogre/DepthShadowmap/Caster/Float");
    //rttSceneManager->setShadowTextureReceiverMaterial("Ogre/DepthShadowmap/BasicTemplateMaterial");
    rttSceneManager->setShadowTextureSize(1024);

    buildUnits();

    //HACKED  Proof of concept/scratchboard

    int tileSize = 1;
    float posX = 0;
    float posY = 0;
    float posZ = 0;
    Entity* tileVector[8][8];
    string tileType = "DirtTile";
    SceneNode* nodeVector[8][8];
    //Entity* blueMarine = rttSceneManager->createEntity("BlueMarine", "BlueMarine.mesh");
    //blueMarine->setCastShadows(true);
    //SceneNode* blueMarineNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("BlueMarine");
    //blueMarineNode->attachObject(blueMarine);
    //blueMarineNode->yaw(Degree(90));
    Entity* redMarine = rttSceneManager->createEntity("RedMarine", "RedMarine.mesh");
    redMarine->setCastShadows(true);
    SceneNode* redMarineNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("RedMarine", Ogre::Vector3(7*1.732 -.866,0,-7*1.5));
    redMarineNode->attachObject(redMarine);
    redMarineNode->yaw(Degree(-30));

    for(int x=0;x < 8*tileSize; x+=tileSize)//build our columns
    {
    	for(int y=0; y<8*tileSize;y+=tileSize)//build our rows
    	{
    		posX = x *1.732;
    		if(y%2 != 0)//test for odd
    		{
    			posX -= .866; //steps over
    		}
    		tileVector[x][y] = rttSceneManager->createEntity(tileType + Ogre::StringConverter::toString(x) + Ogre::StringConverter::toString(y), "DirtTile.mesh", "RTT");
    		tileVector[x][y]->setCastShadows(true);
    		nodeVector[x][y] = rttSceneManager->getRootSceneNode()->createChildSceneNode(tileType + Ogre::StringConverter::toString(x) + Ogre::StringConverter::toString(y), Ogre::Vector3(posX, posY, -y*1.5));
    		nodeVector[x][y]->attachObject(tileVector[x][y]);
    	}
    }

	Entity* hescoTest = rttSceneManager->createEntity("Hesco", "Hesco.mesh");
	hescoTest->setCastShadows(true);
	SceneNode* hescoNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("Hesco", Ogre::Vector3(2*1.732 -.866,-.5,-1*1.5));
	hescoNode->attachObject(hescoTest);
	hescoNode->yaw(Degree(90));
	hescoTest = rttSceneManager->createEntity("Hesco2", "Hesco.mesh");
	hescoTest->setCastShadows(true);
	hescoNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("Hesco2", Ogre::Vector3(3*1.732 -.866,-1,-1*1.5));
	hescoNode->attachObject(hescoTest);
	hescoNode->yaw(Degree(90));
	hescoTest = rttSceneManager->createEntity("Hesco3", "Hesco.mesh");
	hescoTest->setCastShadows(true);
	hescoNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("Hesco3", Ogre::Vector3(4*1.732 -.866,-1.5,-1*1.5));
	hescoNode->attachObject(hescoTest);
	hescoNode->yaw(Degree(90));

	hescoTest = rttSceneManager->createEntity("Hesco4", "Hesco.mesh");
	hescoTest->setCastShadows(true);
	hescoNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("Hesco4", Ogre::Vector3(5*1.732 ,0,-6*1.5));
	hescoNode->attachObject(hescoTest);
	hescoNode->yaw(Degree(30));
	hescoTest = rttSceneManager->createEntity("Hesco5", "Hesco.mesh");
	hescoTest->setCastShadows(true);
	hescoNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("Hesco5", Ogre::Vector3(6*1.732 -.866,-.5,-5*1.5));
	hescoNode->attachObject(hescoTest);
	hescoNode->yaw(Degree(30));
	hescoTest = rttSceneManager->createEntity("Hesco6", "Hesco.mesh");
	hescoTest->setCastShadows(true);
	hescoNode = rttSceneManager->getRootSceneNode()->createChildSceneNode("Hesco6", Ogre::Vector3(6*1.732 ,-1,-4*1.5));
	hescoNode->attachObject(hescoTest);
	hescoNode->yaw(Degree(30));

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

    //END OBJECTS       ************************************************************************************************
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
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        RTT_Ogre_Game app;

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
