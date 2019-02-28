#ifndef __PAGE_MANAGER_H__
#define __PAGE_MANAGER_H__

#include "Datatype.h"
#include <iostream>
#include <cstring>
#include "Page.h"

class PageManager
{	
	// Variables
	private:
		std::string m_strFilePath;
		
	public:
		
	// Methods
	private:

	public:
		PageManager(std::string strFilePath);

		bool ReadPage(u32 PageID, Page& cPage);
		bool WritePage(u32 PageID, const Page& cPage, bool bCreateNewPage = false);
};

#endif
