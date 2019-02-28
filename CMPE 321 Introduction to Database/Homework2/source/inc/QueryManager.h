#ifndef __QUERY_MANAGER_H__
#define __QUERY_MANAGER_H__

#include <iostream>
#include <cstring>

#define EXIT_COMMAND "exit"
#define CREATE_COMMAND "create"
#define DELETE_COMMAND "delete"
#define LIST_COMMAND "list"
#define TYPE "table"
#define TYPES "tables"
#define RECORD "record"
#define RECORDS "records"
#define UPDATE_COMMAND "update"
#define SEARCH_COMMAND "select"
#define DEBUG_PRINT_COMMAND "debug"
#define INFO_PRINT_COMMAND "info"
#define ON_COMMAND "on"
#define OFF_COMMAND "off"

class QueryManager
{
	// Variables
	private:
		bool m_bListenLoopEnable;
		
	public:

	// Methods
	private:
		void ExecuteCommand(std::string strCommand);
		
	public:
		QueryManager();
		~QueryManager();
		void Listen();		
};

#endif
