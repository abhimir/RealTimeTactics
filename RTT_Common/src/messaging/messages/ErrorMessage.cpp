//============================================================================
// Name        : ErrorMessage.h
// Author      : AltF4
// Copyright   : 2011, GNU GPLv3
// Description : Message class pertaining to sending and receiving error conditions
//============================================================================

#include "ErrorMessage.h"
#include "string.h"

using namespace std;
using namespace RTT;

ErrorMessage::ErrorMessage(enum ErrorType type, enum ProtocolDirection direction)
{
	m_messageType = MESSAGE_ERROR;
	m_errorType = type;
	m_direction = direction;
}

ErrorMessage::ErrorMessage(char *buffer, uint32_t length)
{
	uint32_t expectedSize = MSG_HEADER_SIZE + sizeof(m_errorType);
	if( length != expectedSize )
	{
		m_serializeError = true;
		return;
	}

	m_serializeError = false;

	//Deserialize the UI_Message header
	if(!DeserializeHeader(&buffer))
	{
		m_serializeError = true;
		return;
	}

	memcpy(&m_errorType, buffer, sizeof(m_errorType));
	buffer += sizeof(m_errorType);

}

char *ErrorMessage::Serialize(uint32_t *length)
{
	char *buffer, *originalBuffer;
	uint32_t messageSize;

	messageSize = MSG_HEADER_SIZE + sizeof(m_errorType);
	buffer = (char*)malloc(messageSize);
	originalBuffer = buffer;

	SerializeHeader(&buffer);

	//Error type
	memcpy(buffer, &m_errorType, sizeof(m_errorType));
	buffer += sizeof(m_errorType);

	*length = messageSize;

	return originalBuffer;
}
