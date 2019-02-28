#include <iostream>
#include <cstring>
#include "Datatype.h"
#include <sstream>

enum LOG_MESSAGE_TYPE
{
	ENUM_LOG_MESSAGE_LEVEL_SYSTEM = 0x01,
	ENUM_LOG_MESSAGE_LEVEL_INFO = 0x02,
	ENUM_LOG_MESSAGE_LEVEL_DEBUG = 0x04,
	ENUM_LOG_MESSAGE_LEVEL_ERROR = 0x08
};


class LogManager
{
	private:
		static u32 m_u32MessageType;
		
	public:
		static void PrintMessage(LOG_MESSAGE_TYPE eMessageType, std::string strMessage);
		static void PrintMessage(LOG_MESSAGE_TYPE eMessageType, u32 u32Message);
		
		static void SetMessageType(LOG_MESSAGE_TYPE eMessageType, bool bEnable);
};
