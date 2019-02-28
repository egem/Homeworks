#include "dnode.h"

#include <iostream>

template <class T>
DNode<T>::DNode()
{
	m_pcNext = this;
	m_pcPrev = this;
}

template <class T>
DNode<T>::DNode(const T& rtItem)
{
	m_pcNext = this;
	m_pcPrev = this;

	m_tData = rtItem;
}

template <class T>
void DNode<T>::InsertNext(DNode<T> *pcNext)
{
	pcNext->m_pcNext = m_pcNext;
	m_pcNext = pcNext;

	pcNext->m_pcPrev = this;
	pcNext->m_pcNext->m_pcPrev = pcNext;
}

template <class T>
void DNode<T>::InsertPrev(DNode<T> *pcPrev)
{
	pcPrev->m_pcPrev = m_pcPrev; 
	m_pcPrev = pcPrev;

	m_pcPrev->m_pcNext = pcPrev; 
	pcPrev->m_pcNext = this; 
	
}

template <class T>
DNode<T>* DNode<T>::DeleteNode()
{
	if(m_pcNext == m_pcPrev)
		return NULL;

	m_pcPrev->m_pcNext = m_pcNext;
	m_pcNext->m_pcPrev = m_pcPrev;

	return this;

}

template <class T>
DNode<T>* DNode<T>::NextNodeNext() const
{
	return m_pcNext;
}

template <class T>
DNode<T>* DNode<T>::NextNodePrev() const
{
	return m_pcPrev;
}




