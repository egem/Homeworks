#include <iostream>
#include <fstream>
#include <cstring>
#include <new>
#include <map>
#include "mpi.h"
#include "Datatype.h"
#include "FileSplitter.h"
#include "ProcessManager.h"
#include "WordCounter.h"

int main(int argc, char** argv)
{
	int  nNumberOfProcess, nProcessRank;
	
	// initialize MPI
	MPI_Init(&argc,&argv);

	// get number of tasks
	MPI_Comm_size(MPI_COMM_WORLD,&nNumberOfProcess);

	// get my rank
	MPI_Comm_rank(MPI_COMM_WORLD,&nProcessRank);
	
	MPI_Datatype stMPIWordMapType, pstMPIWordMapOldTypes[2];   // required variables
	int pnMPIWordMapBlockCounts[2];

	// MPI_Aint type used to be consistent with syntax of MPI_Type_extent routine
	MPI_Aint pnMPIWordCountOffsets[2], nMPIWordCountExtent;

	// setup description of the MAX_CHAR_ALLOWABLE_IN_WORD MPI_CHAR field pcWord
	pnMPIWordCountOffsets[0] = 0;
	pstMPIWordMapOldTypes[0] = MPI_CHAR;
	pnMPIWordMapBlockCounts[0] = MAX_CHAR_ALLOWABLE_IN_WORD;

	// setup description of the 1 MPI_UNSIGNED field nWordCount
	// need to first figure offset by getting size of MPI_CHAR
	MPI_Type_extent(MPI_CHAR, &nMPIWordCountExtent);
	pnMPIWordCountOffsets[1] = MAX_CHAR_ALLOWABLE_IN_WORD * nMPIWordCountExtent;
	pstMPIWordMapOldTypes[1] = MPI_UNSIGNED;
	pnMPIWordMapBlockCounts[1] = 1;

	// define structured type and commit it
	MPI_Type_struct(2, pnMPIWordMapBlockCounts, pnMPIWordCountOffsets, pstMPIWordMapOldTypes, &stMPIWordMapType);
	MPI_Type_commit(&stMPIWordMapType);
   
	try
	{
		if(nProcessRank == MASTER_PROCESS_RANK)
	    {  	
			if(nNumberOfProcess < 2)
				throw EN_EXCEPTION_PROCESS_NUMBER;
			
			PRINT_DEBUG_MESSAGE("Number of Process : " << nNumberOfProcess);
						
			std::ifstream cInputFile;

			cInputFile.open(argv[1], std::ios::in | std::ios::ate);

			if(!cInputFile.is_open())
			{
				throw EN_EXCEPTION_FILE_NOT_FOUND;
			}
			else
			{
				PRINT_INFO_MESSAGE("File : " << argv[1] << " is opened");
				std::streampos nFileBegin,nFileEnd;
				nFileEnd = cInputFile.tellg();
				cInputFile.seekg (0, std::ios::beg);
				nFileBegin = cInputFile.tellg();
				std::size_t nInputFileSize = nFileEnd - nFileBegin;

				if(nInputFileSize == 0)
				{
					cInputFile.close();
					throw EN_EXCEPTION_FILE_EMPTY;
				}
				
				char* pcFileBuffer = new (std::nothrow) char[nInputFileSize];
				if(pcFileBuffer == NULL)
					throw EN_EXCEPTION_OUT_OF_MEMORY;
				
				cInputFile.read(pcFileBuffer, nInputFileSize);
				
				std::vector<unsigned int> cBrackets(nNumberOfProcess, 0);
				FileSplitter::SplitFile(pcFileBuffer, nInputFileSize, nNumberOfProcess, cBrackets);
				ProcessManager::EliminatePassiveProcesses(cBrackets);
				PRINT_INFO_MESSAGE("Number of Active Process : " << cBrackets.size());

				int nActiveProcessFlag = 0;
				
				for(unsigned int nProcessIndex = 1; nProcessIndex < nNumberOfProcess; nProcessIndex++)
				{
					if(nProcessIndex < cBrackets.size())
						nActiveProcessFlag = 1;
					else
						nActiveProcessFlag = 0;
						
					MPI_Send(&nActiveProcessFlag, 1, MPI_INT, nProcessIndex, 1, MPI_COMM_WORLD);	
						
					unsigned int nDataSize = cBrackets[nProcessIndex] - cBrackets[nProcessIndex - 1];
						
					PRINT_DEBUG_MESSAGE("Process 0 is sent " << nDataSize << " bytes to process " << nProcessIndex);

					MPI_Send(&nDataSize, 1, MPI_INT, nProcessIndex, 1, MPI_COMM_WORLD);
					MPI_Send(pcFileBuffer + cBrackets[nProcessIndex - 1], nDataSize , MPI_CHAR, nProcessIndex, 2, MPI_COMM_WORLD);
					
				}

				//std::string strPartOfFile(pcFileBuffer, cBrackets[0]);
				std::map<std::string, unsigned int> cWordMap;
				
				for(unsigned int nActiveProcessIndex = 1; nActiveProcessIndex < cBrackets.size(); nActiveProcessIndex++)
				{
					int nNumberOfDistinctWord;
					MPI_Status status;

				   	MPI_Recv(&nNumberOfDistinctWord, 1, MPI_INT, nActiveProcessIndex,1, MPI_COMM_WORLD, &status);

				    // Allocate a buffer to hold the incoming numbers
				    WordMap* pstWordMap = new (std::nothrow) WordMap[nNumberOfDistinctWord];
					if(pstWordMap == NULL)
						throw EN_EXCEPTION_OUT_OF_MEMORY;
						
				    // Now receive the message with the allocated buffer
				    MPI_Recv(pstWordMap, nNumberOfDistinctWord, stMPIWordMapType, nActiveProcessIndex, 2, MPI_COMM_WORLD, &status);
				    PRINT_DEBUG_MESSAGE("Process " << nProcessRank << " received " << nNumberOfDistinctWord << " words.");

					WordCounter::Merge(cWordMap, pstWordMap, nNumberOfDistinctWord);

					delete[] pstWordMap;
				}

				WordCounter::PrintResult(cWordMap);
				
				delete[] pcFileBuffer;

				cBrackets.clear();

				cWordMap.clear();
			}

			cInputFile.close();
		
		}
		else
		{
			int nActiveProcessFlag;
			int nReceivedDataSize;
			MPI_Status status;

			MPI_Recv(&nActiveProcessFlag, 1, MPI_INT, 0,1, MPI_COMM_WORLD, &status);

			if(nActiveProcessFlag)
			{
				MPI_Recv(&nReceivedDataSize, 1, MPI_INT, 0,1, MPI_COMM_WORLD, &status);

			    // Allocate a buffer to hold the incoming numbers
			    char* pcBuffer = new (std::nothrow) char[nReceivedDataSize+1];
				if(pcBuffer == NULL)
					throw EN_EXCEPTION_OUT_OF_MEMORY;
				memset(pcBuffer,0,nReceivedDataSize+1);
			    // Now receive the message with the allocated buffer
			    MPI_Recv(pcBuffer, nReceivedDataSize, MPI_CHAR, 0, 2, MPI_COMM_WORLD, &status);
			    PRINT_DEBUG_MESSAGE("Process " << nProcessRank << " received " << nReceivedDataSize << " bytes.");

				pcBuffer[nReceivedDataSize] = '\0';
			    std::string strPartOfFile(pcBuffer);
				std::map<std::string, unsigned int> cWordMap = WordCounter::Map(strPartOfFile);

				WordMap* pstWordMap = new (std::nothrow) WordMap[cWordMap.size()];
				if(pstWordMap == NULL)
					throw EN_EXCEPTION_OUT_OF_MEMORY;

				memset(pstWordMap, 0, sizeof(pstWordMap));
				WordCounter::ConvertMaptoStruct(cWordMap, pstWordMap);

				int nNumberOfDistinctWord = cWordMap.size();
				PRINT_DEBUG_MESSAGE("Process " << nProcessRank <<" is sent " << nNumberOfDistinctWord << " word to process 0");
				MPI_Send(&nNumberOfDistinctWord, 1, MPI_INT, MASTER_PROCESS_RANK, 1, MPI_COMM_WORLD);
				MPI_Send(pstWordMap, nNumberOfDistinctWord , stMPIWordMapType, MASTER_PROCESS_RANK, 2, MPI_COMM_WORLD);
				

				delete[] pstWordMap;
			    delete[] pcBuffer;
			}
		}
	}
	catch(ExceptionType eExceptionType)
	{
		switch(eExceptionType)
		{
			case EN_EXCEPTION_OUT_OF_MEMORY:
			{
				PRINT_ERROR_MESSAGE("Unable to allocate buffer");
			}
			break;
			case EN_EXCEPTION_FILE_EMPTY:
			{
				PRINT_ERROR_MESSAGE("File is empty!");
			}
			break;
			case EN_EXCEPTION_PROCESS_NUMBER:
			{
				PRINT_ERROR_MESSAGE("There should be at least 2 processes.");
			}
			break;
			case EN_EXCEPTION_FILE_NOT_FOUND:
			{
				PRINT_ERROR_MESSAGE("File : " << argv[1] << " cannot be opened");
			}
			break;
			default:
			break;
		}

		for(unsigned int nProcessIndex = 1; nProcessIndex < nNumberOfProcess; nProcessIndex++)
		{
			int nActiveProcessFlag = 0;
			MPI_Send(&nActiveProcessFlag, 1, MPI_INT, nProcessIndex, 1, MPI_COMM_WORLD);
		}
		
	}

	// free datatype when done using it
	MPI_Type_free(&stMPIWordMapType);

	// done with MPI
	MPI_Finalize();

	
	
}

