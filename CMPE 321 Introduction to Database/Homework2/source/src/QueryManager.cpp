#include "QueryManager.h"
#include "LogManager.h"
#include <vector>
#include <sstream>
#include "StorageManager.h"

QueryManager::QueryManager()
{
	m_bListenLoopEnable = true;
}

QueryManager::~QueryManager()
{

}

void QueryManager::Listen()
{
	std::string strInput;
	
	while(m_bListenLoopEnable)
	{
		LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, ">>");
		std::getline(std::cin, strInput);
		ExecuteCommand(strInput);
	}
}

void QueryManager::ExecuteCommand(std::string strCommand)
{
	std::vector<std::string> strCommandVector;
	std::string strSubCommand;
	std::istringstream strCommandStream(strCommand);
	
	for(std::string strSubCommand; strCommandStream >> strSubCommand; )
	{
		strCommandVector.push_back(strSubCommand);
	}

	if(strCommandVector[0].compare(EXIT_COMMAND) == 0)
	{ // >> exit
		m_bListenLoopEnable = false;
	}
	else if(strCommandVector[0].compare(CREATE_COMMAND) == 0)
	{ 
		if(strCommandVector[1].compare(TYPE) == 0)
		{ // >> create table table_name column1_name column2_name ....
			LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_DEBUG, "Create Table command is called\n");
			
			std::string pstrFieldNames[10];
			
			for(u8 u8FieldIndex = 0; u8FieldIndex < (strCommandVector.size()-3); u8FieldIndex++)
			{
				pstrFieldNames[u8FieldIndex] = strCommandVector[u8FieldIndex + 3];
			}
			
			StorageManager::GetInstance()->CreateTable(strCommandVector[2], strCommandVector.size()-3,  pstrFieldNames);
		}
		else if(strCommandVector[1].compare(RECORD) == 0)
		{ // >> create record table_name field1_value field2_value ....
			LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_DEBUG, "Create Record command is called\n");

			std::string pstrFieldNames[10];
			
			for(u8 u8FieldIndex = 0; u8FieldIndex < (strCommandVector.size()-3); u8FieldIndex++)
			{
				pstrFieldNames[u8FieldIndex] = strCommandVector[u8FieldIndex + 3];
			}
			
			StorageManager::GetInstance()->CreateRecord(strCommandVector[2], strCommandVector.size()-3,  pstrFieldNames);
		}
	}
	else if(strCommandVector[0].compare(DELETE_COMMAND) == 0)
	{ 
		if(strCommandVector[1].compare(TYPE) == 0)
		{ // >> delete table table_name
			LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_DEBUG, "Delete Table command is called\n");

			StorageManager::GetInstance()->DeleteTable(strCommandVector[2]);
		}
		else if(strCommandVector[1].compare(RECORD) == 0)
		{ // >> delete record table_name primary_key
			LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_DEBUG, "Delete Record command is called\n");

			StorageManager::GetInstance()->DeleteRecord(strCommandVector[2], strCommandVector[3]);
		}
	}
	else if(strCommandVector[0].compare(LIST_COMMAND) == 0)
	{ // >> list tables
		if(strCommandVector[1].compare(TYPES) == 0)
		{
			LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_DEBUG, "List Tables command is called\n");

			StorageManager::GetInstance()->ListTables();
		}
		else if(strCommandVector[1].compare(RECORDS) == 0)
		{ // >> list records table
			LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_DEBUG, "List Records command is called\n");
			
			StorageManager::GetInstance()->ListRecords(strCommandVector[2]);
		}
	}
	else if(strCommandVector[0].compare(UPDATE_COMMAND) == 0)
	{ 
		if(strCommandVector[1].compare(RECORD) == 0)
		{ // >> update record table_name field1_value field2_value ....
			LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_DEBUG, "Update Record command is called\n");

			std::string pstrFieldNames[10];
			
			for(u8 u8FieldIndex = 0; u8FieldIndex < (strCommandVector.size()-3); u8FieldIndex++)
			{
				pstrFieldNames[u8FieldIndex] = strCommandVector[u8FieldIndex + 3];
			}
			
			StorageManager::GetInstance()->UpdateRecord(strCommandVector[2], strCommandVector.size()-3, pstrFieldNames);
		}
	}
	else if(strCommandVector[0].compare(SEARCH_COMMAND) == 0)
	{ 
		if(strCommandVector[1].compare(RECORD) == 0)
		{ // select record table primary_key
			LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_DEBUG, "Select Record command is called\n");
			Record cOutputRecord;
			StorageManager::GetInstance()->SelectRecord(strCommandVector[2], strCommandVector[3], cOutputRecord); 
		}

	}
	else if(strCommandVector[0].compare(DEBUG_PRINT_COMMAND) == 0)
	{ 
		if(strCommandVector[1].compare(ON_COMMAND) == 0)
		{ 
			LogManager::SetMessageType(ENUM_LOG_MESSAGE_LEVEL_DEBUG, true);
		}
		else if(strCommandVector[1].compare(OFF_COMMAND) == 0)
		{
			LogManager::SetMessageType(ENUM_LOG_MESSAGE_LEVEL_DEBUG, false);
		}
	}
	else if(strCommandVector[0].compare(INFO_PRINT_COMMAND) == 0)
	{ 
		if(strCommandVector[1].compare(ON_COMMAND) == 0)
		{ 
			LogManager::SetMessageType(ENUM_LOG_MESSAGE_LEVEL_INFO, true);
		}
		else if(strCommandVector[1].compare(OFF_COMMAND) == 0)
		{
			LogManager::SetMessageType(ENUM_LOG_MESSAGE_LEVEL_INFO, false);
		}
	}
	else
	{
		LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, "Please call valid command\n");
	}
	
	
}