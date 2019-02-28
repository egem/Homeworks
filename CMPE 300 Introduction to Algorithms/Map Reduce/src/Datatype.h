#ifndef __DATATYPE_H__
#define __DATATYPE_H__

#include <iostream>

#define PRINT_DEBUG_MESSAGE(MESSAGE) //std::cout << "[DEBUG] " << MESSAGE << "  FILE : " << __FILE__ << "  LINE : " << __LINE__ << std::endl
#define PRINT_INFO_MESSAGE(MESSAGE) std::cout << MESSAGE << std::endl
#define PRINT_ERROR_MESSAGE(MESSAGE) std::cerr << "[ERROR] " << MESSAGE << "  FILE : " << __FILE__ << "  LINE : " << __LINE__ << std::endl

#define MASTER_PROCESS_RANK 0

enum ExceptionType
{
	EN_EXCEPTION_OUT_OF_MEMORY,
	EN_EXCEPTION_FILE_EMPTY,
	EN_EXCEPTION_PROCESS_NUMBER,
	EN_EXCEPTION_FILE_NOT_FOUND
};

#endif
