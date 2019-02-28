#include "Record.h"
#include <iostream>
#include <cstring>

Record::RecordHeader::RecordHeader()
{
	m_u8RecordID = 0;
	m_u8IsUsed = 0;
	m_u8NumberOfField = 0;
	memset(m_pu8Reserved, 0, FREE_RECORD_HEADER_SIZE);
}

Record::Record()
{
	memset(m_pu32FieldValues, 0, NUMBER_OF_COLUMN_OF_TYPE);
}
