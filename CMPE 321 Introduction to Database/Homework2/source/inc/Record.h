#ifndef __RECORD_H__
#define __RECORD_H__

#include "Datatype.h"
#include "Type.h"

#define RECORD_SIZE 60
#define RECORD_HEADER_SIZE 20
#define FREE_RECORD_HEADER_SIZE 17

class Record
{
	public:
		class RecordHeader
		{
			public:
				// Variables
				u8 m_u8RecordID;
				u8 m_u8IsUsed;
				u8 m_u8NumberOfField;
				u8 m_pu8Reserved[FREE_RECORD_HEADER_SIZE];

				// Methods
				RecordHeader();
		};

		// Variables
		RecordHeader m_cRecordHeader;
		u32 m_pu32FieldValues[NUMBER_OF_COLUMN_OF_TYPE];

		// Methods
		Record();
		
};

#endif
