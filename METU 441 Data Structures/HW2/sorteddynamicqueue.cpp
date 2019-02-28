#include "sorteddynamicqueue.h"


#define SORTED_DYNAMIC_QUEUE_DEBUG(str)			//do{ std::cout << str << std::endl; } while(false)
#define SORTED_DYNAMIC_QUEUE_ERROR(str)			do{ std::cout << str << std::endl; } while(false)
#define SORTED_DYNAMIC_QUEUE_FUNCTION(str)		//do{ std::cout << str << std::endl; } while(false)

SortedDynamicQueue::SortedDynamicQueue()
{	
	SORTED_DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	m_pcFront = NULL;
	m_pcRear = NULL;
	m_nCount = 0;
}


SortedDynamicQueue::SortedDynamicQueue(EECapsule* pcItem)
{
	SORTED_DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	ENode *cNode = new ENode(pcItem);
	m_pcFront = cNode;
	m_pcRear = cNode;
	m_nCount = 1;
}


SortedDynamicQueue::~SortedDynamicQueue()
{	
	SORTED_DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	ENode *curNode;

	while(!QEmpty())
	{
		curNode= m_pcFront;
		QDelete();
		delete curNode;
	}
}


void SortedDynamicQueue::QInsert(EECapsule* pcItem)
{	
	SORTED_DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);

	SORTED_DYNAMIC_QUEUE_DEBUG("[DYNAMIC_QUEUE][DEBUG] m_nCount = " << m_nCount);

	if(QEmpty())
	{
		ENode *cNode = new ENode(pcItem);
		m_pcFront = cNode;
		m_pcRear = cNode;
		m_nCount++;
	
		SORTED_DYNAMIC_QUEUE_DEBUG("[DYNAMIC_QUEUE][DEBUG] Front		: " << m_pcFront->m_tData);		
		SORTED_DYNAMIC_QUEUE_DEBUG("[DYNAMIC_QUEUE][DEBUG] Rear 		: " << m_pcRear->m_tData);
	}
	else
	{
		ENode *currNode;
		currNode = m_pcFront;

		while(currNode != NULL)
		{
			if(*pcItem < *(currNode->m_tData))
			{
				if(currNode == m_pcFront)
					break;
				else
				{
					ENode *cNode = new ENode(pcItem);
					currNode->InsertPrev(cNode);
					break;
				}
			}

			currNode = currNode->NextNodeNext();
			
		}

		if(currNode == NULL)
		{
			ENode *cRear = new ENode(pcItem);
			m_pcRear->InsertNext(cRear);
			m_pcRear = m_pcRear->NextNodeNext();
		}
		else if(currNode == m_pcFront)
		{
			ENode *cFront = new ENode(pcItem);
			m_pcFront->InsertPrev(cFront);
			m_pcFront = m_pcFront->NextNodePrev();
		}
		
		m_nCount++;
		
		SORTED_DYNAMIC_QUEUE_DEBUG("[DYNAMIC_QUEUE][DEBUG] Front		: " << m_pcFront->m_tData);		
		SORTED_DYNAMIC_QUEUE_DEBUG("[DYNAMIC_QUEUE][DEBUG] Front Next	: " << m_pcFront->NextNodeNext()->m_tData);
		SORTED_DYNAMIC_QUEUE_DEBUG("[DYNAMIC_QUEUE][DEBUG] Rear 		: " << m_pcRear->m_tData);
	}
	

}


EECapsule* SortedDynamicQueue::QDelete()
{
	SORTED_DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	if(QEmpty())
	{
		SORTED_DYNAMIC_QUEUE_ERROR("[DYNAMIC_QUEUE][ERROR]Dynamic queue is already empty at FILE : " << __FILE__ << " LINE : " << __LINE__ );
		exit(1);
	}
	else
	{
		ENode *pcTemp = m_pcFront;
		EECapsule* tTempValue = m_pcFront->m_tData;
		m_pcFront = m_pcFront->NextNodeNext();
		m_nCount--;
		return tTempValue;
	}

}

void SortedDynamicQueue::ClearQueue()
{	
	SORTED_DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);

	ENode *curNode;
	
	while(!QEmpty())
	{
		curNode= m_pcFront;
		QDelete();
		delete curNode;
	}
	
	m_pcFront = NULL;
	m_pcRear = NULL;
	m_nCount = 0;
}


EECapsule* SortedDynamicQueue::QFront() const
{
	SORTED_DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	return m_pcFront->m_tData;
}


int SortedDynamicQueue::QLength() const
{
	SORTED_DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	return m_nCount;
}

bool SortedDynamicQueue::QEmpty() const
{	
	SORTED_DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	if(m_nCount == 0)
		return true;
	else
		return false;
}

void SortedDynamicQueue::PrintValues() const
{
	SORTED_DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	ENode *currNode;
	currNode = m_pcFront;

	while(currNode != NULL)
	{
		currNode->m_tData->PrintInfo();
		currNode = currNode->NextNodeNext();
	}

	
}

