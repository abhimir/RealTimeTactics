//============================================================================
// Name        : Unit.h
// Author      : AltF4
// Copyright   : 2011, GNU GPLv3
// Description : Message class pertaining to the Match Lobby (not main lobby)
//============================================================================

#include "MatchLobbyMessage.h"
#include "string.h"

using namespace std;
using namespace RTT;

MatchLobbyMessage::~MatchLobbyMessage()
{

}

MatchLobbyMessage::MatchLobbyMessage()
{

}

MatchLobbyMessage::MatchLobbyMessage(char *buffer, uint length)
{
	if( length < MESSAGE_MIN_SIZE )
	{
		return;
	}

	serializeError = false;

	//Copy the message type
	memcpy(&type, buffer, MESSAGE_MIN_SIZE);
	buffer += MESSAGE_MIN_SIZE;

	switch(type)
	{
		//*********************
		//	MatchLobbyMessage
		// (Initiated by client)
		//*********************
		//Leaving a match you're in
		case MATCH_LEAVE_NOTIFICATION:
		{
			//Uses: 1) Message Type
			uint expectedSize = MESSAGE_MIN_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			break;
		}
		case MATCH_LEAVE_ACKNOWLEDGE:
		{
			//Uses: 1) Message Type
			uint expectedSize = MESSAGE_MIN_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			break;
		}
		case CHANGE_TEAM_REQUEST:
		{
			//Uses: 1) Message Type
			//		2) New team
			//		3) Player ID to change
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(newTeam) + sizeof(playerID);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//new team
			memcpy(&newTeam, buffer, sizeof(newTeam));
			buffer += sizeof(newTeam);
			//new team
			memcpy(&playerID, buffer, sizeof(playerID));
			buffer += sizeof(playerID);

			break;
		}
		case CHANGE_TEAM_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//new team
			memcpy(&changeAccepted, buffer, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}
		case START_MATCH_REQUEST:
		{
			//Uses: 1) Message Type
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			break;
		}
		case START_MATCH_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//new team
			memcpy(&changeAccepted, buffer, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}
		case CHANGE_COLOR_REQUEST:
		{
			//Uses: 1) Message Type
			//		2) New Color
			//		3) Player ID
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(newColor) + sizeof(playerID);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//new team
			memcpy(&newColor, buffer, sizeof(newColor));
			buffer += sizeof(newColor);
			//Player to change
			memcpy(&playerID, buffer, sizeof(playerID));
			buffer += sizeof(playerID);

			break;
		}
		case CHANGE_COLOR_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//new team
			memcpy(&changeAccepted, buffer, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}
		case CHANGE_MAP_REQUEST:
		{
			//Uses: 1) Message Type
			//		2) New map data
			uint expectedSize = MESSAGE_MIN_SIZE + MAP_DESCR_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//new map
			memcpy(&mapDescription.name, buffer, MAP_NAME_LEN);
			buffer += sizeof(mapDescription);
			memcpy(&mapDescription.length, buffer, sizeof(uint));
			buffer += sizeof(uint);
			memcpy(&mapDescription.width, buffer, sizeof(uint));
			buffer += sizeof(uint);
			break;
		}
		case CHANGE_MAP_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//new team
			memcpy(&changeAccepted, buffer, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}
		case CHANGE_VICTORY_COND_REQUEST:
		{
			//Uses: 1) Message Type
			//		2) New map data
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(newVictCond);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//new team
			memcpy(&newVictCond, buffer, sizeof(newVictCond));
			buffer += sizeof(newVictCond);

			break;
		}
		case CHANGE_VICTORY_COND_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//new team
			memcpy(&changeAccepted, buffer, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}
		case CHANGE_GAME_SPEED_REQUEST:
		{
			//Uses: 1) Message Type
			//		2) New map data
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(newSpeed);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//new team
			memcpy(&newSpeed, buffer, sizeof(newSpeed));
			buffer += sizeof(newSpeed);

			break;
		}
		case CHANGE_GAME_SPEED_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//new team
			memcpy(&changeAccepted, buffer, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}
		case CALLBACK_REGISTER:
		{
			//Uses: 1) Message Type
			//		2) playerID
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(playerID);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//PlayerID
			memcpy(&playerID, buffer, sizeof(playerID));
			buffer += sizeof(playerID);

			break;
		}
		case KICK_PLAYER_REQUEST:
		{
			//Uses: 1) Message Type
			//		2) Player ID
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(playerID);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//new team
			memcpy(&playerID, buffer, sizeof(playerID));
			buffer += sizeof(playerID);

			break;
		}
		case KICK_PLAYER_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//new team
			memcpy(&changeAccepted, buffer, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}

		//************************
		//	MatchLobbyMessage
		// (Initiated by server)
		//************************
		case TEAM_CHANGED_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) New team
			//		3) Player ID
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(newTeam) + sizeof(playerID);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//New team
			memcpy(&newTeam, buffer, sizeof(newTeam));
			buffer += sizeof(newTeam);
			//Player ID that changed
			memcpy(&playerID, buffer, sizeof(playerID));
			buffer += sizeof(playerID);

			break;
		}
		case TEAM_CHANGED_ACK:
		{
			//Uses: 1) Message Type
			uint expectedSize = MESSAGE_MIN_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			break;
		}
		case KICKED_FROM_MATCH_NOTIFICATION:
		{
			//Uses: 1) Message Type
			uint expectedSize = MESSAGE_MIN_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			break;
		}
		case KICKED_FROM_MATCH_ACK:
		{
			//Uses: 1) Message Type
			uint expectedSize = MESSAGE_MIN_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			break;
		}
		case PLAYER_LEFT_MATCH_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) Player ID
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(playerID);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//Player ID that left
			memcpy(&playerID, buffer, sizeof(playerID));
			buffer += sizeof(playerID);

			break;
		}
		case PLAYER_LEFT_MATCH_ACK:
		{
			//Uses: 1) Message Type
			uint expectedSize = MESSAGE_MIN_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			break;
		}
		case PLAYER_JOINED_MATCH_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) Player Description
			uint expectedSize = MESSAGE_MIN_SIZE + PLAYER_DESCR_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//Player ID that joined
			memcpy(&playerDescription.name, buffer, PLAYER_NAME_SIZE);
			buffer += PLAYER_NAME_SIZE;
			memcpy(&playerDescription.ID, buffer, sizeof(uint));
			buffer += sizeof(uint);
			memcpy(&playerDescription.color, buffer, sizeof(enum TeamColor));
			buffer += sizeof(enum TeamColor);
			memcpy(&playerDescription.team, buffer, sizeof(enum TeamNumber));
			buffer += sizeof(enum TeamNumber);


			break;
		}
		case PLAYER_JOINED_MATCH_ACK:
		{
			//Uses: 1) Message Type
			uint expectedSize = MESSAGE_MIN_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			break;
		}
		case COLOR_CHANGED_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) Player ID
			//		3) New color
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(playerID) + sizeof(newColor);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//Player ID
			memcpy(&playerID, buffer, sizeof(playerID));
			buffer += sizeof(playerID);
			//New Color
			memcpy(&newColor, buffer, sizeof(newColor));
			buffer += sizeof(newColor);

			break;
		}
		case COLOR_CHANGED_ACK:
		{
			//Uses: 1) Message Type
			uint expectedSize = MESSAGE_MIN_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			break;
		}
		case MAP_CHANGED_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) Map Description
			uint expectedSize = MESSAGE_MIN_SIZE + MAP_DESCR_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//Map description
			memcpy(&mapDescription.name, buffer, MAP_NAME_LEN);
			buffer += sizeof(mapDescription);
			memcpy(&mapDescription.length, buffer, sizeof(uint));
			buffer += sizeof(uint);
			memcpy(&mapDescription.width, buffer, sizeof(uint));
			buffer += sizeof(uint);

			break;
		}
		case MAP_CHANGED_ACK:
		{
			//Uses: 1) Message Type
			uint expectedSize = MESSAGE_MIN_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			break;
		}
		case GAME_SPEED_CHANGED_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) Game speed
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(newSpeed);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//Map description
			memcpy(&newSpeed, buffer, sizeof(newSpeed));
			buffer += sizeof(newSpeed);

			break;
		}
		case GAME_SPEED_CHANGED_ACK:
		{
			//Uses: 1) Message Type
			uint expectedSize = MESSAGE_MIN_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			break;
		}
		case VICTORY_COND_CHANGED_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) Victory Condition
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(newVictCond);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//Victory condition
			memcpy(&newVictCond, buffer, sizeof(newVictCond));
			buffer += sizeof(newVictCond);

			break;
		}
		case VICTORY_COND_CHANGED_ACK:
		{
			//Uses: 1) Message Type
			uint expectedSize = MESSAGE_MIN_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			break;
		}
		case MATCH_START_NOTIFICATION:
		{
			//Uses: 1) Message Type
			uint expectedSize = MESSAGE_MIN_SIZE;
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			break;
		}
		case MATCH_START_ACK:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			uint expectedSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			if( length != expectedSize)
			{
				serializeError = true;
				return;
			}

			//Map description
			memcpy(&changeAccepted, buffer, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}


		default:
		{
			//Error
			return;
		}
	}
}


