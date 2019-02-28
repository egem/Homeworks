#include "StorageManager.h"
#include <iostream>
#include <stdio.h>
#include "PageManager.h"
#include "LogManager.h"
#include "Record.h"
#include <sstream>

StorageManager* StorageManager::m_pcStorageManagerInstance = NULL;

StorageManager* StorageManager::GetInstance()
{
	if(m_pcStorageManagerInstance == NULL)
	{
		m_pcStorageManagerInstance = new StorageManager();
	}

	return m_pcStorageManagerInstance;
}

StorageManager::StorageManager()
{

}

StorageManager::~StorageManager()
{
	
}

bool StorageManager::CreateTable(std::string strTypeName, u8 u8NumberOfField, std::string pstrFieldNames[10])
{
	PageManager cPageManager(SYSTEM_CATALOG_FILE_NAME);

	u32 u32PageID = 0;	
	Page cCurrentPage;
	bool bWritten = false;
	
	while(!bWritten)
	{
		if(cPageManager.ReadPage(u32PageID, cCurrentPage))
		{			
			if(cCurrentPage.m_cPageHeader.m_u16FreeSpace < TYPE_SIZE)
			{
				u32PageID++;
				continue;
			}
			else
			{
				u8 u8TypeID = 0;
				while(u8TypeID * sizeof(Type) < TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE)
				{
					Type cType;
					memcpy((void*)&cType, (void*)&cCurrentPage.m_pu8Data[u8TypeID * TYPE_SIZE], TYPE_SIZE);
					if(cType.m_cTypeHeader.m_u8IsUsed == 0)
					{
						memcpy((void*)cType.m_cTypeHeader.m_pu8TypeName, (void*)strTypeName.c_str(), strTypeName.length());
						cType.m_cTypeHeader.m_u8NumberOfField = u8NumberOfField;
						cType.m_cTypeHeader.m_u8TypeID = u8TypeID;

						for(u8 u8FieldNameIndex = 0; u8FieldNameIndex < u8NumberOfField; u8FieldNameIndex++)
						{
							memcpy((void*)cType.m_pu8TypeData[u8FieldNameIndex], (void*)pstrFieldNames[u8FieldNameIndex].c_str(), pstrFieldNames[u8FieldNameIndex].length());
						}

						cType.m_cTypeHeader.m_u8IsUsed = 1;

						memcpy((void*)&cCurrentPage.m_pu8Data[u8TypeID * TYPE_SIZE], (void*)&cType, TYPE_SIZE);
						cCurrentPage.m_cPageHeader.m_u16FreeSpace -= TYPE_SIZE;
						cPageManager.WritePage(u32PageID,cCurrentPage);

						return true;
					}
					u8TypeID++;
				}
			}
		}
		else
		{
			Page cNewPage;
			cNewPage.m_cPageHeader.m_u32PageID = u32PageID;
			cNewPage.m_cPageHeader.m_u16TotalSpace = TOTAL_PAGE_SIZE;
			cNewPage.m_cPageHeader.m_u16FreeSpace = TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE;

			if(u32PageID == 0)
				cPageManager.WritePage(u32PageID, cNewPage, true);
			else
				cPageManager.WritePage(u32PageID, cNewPage);
		}
		
	}

	return false;
}

