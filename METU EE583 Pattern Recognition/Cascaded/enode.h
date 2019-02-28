#ifndef __ENODE_H__
#define __ENODE_H__

#include <iostream>


class ENode
{
	private: 
		ENode *m_pcNext;
		ENode *m_pcPrev;
		

	public:
		int m_tData;
		
		ENode(int nItem, ENode *pcNext = NULL, ENode *pcPrev = NULL);

		void InsertNext(ENode *pcNext);
		void InsertPrev(ENode *pcPrev);

		ENode* DeleteNode();

		ENode* NextNodeNext() const;
		ENode* NextNodePrev() const;
};


#endif 
