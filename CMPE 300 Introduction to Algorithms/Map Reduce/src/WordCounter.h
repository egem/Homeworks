#ifndef __WORDCOUNTER_H__
#define __WORDCOUNTER_H__

#include <iostream>
#include <cstring>
#include <map>

#define MAX_CHAR_ALLOWABLE_IN_WORD 50

struct WordMap
{
	char pcWord[MAX_CHAR_ALLOWABLE_IN_WORD];
	unsigned int nWordCount;
};

class WordCounter
{
	// Attributes
	private:

	public:

	// Methods
	private:

	public:
		static std::map<std::string, unsigned int> Map(std::string strInput);

		static void ConvertMaptoStruct(const std::map<std::string, unsigned int>& cWordMap, WordMap* pstWordMap);

		static void Merge(std::map<std::string, unsigned int>& cWordMap, WordMap* pstWordMap, unsigned int nNumberOfDistinctWord);

		static void PrintResult(const std::map<std::string, unsigned int>& cWordMap);
};

#endif