bool StorageManager::DeleteTable(std::string strTypeName)
{
	PageManager cPageManager(SYSTEM_CATALOG_FILE_NAME);

	u32 u32PageID = 0;
	Page cCurrentPage;
	bool bDeleted = false;

	while(!bDeleted)
	{
		if(cPageManager.ReadPage(u32PageID, cCurrentPage))
		{
			if(cCurrentPage.m_cPageHeader.m_u16FreeSpace == (TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE))
			{
				u32PageID++;
				continue;
			}
			else
			{
				u8 u8TypeID = 0;
				while(u8TypeID * sizeof(Type) < TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE)
				{
					Type cType;
					memcpy((void*)&cType, (void*)&cCurrentPage.m_pu8Data[u8TypeID * sizeof(cType)], TYPE_SIZE);
					if(cType.m_cTypeHeader.m_u8IsUsed == 1)
					{
						char pchTypeName[TYPE_NAME_MAX_SIZE];
						memcpy(pchTypeName, cType.m_cTypeHeader.m_pu8TypeName, TYPE_NAME_MAX_SIZE);
						
						if(strcmp(strTypeName.c_str(), pchTypeName) == 0)
						{
							Type cEmptyType;
							cEmptyType.m_cTypeHeader.m_u8TypeID = u8TypeID;	
							memcpy((void*)&cCurrentPage.m_pu8Data[u8TypeID * TYPE_SIZE], (void*)&cEmptyType, TYPE_SIZE);
							cCurrentPage.m_cPageHeader.m_u16FreeSpace += TYPE_SIZE;
							cPageManager.WritePage(u32PageID,cCurrentPage);

							std::string strDataFile = strTypeName + DATA_FILE_EXTENSION;
							remove(strDataFile.c_str());
							LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, "Deleted successfully\n");
							return true;
						}
					}
					u8TypeID++;
				}

				u32PageID++;
			}
		}
		else
		{
			LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, "There is no type like that\n");
			break;
		}
	}

	return false;
}

bool StorageManager::ListTables()
{
	PageManager cPageManager(SYSTEM_CATALOG_FILE_NAME);

	u32 u32PageID = 0;
	Page cCurrentPage;

	while(cPageManager.ReadPage(u32PageID, cCurrentPage))
	{
		if(cCurrentPage.m_cPageHeader.m_u16FreeSpace == (TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE))
		{
			u32PageID++;
			continue;
		}
		else
		{
			u8 u8TypeID = 0;
			while(u8TypeID * sizeof(Type) < TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE)
			{
				Type cType;
				memcpy((void*)&cType, (void*)&cCurrentPage.m_pu8Data[u8TypeID * sizeof(cType)], TYPE_SIZE);
				if(cType.m_cTypeHeader.m_u8IsUsed == 1)
				{
					char pchTypeName[TYPE_NAME_MAX_SIZE];
					memcpy(pchTypeName, cType.m_cTypeHeader.m_pu8TypeName, TYPE_NAME_MAX_SIZE);
					std::string strTypeName(pchTypeName);
					LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, strTypeName + "\t");

					for(int nFieldIndex = 0; nFieldIndex < cType.m_cTypeHeader.m_u8NumberOfField; nFieldIndex++)
					{
						char pchFieldName[COLUMN_NAME_MAX_SIZE];
						memcpy((void*)pchFieldName, (void*)cType.m_pu8TypeData[nFieldIndex], COLUMN_NAME_MAX_SIZE);
						std::string strFieldName(pchFieldName);
						LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, strFieldName + "\t");
					}
					LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, "\n");
				}
				u8TypeID++;
			}
			u32PageID++;
		}
	}

	return true;
}


bool StorageManager::CreateRecord(std::string strTypeName, u8 u8NumberOfField, std::string pstrFieldNames[10])
{
	std::string strDataFilePath = strTypeName + DATA_FILE_EXTENSION;
	
	PageManager cPageManager(strDataFilePath);

	u32 u32PageID = 0;	
	Page cCurrentPage;
	bool bWritten = false;
	
	while(!bWritten)
	{
		if(cPageManager.ReadPage(u32PageID, cCurrentPage))
		{			
			if(cCurrentPage.m_cPageHeader.m_u16FreeSpace < RECORD_SIZE)
			{
				u32PageID++;
				continue;
			}
			else
			{
				u8 u8RecordID = 0;
				while(u8RecordID * sizeof(Record) < TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE)
				{
					Record cRecord;
					memcpy((void*)&cRecord, (void*)&cCurrentPage.m_pu8Data[u8RecordID * RECORD_SIZE], RECORD_SIZE);
					if(cRecord.m_cRecordHeader.m_u8IsUsed == 0)
					{
						cRecord.m_cRecordHeader.m_u8NumberOfField = u8NumberOfField;
						cRecord.m_cRecordHeader.m_u8RecordID = u8RecordID;

						for(u8 u8FieldNameIndex = 0; u8FieldNameIndex < u8NumberOfField; u8FieldNameIndex++)
						{
							std::stringstream s_str(pstrFieldNames[u8FieldNameIndex]);
							s_str >> cRecord.m_pu32FieldValues[u8FieldNameIndex];
						}

						cRecord.m_cRecordHeader.m_u8IsUsed = 1;

						memcpy((void*)&cCurrentPage.m_pu8Data[u8RecordID * RECORD_SIZE], (void*)&cRecord, RECORD_SIZE);
						cCurrentPage.m_cPageHeader.m_u16FreeSpace -= RECORD_SIZE;
						cPageManager.WritePage(u32PageID,cCurrentPage);

						return true;
					}
					u8RecordID++;
				}
			}
		}
		else
		{
			Page cNewPage;
			cNewPage.m_cPageHeader.m_u32PageID = u32PageID;
			cNewPage.m_cPageHeader.m_u16TotalSpace = TOTAL_PAGE_SIZE;
			cNewPage.m_cPageHeader.m_u16FreeSpace = TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE;

			if(u32PageID == 0)
				cPageManager.WritePage(u32PageID, cNewPage, true);
			else
				cPageManager.WritePage(u32PageID, cNewPage);
		}
		
	}

	return false;
}

