#include "ProcessManager.h"

void ProcessManager::EliminatePassiveProcesses(std::vector<unsigned int>& cBracketsList)
{
	for(std::vector<unsigned int>::reverse_iterator cIterator = cBracketsList.rbegin()+1; cIterator != cBracketsList.rend(); cIterator++)
	{
		if(*cIterator == *(cBracketsList.rbegin()))
			cBracketsList.erase(--cIterator.base());
		else
			break;
			
	}
}
