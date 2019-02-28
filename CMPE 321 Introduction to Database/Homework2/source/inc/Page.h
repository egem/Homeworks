#ifndef __PAGE_H__
#define __PAGE_H__

#include "Datatype.h"

#define TOTAL_PAGE_HEADER_SIZE 124
#define USED_PAGE_HEADER_SIZE 8
#define FREE_PAGE_HEADER_SIZE (TOTAL_PAGE_HEADER_SIZE - USED_PAGE_HEADER_SIZE)
#define TOTAL_PAGE_SIZE 1024
#define PAGE_DATA_SIZE (TOTAL_PAGE_SIZE - TOTAL_PAGE_HEADER_SIZE)

#if(TOTAL_PAGE_HEADER_SIZE > TOTAL_PAGE_SIZE)
	#error "Check Total Page Header Size"
#endif

#if(USED_PAGE_HEADER_SIZE > TOTAL_PAGE_HEADER_SIZE)
	#error "Check Used Page Header Size"
#endif

class Page
{
	public:
		class PageHeader
		{
			// Variables
			public:
				u32 m_u32PageID;
				u16 m_u16TotalSpace;
				u16 m_u16FreeSpace;
				u8 m_pu8Reserved[FREE_PAGE_HEADER_SIZE];

			//Methods
			PageHeader();
			
		};

		// Variables	
		PageHeader m_cPageHeader;
		u8 m_pu8Data[PAGE_DATA_SIZE];

		// Methods
		Page();
	
};

#endif
