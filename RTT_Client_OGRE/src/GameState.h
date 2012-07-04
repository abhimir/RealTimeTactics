//============================================================================
// Name        : GameState.hpp
// Author      : Mark Petro
// Copyright   : 2011, GNU GPLv3
// Description : Built from the Advanced OGRE Framework tutorial found here:
//	http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Advanced+Ogre+Framework&structure=Tutorials
//============================================================================

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "AppState.h"
#include "RTT_Ogre_Unit.h"
#include "RTT_Ogre_Player.h"

#include "GameCommands.h"
#include "GameEvents.h"

//#include "DotSceneLoader.hpp"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>

enum QueryFlags
{
	OGRE_HEAD_MASK	= 1<<0,
	CUBE_MASK		= 1<<1
};

class GameState : public AppState
{
public:
	GameState(void);

	DECLARE_APPSTATE_CLASS(GameState)

	void enter();
	void createScene();
	void exit();
	bool pause();
	void resume();

	void moveCamera();
	void getInput();
	void buildGUI();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	void onLeftPressed(const OIS::MouseEvent &evt);
	//void itemSelected(OgreBites::SelectMenu* menu);
	bool onExitButtonGame(const CEGUI::EventArgs &args);

	void setBufferedMode();
	void setUnbufferedMode();

	void update(double timeSinceLastFrame);

	void moveUnit(RTT::RTT_Ogre_Unit &arg);
	void moveCursor(const RTT::Direction &arg);
	void showRange(RTT::RTT_Ogre_Unit &arg, bool &arg2);
	void makeMove(RTT::RTT_Ogre_Unit &arg);

	void buildUnits();

	private:
	Ogre::SceneNode *m_pOgreHeadNode;
	Ogre::Entity *m_pOgreHeadEntity;
	Ogre::MaterialPtr m_pOgreHeadMat;
	Ogre::MaterialPtr m_pOgreHeadMatHigh;

	//OgreBites::ParamsPanel *m_pDetailsPanel;
	bool m_bQuit;

	Ogre::Vector3 m_TranslateVector;
	Ogre::Real m_MoveSpeed;
	Ogre::Degree m_RotateSpeed;
	float m_MoveScale;
	Ogre::Degree m_RotScale;

	Ogre::RaySceneQuery *m_pRSQ;
	Ogre::SceneNode *m_pCurrentObject;
	Ogre::Entity *m_pCurrentEntity;
	bool m_bLMouseDown, m_bRMouseDown;

	//TODO: these two may be the same
	bool m_bSettingsMode;
	bool m_bChatMode;

	bool m_isMoving;
	RTT::RTT_Ogre_Player m_mainPlayer;
	RTT::RTT_Ogre_Unit m_playerCursor;
	CEGUI::Window *m_pMainWnd;
	CEGUI::Window *m_pChatWnd;
};

#endif
