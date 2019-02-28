#include "queue.h"

#include <iostream>
#include <stdlib.h>
#include <cstring>

template <class T>
Queue<T>::Queue()
:m_nFront(0), m_nRear(0), m_nCount(0)
{

}

template <class T>
void Queue<T>::QInsert(const T &rtData)
{
	if(!QFull())
	{
		m_tQList[m_nRear] = rtData;
		m_nRear = (m_nRear+1) % MAX_QUEUE_SIZE ; 
		m_nCount++;
	}
	else
	{
		std::cerr << "Queue is full!" << std::endl;
		exit(1);
	}
}

template <class T>
T Queue<T>::QDelete()
{
	if(!QEmpty())
	{
		T tTempValue = m_tQList[m_nFront];
		m_nFront = (m_nFront+1) % MAX_QUEUE_SIZE;
		m_nCount--;
		return tTempValue;
	}
	else
	{
		std::cerr << "Queue is empty!" << std::endl;
		exit(1);
	}
}

template <class T>
void Queue<T>::ClearQueue()
{	
	m_nCount = 0;
	m_nFront = 0;
	m_nRear = 0;
}

template <class T>
T Queue<T>::QFront() const
{
	if(!QEmpty())
	{
		return m_tQList[m_nFront];
	}
	else
	{
		std::cerr << "Queue is empty!" << std::endl;
		exit(1);
	}
}

template <class T>
int Queue<T>::QLength() const
{
	return m_nCount;
}

template <class T>
bool Queue<T>::QEmpty() const
{	
	if(m_nCount == 0)
		return true;
	else
		return false;
}

template <class T>
bool Queue<T>::QFull() const
{
	if(m_nCount == MAX_QUEUE_SIZE)
		return true;
	else
		return false;
}

template class Queue<int>;
template class Queue<float>;
template class Queue<double>;
template class Queue<char>;
template class Queue<std::string>;
template class Queue<int*>;
template class Queue<float*>;
template class Queue<double*>;
template class Queue<char*>;
template class Queue<std::string*>;














