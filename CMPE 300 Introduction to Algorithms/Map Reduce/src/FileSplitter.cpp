#include "FileSplitter.h"
#include "Datatype.h"


void FileSplitter::SplitFile(char* pcInputFile, unsigned int nFileSize, unsigned int nNumberOfProcess, std::vector<unsigned int>& cBrackets)
{
	PRINT_DEBUG_MESSAGE("nFileSize : " << nFileSize);
	PRINT_DEBUG_MESSAGE("nNumberOfProcess : " << nNumberOfProcess);

	while(pcInputFile[cBrackets[MASTER_PROCESS_RANK]] == '\t' || pcInputFile[cBrackets[MASTER_PROCESS_RANK]] == ' ' || pcInputFile[cBrackets[MASTER_PROCESS_RANK]] == '\n')
	{
		cBrackets[MASTER_PROCESS_RANK]++;
		if(cBrackets[MASTER_PROCESS_RANK] == nFileSize)
		{
			PRINT_DEBUG_MESSAGE("File limit is reached.");
			break;
		}			
	}

	if(cBrackets[MASTER_PROCESS_RANK] > 0)
		cBrackets[MASTER_PROCESS_RANK]--;

	unsigned int nSizePerProcess = (nFileSize - cBrackets[MASTER_PROCESS_RANK]) / (nNumberOfProcess-1);
	unsigned int nResidualData = (nFileSize - cBrackets[MASTER_PROCESS_RANK]) % (nNumberOfProcess-1);
		
	for(unsigned int nProcessIndex = 1; nProcessIndex < nNumberOfProcess; nProcessIndex++)
	{		
		cBrackets[nProcessIndex] = nSizePerProcess * nProcessIndex;
		PRINT_DEBUG_MESSAGE("1. Before arranged cBrackets[" << nProcessIndex << "] = " << cBrackets[nProcessIndex]);
		
		if(nResidualData > 0)
		{
			cBrackets[nProcessIndex]++;
			nResidualData--;
		}
		PRINT_DEBUG_MESSAGE("2. Before arranged cBrackets[" << nProcessIndex << "] = " << cBrackets[nProcessIndex]);
		
		if(cBrackets[nProcessIndex-1] < (nFileSize - 1))
		{
			if(cBrackets[nProcessIndex-1] >= cBrackets[nProcessIndex])
				cBrackets[nProcessIndex] = cBrackets[nProcessIndex - 1] + 1;
		}
		else
		{
			cBrackets[nProcessIndex] = nFileSize - 1;
			continue;
		}

		PRINT_DEBUG_MESSAGE("1. After arranged cBrackets[" << nProcessIndex << "] = " << cBrackets[nProcessIndex]);
		
		while(cBrackets[nProcessIndex] < (nFileSize-1))
		{
			if(pcInputFile[cBrackets[nProcessIndex]] != '\t' && pcInputFile[cBrackets[nProcessIndex]] != ' '  && pcInputFile[cBrackets[nProcessIndex]] != '\n')
				cBrackets[nProcessIndex]++;
			else
				break;
		}

		PRINT_DEBUG_MESSAGE("2. After arranged cBrackets[" << nProcessIndex << "] = " << cBrackets[nProcessIndex]);
		
		while(cBrackets[nProcessIndex] < (nFileSize-1))
		{
			if(pcInputFile[cBrackets[nProcessIndex]] == '\t' || pcInputFile[cBrackets[nProcessIndex]] == ' '  || pcInputFile[cBrackets[nProcessIndex]] == '\n')
				cBrackets[nProcessIndex]++;
			else
			{
				cBrackets[nProcessIndex]--;
				break;
			}
		}

		PRINT_DEBUG_MESSAGE("3. After arranged cBrackets[" << nProcessIndex << "] = " << cBrackets[nProcessIndex]);

		
	}

}


