#include "cnode.h"

#include <iostream>

template <class T>
CNode<T>::CNode()
{
	m_pcNext = this;
}

template <class T>
CNode<T>::CNode(const T& rtItem)
{
	m_pcNext = this;
	m_tData = rtItem;
}

template <class T>
CNode<T>* CNode<T>::NextNode() const
{
	return m_pcNext;
}

template <class T>
void CNode<T>::InsertAfter(CNode<T> *pcNode)
{	
	pcNode->m_pcNext = m_pcNext;

	m_pcNext = pcNode;
	
}

template <class T>
CNode<T>* CNode<T>::DeleteAfter()
{
	CNode<T> *tempNode = m_pcNext;

	if(m_pcNext == this)
		return NULL;

	m_pcNext = tempNode->m_pcNext;

	return tempNode;
	
}



