//============================================================================
// Name        : RTT_Server.cpp
// Author      : AltF4
// Copyright   : 2011, GNU GPLv3
// Description : One Hex on the gameboard
//============================================================================

#include <iostream>
#include "Tile.h"
#include "exceptions/IllegalMoveException.h"


using namespace std;
using namespace RTT;

Tile::Tile(uint x_arg, uint y_arg)
{
	m_x = x_arg;
	m_y = y_arg;
	m_isPassable = true;
}

//Moves the Unit (who is currently on this tile) to the specified tile
void Tile::MoveUnitTo(Unit *unit, Tile *tile)
{
	int tileIndex = this->IndexOfUnit( unit );
	if( tileIndex != -1)
	{
		//TODO: Find the shortest path

		tile->m_unitsPresent.push_back(unit);
		//Null it out first, so that erase doesn't call the destructor
		m_unitsPresent[tileIndex] = NULL;
		m_unitsPresent.erase( m_unitsPresent.begin()+tileIndex );
	}
	else
	{
		cerr << "Error: Unit '" << unit->m_ID << "' not present on tile ("
				<< m_x << ", " << m_y << ")\n";
		throw IllegalMoveException("Unit not present on tile to be moved from.");
	}

}

//Checks if the given unit is standing on this tile
//Returns the index of the Unit in the Tile's list
//Returns -1 if it's not there
int Tile::IndexOfUnit(Unit *unit)
{
	for( uint i = 0; i < m_unitsPresent.size(); i++ )
	{
		if( m_unitsPresent[i]->Equals(unit) )
		{
			return i;
		}
	}
	return -1;
}

