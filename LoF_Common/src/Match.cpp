//============================================================================
// Name        : LoF_Server.cpp
// Author      : AltF4
// Copyright   : 2011, GNU GPLv3
// Description : A single match (or game) that is being played.
//					A server can have many at one time
//============================================================================s

#include "Match.h"

using namespace std;
using namespace LoF;

Match::Match()
{

}

void Match::SetID(uint newID)
{
	ID = newID;
	description.ID = newID;
}

void Match::SetStatus(enum Status newStatus)
{
	status = newStatus;
	description.status = newStatus;
}

enum Status Match::GetStatus()
{
	return status;
}

uint Match::GetID()
{
	return ID;
}
