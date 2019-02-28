#include "Type.h"
#include <iostream>
#include <cstring>

Type::TypeHeader::TypeHeader()
{
	memset(m_pu8TypeName,0, TYPE_NAME_MAX_SIZE);
	m_u8TypeID = 0;
	m_u8IsUsed = 0;
	m_u8NumberOfField = 0;
	m_u8Reserved = 0;
}

Type::Type()
{
	for(int nIndex = 0; nIndex < NUMBER_OF_COLUMN_OF_TYPE; nIndex++)
		memset(m_pu8TypeData[nIndex],0, COLUMN_NAME_MAX_SIZE);
}
