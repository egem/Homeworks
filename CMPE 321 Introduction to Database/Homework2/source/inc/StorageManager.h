#ifndef __STORAGE_MANAGER_H__
#define __STORAGE_MANAGER_H__

#include "Datatype.h"
#include <iostream>
#include <cstring>
#include "Type.h"
#include "Record.h"

#define SYSTEM_CATALOG_FILE_NAME "sys.cat"
#define DATA_FILE_EXTENSION ".dat"

class StorageManager
{
	// Variables
	private:
		static StorageManager* m_pcStorageManagerInstance;
	public:

	// Methods
	private:

	protected:
		StorageManager();
		virtual ~StorageManager();
		
	public:
		static StorageManager* GetInstance();

		bool CreateTable(std::string strTypeName, u8 u8NumberOfField, std::string pstrFieldNames[10]);
		bool DeleteTable(std::string strTypeName);
		bool ListTables();
		
		bool CreateRecord(std::string strTypeName, u8 u8NumberOfField, std::string pstrFieldNames[10]);
		bool DeleteRecord(std::string strTypeName, std::string strPrimaryKey);
		bool ListRecords(std::string strTypeName);
		bool UpdateRecord(std::string strTypeName, u8 u8NumberOfField, std::string pstrFieldNames[10]);
		bool SelectRecord(std::string strTypeName, std::string strPrimaryKey, Record& cOutputRecord);
};

#endif
