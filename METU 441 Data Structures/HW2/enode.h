#ifndef __ENODE_H__
#define __ENODE_H__

#include <iostream>
#include "eecapsule.h"

class ENode
{
	private: 
		ENode *m_pcNext;
		ENode *m_pcPrev;
		

	public:
		EECapsule* m_tData;
		
		ENode(EECapsule* pcItem, ENode *pcNext = NULL, ENode *pcPrev = NULL);

		void InsertNext(ENode *pcNext);
		void InsertPrev(ENode *pcPrev);

		ENode* DeleteNode();

		ENode* NextNodeNext() const;
		ENode* NextNodePrev() const;
};


#endif 