bool StorageManager::DeleteRecord(std::string strTypeName, std::string strPrimaryKey)
{	
	std::string strDataFilePath = strTypeName + DATA_FILE_EXTENSION;
	
	PageManager cPageManager(strDataFilePath);

	u32 u32PageID = 0;
	Page cCurrentPage;
	bool bDeleted = false;

	while(!bDeleted)
	{
		if(cPageManager.ReadPage(u32PageID, cCurrentPage))
		{
			if(cCurrentPage.m_cPageHeader.m_u16FreeSpace == (TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE))
			{
				u32PageID++;
				continue;
			}
			else
			{
				u8 u8RecordID = 0;
				while(u8RecordID * sizeof(Record) < TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE)
				{
					Record cRecord;
					memcpy((void*)&cRecord, (void*)&cCurrentPage.m_pu8Data[u8RecordID * RECORD_SIZE], RECORD_SIZE);
					if(cRecord.m_cRecordHeader.m_u8IsUsed == 1)
					{
						u32 u32PrimaryKeyValue = 0;
						std::stringstream s_str(strPrimaryKey);
						s_str >> u32PrimaryKeyValue;

						if(u32PrimaryKeyValue == cRecord.m_pu32FieldValues[0])
						{
							Record cEmptyRecord;
							cEmptyRecord.m_cRecordHeader.m_u8RecordID = u8RecordID;
							memcpy((void*)&cCurrentPage.m_pu8Data[u8RecordID * RECORD_SIZE], (void*)&cEmptyRecord, RECORD_SIZE);
							cCurrentPage.m_cPageHeader.m_u16FreeSpace += RECORD_SIZE;

							cPageManager.WritePage(u32PageID,cCurrentPage);

							LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, "Deleted successfully\n");

							return true;
						}
						
					}
					u8RecordID++;
				}

				u32PageID++;
			}
		}
		else
		{
			LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, "There is no record like that\n");
			break;
		}
	}

	return false;
}

bool StorageManager::ListRecords(std::string strTypeName)
{	
	std::string strDataFilePath = strTypeName + DATA_FILE_EXTENSION;
	
	PageManager cPageManager(strDataFilePath);

	u32 u32PageID = 0;
	Page cCurrentPage;

	while(cPageManager.ReadPage(u32PageID, cCurrentPage))
	{
		if(cCurrentPage.m_cPageHeader.m_u16FreeSpace == (TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE))
		{
			u32PageID++;
			continue;
		}
		else
		{
			u8 u8RecordID = 0;
			while(u8RecordID * RECORD_SIZE < TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE)
			{
				Record cRecord;
				memcpy((void*)&cRecord, (void*)&cCurrentPage.m_pu8Data[u8RecordID * RECORD_SIZE], RECORD_SIZE);
				if(cRecord.m_cRecordHeader.m_u8IsUsed == 1)
				{
					for(int nFieldIndex = 0; nFieldIndex < cRecord.m_cRecordHeader.m_u8NumberOfField; nFieldIndex++)
					{
						std::stringstream cInt2String;
						cInt2String << cRecord.m_pu32FieldValues[nFieldIndex];
						LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, cInt2String.str() + "\t");
					}
					LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, "\n");

				}
				u8RecordID++;
			}
			u32PageID++;
		}
	}

	return true;
}


