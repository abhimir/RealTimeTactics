/*
 * RTT_Ogre_Player.h
 *
 *  Created on: Feb 10, 2012
 *      Author: mark
 */

#ifndef RTT_OGRE_PLAYER_H_
#define RTT_OGRE_PLAYER_H_


#include "RTT_Ogre_Unit.h"
#include "RTT_Ogre_Base.h"
#include "Enums.h"

#include <vector>

namespace RTT
{
	class RTT_Ogre_Player
	{
	public:
		RTT_Ogre_Player();
		virtual ~RTT_Ogre_Player();
		std::vector<RTT_Ogre_Unit*> units;
		uint currentUnit;
		RTT::TeamNumber Team;
	};

}

#endif /* RTT_OGRE_PLAYER_H_ */
