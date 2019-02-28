#include "enode.h"


ENode::ENode(int nItem, ENode *pcNext, ENode *pcPrev)
{
	m_pcNext = pcNext;
	m_pcPrev = pcPrev;
	m_tData = nItem;
}


void ENode::InsertNext(ENode *pcNext)
{
	pcNext->m_pcNext = m_pcNext;
	m_pcNext = pcNext;

	pcNext->m_pcPrev = this;
	if(pcNext->m_pcNext != NULL)
		pcNext->m_pcNext->m_pcPrev = pcNext;

}


void ENode::InsertPrev(ENode *pcPrev)
{
	pcPrev->m_pcPrev = m_pcPrev;
	m_pcPrev = pcPrev;

	pcPrev->m_pcNext = this;
	if(pcPrev->m_pcPrev != NULL)
		pcPrev->m_pcPrev->m_pcNext = pcPrev;
}


ENode* ENode::DeleteNode()
{
	if(m_pcNext == NULL && m_pcPrev == NULL)
	{// If the node is the only element. 

		
	}
	else if(m_pcPrev == NULL)
	{// If the  node is the first element.

		m_pcNext->m_pcPrev = NULL;
		m_pcNext = NULL;

	}
	else if(m_pcNext == NULL)
	{ // If the node is the last element.

		m_pcPrev->m_pcNext = NULL;
		m_pcPrev = NULL;

	}
	else
	{
		m_pcNext->m_pcPrev = m_pcPrev;
		m_pcPrev->m_pcNext = m_pcNext;

		m_pcNext = NULL;
		m_pcPrev = NULL;

	}

	return this;
}


ENode* ENode::NextNodeNext() const
{
	return m_pcNext;
}


ENode* ENode::NextNodePrev() const
{
	return m_pcPrev;
}

