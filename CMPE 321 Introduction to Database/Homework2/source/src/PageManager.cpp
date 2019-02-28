#include "PageManager.h"
#include <iostream>
#include "LogManager.h"
#include <fstream>

PageManager::PageManager(std::string strFilePath)
:m_strFilePath(strFilePath)
{

}


bool PageManager::ReadPage(u32 PageID, Page& cPage)
{	
	u32 u32Size;
  	char pchPageData[TOTAL_PAGE_SIZE];

  	std::fstream file(m_strFilePath.c_str(), std::ios::in|std::ios::binary|std::ios::ate);

	if (file.is_open())
	{
		u32Size = file.tellg();
		if((PageID+1)*TOTAL_PAGE_SIZE > u32Size)
		{
			return false;
		}

		LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_INFO, "Reading Page ");
		LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_INFO, PageID);
		LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_INFO, "\n");
		
		file.seekg (PageID * TOTAL_PAGE_SIZE, std::ios::beg);
		file.read(pchPageData, TOTAL_PAGE_SIZE);
		memcpy((void*)&cPage, (void*)pchPageData, TOTAL_PAGE_SIZE);
		file.close();

		return true;
	}
	else
	{
		return false;
	}

	
}

bool PageManager::WritePage(u32 PageID, const Page& cPage, bool bCreateNewPage)
{
  	char pchPageData[TOTAL_PAGE_SIZE];

  	std::fstream file;

  	if(bCreateNewPage)
  		file.open(m_strFilePath.c_str(), std::ios::out | std::ios::binary);
  	else
  		file.open(m_strFilePath.c_str(), std::ios::in | std::ios::out | std::ios::binary);
  	
	if (file.is_open())
	{
		LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_INFO, "Writing Page ");
		LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_INFO, PageID);
		LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_INFO, "\n");
		
		file.seekg(PageID * TOTAL_PAGE_SIZE, std::ios::beg);
		memcpy((void*)pchPageData, (void*)&cPage, TOTAL_PAGE_SIZE);
		file.write(pchPageData, TOTAL_PAGE_SIZE);
		file.close();

		return true;
	}
	else
	{
		LogManager::PrintMessage(ENUM_LOG_MESSAGE_LEVEL_ERROR, "Unable to open " + m_strFilePath + "\n");
		return false;
	}
}


