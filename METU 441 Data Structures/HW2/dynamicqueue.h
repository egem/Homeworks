#ifndef __DYNAMICQUEUE_H__
#define __DYNAMICQUEUE_H__

#include "enode.h"
#include <iostream>
#include <stdlib.h>

#define DYNAMIC_QUEUE_DEBUG(str)		//do{ std::cout << str << std::endl; } while(false)
#define DYNAMIC_QUEUE_ERROR(str)		do{ std::cout << str << std::endl; } while(false)
#define DYNAMIC_QUEUE_FUNCTION(str)		//do{ std::cout << str << std::endl; } while(false)


template <class T>
class DynamicQueue
{
	private:
		ENode<T> *m_pcFront;
		ENode<T> *m_pcRear;
		int m_nCount;
		
	public:
		DynamicQueue();
		DynamicQueue(const T& rtItem);

		~DynamicQueue();
		
		void QInsert(const T& rtItem);

		T QDelete();
		void ClearQueue();
		
		T QFront() const;
		int QLength() const;
		bool QEmpty() const;

		void PrintValues() const;

		
};


template <class T>
DynamicQueue<T>::DynamicQueue()
{	
	DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	m_pcFront = NULL;
	m_pcRear = NULL;
	m_nCount = 0;
}

template <class T>
DynamicQueue<T>::DynamicQueue(const T& rtItem)
{
	ENode<T> *cNode = new ENode<T>(rtItem);
	m_pcFront = cNode;
	m_pcRear = cNode;
	m_nCount = 1;
}

template <class T>
DynamicQueue<T>::~DynamicQueue()
{	
	ENode<T> *curNode;

	while(!QEmpty())
	{
		curNode= m_pcFront;
		QDelete();
		delete curNode;
	}
}


template <class T>
void DynamicQueue<T>::QInsert(const T& rtItem)
{	
	DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);	

	DYNAMIC_QUEUE_DEBUG("[DYNAMIC_QUEUE][DEBUG] m_nCount = " << m_nCount);

	if(QEmpty())
	{
		ENode<T> *cNode = new ENode<T>(rtItem);
		m_pcFront = cNode;
		m_pcRear = cNode;
		m_nCount++;
	
		DYNAMIC_QUEUE_DEBUG("[DYNAMIC_QUEUE][DEBUG] Front		: " << m_pcFront->m_tData);		
		DYNAMIC_QUEUE_DEBUG("[DYNAMIC_QUEUE][DEBUG] Rear 		: " << m_pcRear->m_tData);
	}
	else
	{
		ENode<T> *cRear = new ENode<T>(rtItem);
		m_pcRear->InsertNext(cRear);
		m_pcRear = m_pcRear->NextNodeNext();
		m_nCount++;
		
		DYNAMIC_QUEUE_DEBUG("[DYNAMIC_QUEUE][DEBUG] Front		: " << m_pcFront->m_tData);		
		DYNAMIC_QUEUE_DEBUG("[DYNAMIC_QUEUE][DEBUG] Front Next	: " << m_pcFront->NextNodeNext()->m_tData);
		DYNAMIC_QUEUE_DEBUG("[DYNAMIC_QUEUE][DEBUG] Rear 		: " << m_pcRear->m_tData);
	}
	

}

template <class T>
T DynamicQueue<T>::QDelete()
{
	DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	if(QEmpty())
	{
		DYNAMIC_QUEUE_ERROR("[DYNAMIC_QUEUE][ERROR]Dynamic queue is already empty at FILE : " << __FILE__ << " LINE : " << __LINE__ );
		exit(1);
	}
	else
	{
		ENode<T> *pcTemp = m_pcFront;
		T tTempValue = m_pcFront->m_tData;
		m_pcFront = m_pcFront->NextNodeNext();
		m_nCount--;
		return tTempValue;
	}

}

template <class T>
void DynamicQueue<T>::ClearQueue()
{	
	DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);

	ENode<T> *curNode;
	
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

template <class T>
T DynamicQueue<T>::QFront() const
{
	DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	return m_pcFront->m_tData;
}

template <class T>
int DynamicQueue<T>::QLength() const
{
	DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	return m_nCount;
}

template <class T>
bool DynamicQueue<T>::QEmpty() const
{	
	DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	if(m_nCount == 0)
		return true;
	else
		return false;
}

template <class T>
void DynamicQueue<T>::PrintValues() const
{
	DYNAMIC_QUEUE_FUNCTION("[DYNAMIC_QUEUE][FUNCTION] FUNCTION : " << __FUNCTION__ << " FILE: " << __FILE__);
	ENode<T> *currNode;
	currNode = m_pcFront;

	while(currNode != NULL)
	{
		std::cout << currNode->m_tData << "  ";
		currNode = currNode->NextNodeNext();
	}

	std::cout << std::endl << std::endl;
}


#endif
