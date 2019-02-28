#include "LogManager.h"
#include "Datatype.h"

u32 LogManager::m_u32MessageType = ENUM_LOG_MESSAGE_LEVEL_SYSTEM | ENUM_LOG_MESSAGE_LEVEL_ERROR;

void LogManager::PrintMessage(LOG_MESSAGE_TYPE eMessageType, std::string strMessage)
{
	if(m_u32MessageType & eMessageType)
	{
		std::cout << strMessage;
	}
}

void LogManager::PrintMessage(LOG_MESSAGE_TYPE eMessageType, u32 u32Message)
{
	if(m_u32MessageType & eMessageType)
	{
		std::cout << u32Message;
	}
}

void LogManager::SetMessageType(LOG_MESSAGE_TYPE eMessageType, bool bEnable)
{
	if(bEnable)
	{
		m_u32MessageType |= (int)eMessageType;
	}
	else
	{
		m_u32MessageType &= (~((int)eMessageType));
	}
}