char *MatchLobbyMessage::Serialize(uint *length)
{
	char *buffer, *originalBuffer;
	uint messageSize;
	switch(type)
	{
		//*********************
		//	MatchLobbyMessage
		// (Initiated by client)
		//*********************
		//Leaving a match you're in
		case MATCH_LEAVE_NOTIFICATION:
		{
			//Uses: 1) Message Type
			messageSize = MESSAGE_MIN_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			break;
		}
		case MATCH_LEAVE_ACKNOWLEDGE:
		{
			//Uses: 1) Message Type
			messageSize = MESSAGE_MIN_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			break;
		}
		case CHANGE_TEAM_REQUEST:
		{
			//Uses: 1) Message Type
			//		2) New team
			//		3) Player ID to change
			messageSize = MESSAGE_MIN_SIZE + sizeof(newTeam) + sizeof(playerID);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//Page Count
			memcpy(buffer, &newTeam, sizeof(newTeam));
			buffer += sizeof(newTeam);
			//PlayerID
			memcpy(buffer, &playerID, sizeof(playerID));
			buffer += sizeof(playerID);

			break;
		}
		case CHANGE_TEAM_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			messageSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//Change accepted
			memcpy(buffer, &changeAccepted, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}
		case START_MATCH_REQUEST:
		{
			//Uses: 1) Message Type
			messageSize = MESSAGE_MIN_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			break;
		}
		case START_MATCH_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			messageSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//Change accepted
			memcpy(buffer, &changeAccepted, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}
		case CHANGE_COLOR_REQUEST:
		{
			//Uses: 1) Message Type
			//		2) new Color
			//		3) Player ID
			messageSize = MESSAGE_MIN_SIZE + sizeof(newColor) + sizeof(playerID);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//New color
			memcpy(buffer, &newColor, sizeof(newColor));
			buffer += sizeof(newColor);
			//Player ID
			memcpy(buffer, &playerID, sizeof(playerID));
			buffer += sizeof(playerID);

			break;
		}
		case CHANGE_COLOR_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			messageSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//Change accepted
			memcpy(buffer, &changeAccepted, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}
		case CHANGE_MAP_REQUEST:
		{
			//Uses: 1) Message Type
			//		2) New Map
			messageSize = MESSAGE_MIN_SIZE + MAP_DESCR_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			//New color
			memcpy(buffer, &mapDescription.name, MAP_NAME_LEN);
			buffer += sizeof(mapDescription);
			memcpy(buffer, &mapDescription.length, sizeof(uint));
			buffer += sizeof(uint);
			memcpy(buffer, &mapDescription.width, sizeof(uint));
			buffer += sizeof(uint);

			break;
		}
		case CHANGE_MAP_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			messageSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//Change accepted
			memcpy(buffer, &changeAccepted, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}
		case CHANGE_VICTORY_COND_REQUEST:
		{
			//Uses: 1) Message Type
			//		2) New victory condition
			messageSize = MESSAGE_MIN_SIZE + sizeof(newVictCond);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//New color
			memcpy(buffer, &newVictCond, sizeof(newVictCond));
			buffer += sizeof(newVictCond);

			break;
		}
		case CHANGE_VICTORY_COND_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			messageSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//Change accepted
			memcpy(buffer, &changeAccepted, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}
		case CHANGE_GAME_SPEED_REQUEST:
		{
			//Uses: 1) Message Type
			//		2) New Game Speed
			messageSize = MESSAGE_MIN_SIZE + sizeof(newSpeed);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//New color
			memcpy(buffer, &newSpeed, sizeof(newSpeed));
			buffer += sizeof(newSpeed);

			break;
		}
		case CHANGE_GAME_SPEED_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			messageSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//Change accepted
			memcpy(buffer, &changeAccepted, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}
		case CALLBACK_REGISTER:
		{
			//Uses: 1) Message Type
			//		2) PlayerID
			messageSize = MESSAGE_MIN_SIZE + sizeof(playerID);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//New color
			memcpy(buffer, &playerID, sizeof(playerID));
			buffer += sizeof(playerID);

			break;
		}
		case KICK_PLAYER_REQUEST:
		{
			//Uses: 1) Message Type
			//		2) Player ID
			messageSize = MESSAGE_MIN_SIZE + sizeof(playerID);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//New color
			memcpy(buffer, &playerID, sizeof(playerID));
			buffer += sizeof(playerID);

			break;
		}
		case KICK_PLAYER_REPLY:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			messageSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//Change accepted
			memcpy(buffer, &changeAccepted, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}

		//************************
		//	MatchLobbyMessage
		// (Initiated by server)
		//************************
		case TEAM_CHANGED_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) New team
			//		3) Player ID
			messageSize = MESSAGE_MIN_SIZE + sizeof(newTeam) + sizeof(playerID);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//New Team
			memcpy(buffer, &newTeam, sizeof(newTeam));
			buffer += sizeof(newTeam);
			//Player ID
			memcpy(buffer, &playerID, sizeof(playerID));
			buffer += sizeof(playerID);

			break;
		}
		case TEAM_CHANGED_ACK:
		{
			//Uses: 1) Message Type
			messageSize = MESSAGE_MIN_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			break;
		}
		case KICKED_FROM_MATCH_NOTIFICATION:
		{
			//Uses: 1) Message Type
			messageSize = MESSAGE_MIN_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			break;
		}
		case KICKED_FROM_MATCH_ACK:
		{
			//Uses: 1) Message Type
			messageSize = MESSAGE_MIN_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			break;
		}
		case PLAYER_LEFT_MATCH_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) Player ID
			messageSize = MESSAGE_MIN_SIZE + sizeof(playerID);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//Put the type in
			memcpy(buffer, &playerID, sizeof(playerID));
			buffer += sizeof(playerID);

			break;
		}
		case PLAYER_LEFT_MATCH_ACK:
		{
			//Uses: 1) Message Type
			messageSize = MESSAGE_MIN_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			break;
		}
		case PLAYER_JOINED_MATCH_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) Player Description
			messageSize = MESSAGE_MIN_SIZE + PLAYER_DESCR_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			//Put the player description in
			memcpy(buffer, &playerDescription.name, PLAYER_NAME_SIZE);
			buffer += PLAYER_NAME_SIZE;
			memcpy(buffer, &playerDescription.ID, sizeof(uint));
			buffer += sizeof(uint);
			memcpy(buffer, &playerDescription.color, sizeof(enum TeamColor));
			buffer += sizeof(enum TeamColor);
			memcpy(buffer, &playerDescription.team, sizeof(enum TeamNumber));
			buffer += sizeof(enum TeamNumber);

			break;
		}
		case PLAYER_JOINED_MATCH_ACK:
		{
			//Uses: 1) Message Type
			messageSize = MESSAGE_MIN_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			break;
		}
		case COLOR_CHANGED_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) Player ID
			//		3) New Color
			messageSize = MESSAGE_MIN_SIZE + sizeof(playerID) + sizeof(newColor);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//Player ID
			memcpy(buffer, &playerID, sizeof(playerID));
			buffer += sizeof(playerID);
			//Player ID
			memcpy(buffer, &newColor, sizeof(newColor));
			buffer += sizeof(newColor);

			break;
		}
		case COLOR_CHANGED_ACK:
		{
			//Uses: 1) Message Type
			messageSize = MESSAGE_MIN_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			break;
		}
		case MAP_CHANGED_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) Map Description
			messageSize = MESSAGE_MIN_SIZE + MAP_DESCR_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			//Put the map description in
			memcpy(buffer, &mapDescription.name, MAP_NAME_LEN);
			buffer += sizeof(mapDescription);
			memcpy(buffer, &mapDescription.length, sizeof(uint));
			buffer += sizeof(uint);
			memcpy(buffer, &mapDescription.width, sizeof(uint));
			buffer += sizeof(uint);
			break;
		}
		case MAP_CHANGED_ACK:
		{
			//Uses: 1) Message Type
			messageSize = MESSAGE_MIN_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			break;
		}
		case GAME_SPEED_CHANGED_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) Game Speed
			messageSize = MESSAGE_MIN_SIZE + sizeof(newSpeed);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//Put the type in
			memcpy(buffer, &newSpeed, sizeof(newSpeed));
			buffer += sizeof(newSpeed);

			break;
		}
		case GAME_SPEED_CHANGED_ACK:
		{
			//Uses: 1) Message Type
			messageSize = MESSAGE_MIN_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			break;
		}
		case VICTORY_COND_CHANGED_NOTIFICATION:
		{
			//Uses: 1) Message Type
			//		2) Victory Condition
			messageSize = MESSAGE_MIN_SIZE + sizeof(newVictCond);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//PVictory Condition
			memcpy(buffer, &newVictCond, sizeof(newVictCond));
			buffer += sizeof(newVictCond);

			break;
		}
		case VICTORY_COND_CHANGED_ACK:
		{
			//Uses: 1) Message Type
			messageSize = MESSAGE_MIN_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			break;
		}
		case MATCH_START_NOTIFICATION:
		{
			//Uses: 1) Message Type
			messageSize = MESSAGE_MIN_SIZE;
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;

			break;
		}
		case MATCH_START_ACK:
		{
			//Uses: 1) Message Type
			//		2) Change Accepted
			messageSize = MESSAGE_MIN_SIZE + sizeof(changeAccepted);
			buffer = (char*)malloc(messageSize);
			originalBuffer = buffer;

			//Put the type in
			memcpy(buffer, &type, MESSAGE_MIN_SIZE);
			buffer += MESSAGE_MIN_SIZE;
			//Accept Changes
			memcpy(buffer, &changeAccepted, sizeof(changeAccepted));
			buffer += sizeof(changeAccepted);

			break;
		}

		default:
		{
			//Error
			return NULL;
		}
	}

	*length = messageSize;
	return originalBuffer;
}
