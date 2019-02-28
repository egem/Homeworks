#include "WordCounter.h"
#include <algorithm>
#include <boost/tokenizer.hpp>
#include "Datatype.h"
#include <sstream>


std::map<std::string, unsigned int> WordCounter::Map(std::string strInput)
{
	boost::char_separator<char> sep(", .\t\n\"-");
   	boost::tokenizer< boost::char_separator<char> > tokens(strInput, sep);

	std::map<std::string, unsigned int> cWordMap;
	
	for(boost::tokenizer< boost::char_separator<char> >::iterator cIterator=tokens.begin(); cIterator != tokens.end(); ++cIterator)
    {
    	std::string strWord(*cIterator);
    	std::transform(strWord.begin(), strWord.end(), strWord.begin(), ::tolower);
    	PRINT_DEBUG_MESSAGE("Word : " << strWord);
		if(cWordMap.find(strWord) == cWordMap.end())
			cWordMap[strWord] = 1;
		else
			cWordMap[strWord]++;
    }

    return cWordMap;
	
}

void WordCounter::ConvertMaptoStruct(const std::map<std::string, unsigned int>& cWordMap, WordMap* pstWordMap)
{
	unsigned int nWordMapIndex = 0;
	for(std::map<std::string, unsigned int>::const_iterator cIterator=cWordMap.begin(); cIterator!=cWordMap.end(); ++cIterator)
	{
		std::copy(cIterator->first.begin(), cIterator->first.end(), pstWordMap[nWordMapIndex].pcWord);
		pstWordMap[nWordMapIndex].pcWord[cIterator->first.size()] = '\0';
		pstWordMap[nWordMapIndex].nWordCount = cIterator->second;
		nWordMapIndex++;

	}
}

void WordCounter::Merge(std::map<std::string, unsigned int>& cWordMap, WordMap* pstWordMap, unsigned int nNumberOfDistinctWord)
{
	for(int nWordMapIndex = 0; nWordMapIndex<nNumberOfDistinctWord; nWordMapIndex++)
	{
		std::string strWord(pstWordMap[nWordMapIndex].pcWord);
		if(cWordMap.find(strWord) == cWordMap.end())
			cWordMap[strWord] = pstWordMap[nWordMapIndex].nWordCount;
		else
			cWordMap[strWord] += pstWordMap[nWordMapIndex].nWordCount;
	}
}

void WordCounter::PrintResult(const std::map<std::string, unsigned int>& cWordMap)
{
	for(std::map<std::string, unsigned int>::const_iterator cIterator = cWordMap.begin(); cIterator!=cWordMap.end(); ++cIterator)
    	std::cout << cIterator->first << " => " << cIterator->second << "\n";
}

