//============================================================================
// Name        : LoF_Server.cpp
// Author      : AltF4
// Copyright   : GNU GPLv3
// Description : Error handling for Gameboard
//============================================================================

#ifndef INVALIDGAMEBOARDEXCEPTION_H_
#define INVALIDGAMEBOARDEXCEPTION_H_

#include <stdexcept>
#include <string>

class InvalidGameboardException : public std::runtime_error
{

public:
	InvalidGameboardException(const string& message)
        : std::runtime_error(message) { };
};



#endif /* INVALIDGAMEBOARDEXCEPTION_H_ */
