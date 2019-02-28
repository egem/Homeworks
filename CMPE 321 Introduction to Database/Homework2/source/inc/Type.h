#ifndef __TYPE_H__
#define __TYPE_H__

#include "Datatype.h"

#define TYPE_SIZE 180
#define TYPE_HEADER_SIZE 20
#define TYPE_NAME_MAX_SIZE 16
#define COLUMN_NAME_MAX_SIZE 16
#define NUMBER_OF_COLUMN_OF_TYPE 10

#if(NUMBER_OF_COLUMN_OF_TYPE * COLUMN_NAME_MAX_SIZE + TYPE_HEADER_SIZE != TYPE_SIZE)
	#error "Check Type Size Values"
#endif

class Type
{
	public:
		class TypeHeader
		{
			public:
				// Variables
				u8 m_u8TypeID;
				u8 m_u8IsUsed;
				u8 m_u8NumberOfField;
				u8 m_pu8TypeName[TYPE_NAME_MAX_SIZE];
				u8 m_u8Reserved;
				// Methods
				TypeHeader();
		};

		// Variables
		TypeHeader m_cTypeHeader;
		u8 m_pu8TypeData[NUMBER_OF_COLUMN_OF_TYPE][COLUMN_NAME_MAX_SIZE];

		// Methods
		Type();
		
};

#endif
