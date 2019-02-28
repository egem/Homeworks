#include "node.h"

#include <iostream>


template <class T>
Node<T>::Node(const T &rtItem, Node<T>* pcNext)
:m_tData(rtItem), m_pcNext(pcNext)
{
	
}

template <class T>
Node<T>* Node<T>::NextNode() const
{
	return m_pcNext;	
}

template <class T>
void Node<T>::InsertAfter(Node<T>* pcNode)
{
	pcNode->m_pcNext = m_pcNext; 
	m_pcNext = pcNode;
	
}

template <class T>
Node<T>* Node<T>::DeleteAfter()
{
	// Save address of the node to be deleted
	Node<T> *tempPtr = m_pcNext;

	// If no successor, return NULL
	if(m_pcNext == NULL)
		return NULL;

	// Delete next node by copying its m_pcNext to the m_pcNext of the current node
	m_pcNext = tempPtr->m_pcNext;

	// Return pointer to deleted node
	return tempPtr;
}

template <class T>
Node<T>* GetNode(const T& rtItem, Node<T>* pcNext = 0)
{
	Node<T> *newNode = new Node<T>(rtItem, pcNext);

	if(newNode == NULL)
		std::cerr << "Memory allocation failed at " << __FILE__ << " Line: " << __LINE__ << std::endl;

	return newNode;
}

template class Node<int>;


