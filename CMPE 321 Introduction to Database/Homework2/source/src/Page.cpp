#include "Page.h"
#include <stdio.h>
#include <cstring>

Page::PageHeader::PageHeader()
{
	memset(m_pu8Reserved, 0, FREE_PAGE_HEADER_SIZE);
	m_u32PageID = 0;
	m_u16TotalSpace = TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE;
	m_u16FreeSpace = m_u16TotalSpace;
}

Page::Page()
{
	memset(m_pu8Data, 0, PAGE_DATA_SIZE);
}
