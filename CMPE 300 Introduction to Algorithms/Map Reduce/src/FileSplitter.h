#ifndef __FILESPLITTER_H__
#define __FILESPLITTER_H__

#include <iostream>
#include <vector>

class FileSplitter
{
	// Attributes
	private:

	public:

	// Methods
	private:
		
	public:
		static void SplitFile(char* pcInputFile, unsigned int nFileSize, unsigned int nNumberOfProcess, std::vector<unsigned int>& cBracketsList);
};

#endif