bool StorageManager::UpdateRecord(std::string strTypeName, u8 u8NumberOfField, std::string pstrFieldNames[10])
{
	std::string strDataFilePath = strTypeName + DATA_FILE_EXTENSION;
	
	PageManager cPageManager(strDataFilePath);

	u32 u32PageID = 0;
	Page cCurrentPage;

	while(cPageManager.ReadPage(u32PageID, cCurrentPage))
	{
		if(cCurrentPage.m_cPageHeader.m_u16FreeSpace == (TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE))
		{
			u32PageID++;
			continue;
		}
		else
		{
			u8 u8RecordID = 0;
			while(u8RecordID * RECORD_SIZE < TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE)
			{
				Record cRecord;
				memcpy((void*)&cRecord, (void*)&cCurrentPage.m_pu8Data[u8RecordID * RECORD_SIZE], RECORD_SIZE);
				if(cRecord.m_cRecordHeader.m_u8IsUsed == 1)
				{
					u32 u32PrimaryKeyValue = 0;
					std::stringstream s_str(pstrFieldNames[0]);
					s_str >> u32PrimaryKeyValue;
					
					if(cRecord.m_pu32FieldValues[0] == u32PrimaryKeyValue)
					{
						cRecord.m_cRecordHeader.m_u8NumberOfField = u8NumberOfField;
						cRecord.m_cRecordHeader.m_u8RecordID = u8RecordID;

						for(u8 u8FieldNameIndex = 0; u8FieldNameIndex < u8NumberOfField; u8FieldNameIndex++)
						{
							std::stringstream s_str(pstrFieldNames[u8FieldNameIndex]);
							s_str >> cRecord.m_pu32FieldValues[u8FieldNameIndex];
						}

						cRecord.m_cRecordHeader.m_u8IsUsed = 1;

						memcpy((void*)&cCurrentPage.m_pu8Data[u8RecordID * RECORD_SIZE], (void*)&cRecord, RECORD_SIZE);
						cPageManager.WritePage(u32PageID,cCurrentPage);

						LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, "Updated Successfully\n");

						return true;
					}
					
					

				}
				u8RecordID++;
			}
			u32PageID++;
		}
	}

	return false;
}

bool StorageManager::SelectRecord(std::string strTypeName, std::string strPrimaryKey, Record& cOutputRecord)
{
	std::string strDataFilePath = strTypeName + DATA_FILE_EXTENSION;
	
	PageManager cPageManager(strDataFilePath);

	u32 u32PageID = 0;
	Page cCurrentPage;

	while(cPageManager.ReadPage(u32PageID, cCurrentPage))
	{
		if(cCurrentPage.m_cPageHeader.m_u16FreeSpace == (TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE))
		{
			u32PageID++;
			continue;
		}
		else
		{
			u8 u8RecordID = 0;
			while(u8RecordID * RECORD_SIZE < TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE)
			{
				Record cRecord;
				memcpy((void*)&cRecord, (void*)&cCurrentPage.m_pu8Data[u8RecordID * RECORD_SIZE], RECORD_SIZE);
				if(cRecord.m_cRecordHeader.m_u8IsUsed == 1)
				{
					u32 u32PrimaryKeyValue = 0;
					std::stringstream s_str(strPrimaryKey);
					s_str >> u32PrimaryKeyValue;
					
					if(cRecord.m_pu32FieldValues[0] == u32PrimaryKeyValue)
					{
						cOutputRecord = cRecord;
						LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, "Record Found Successfully\n");

						for(int nFieldIndex = 0; nFieldIndex < cRecord.m_cRecordHeader.m_u8NumberOfField; nFieldIndex++)
						{
							std::stringstream cInt2String;
							cInt2String << cRecord.m_pu32FieldValues[nFieldIndex];
							LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, cInt2String.str() + "\t");
						}

						LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_SYSTEM, "\n");
						
						return true;
					}
					
					
				}
				u8RecordID++;
			}
			u32PageID++;
		}
	}

	return false;
}

