#include "treenode.h"

#include <iostream>

template <class T>
TreeNode<T>::TreeNode(const T &rtItem, TreeNode<T> *pcLeft, TreeNode<T> *pcRight)
:m_tData(rtItem), m_pcLeft(pcLeft), m_pcRight(pcRight)
{
	
}

template <class T>
TreeNode<T>* TreeNode<T>::Left() const
{
	return m_pcLeft;
}

template <class T>
TreeNode<T>* TreeNode<T>::Right() const
{
	return m_pcRight;
}

template <class T>
TreeNode<T>* TreeNode<T>::GetTreeNode(T tItem, TreeNode<T>* pcLeft, TreeNode<T>* pcRight)
{
	TreeNode<T> *newTreeNode = new TreeNode<T>(tItem, pcLeft, pcRight);

	if(newTreeNode == NULL)
	{
		std::cerr << "Memory allocation failure at " << __FILE__ << " LINE: " << __LINE__ << std::endl;
	}
	
	return newTreeNode;

}

template <class T>
void TreeNode<T>::FreeTreeNode(TreeNode<T>* &pcTreeNode)
{
	if(pcTreeNode != NULL)
	{
		delete pcTreeNode;
		pcTreeNode = NULL;
	}

}

template <class T>
void TreeNode<T>::InOrder(TreeNode<T>* pcTreeNode)
{
	if(pcTreeNode != NULL)
	{
		InOrder(pcTreeNode->m_pcLeft);
		std::cout << "Data : " << pcTreeNode->m_tData << std::endl;
		InOrder(pcTreeNode->m_pcRight);
	}
		
}

template <class T>
void TreeNode<T>::PreOrder(TreeNode<T>* pcTreeNode)
{
	if(pcTreeNode != NULL)
	{
		std::cout << " Data : " << pcTreeNode->m_tData << std::endl;
		PreOrder(pcTreeNode->m_pcLeft);
		PreOrder(pcTreeNode->m_pcRight);
		
	}
}

template <class T>
void TreeNode<T>::PostOrder(TreeNode<T>* pcTreeNode)
{
	if(pcTreeNode != NULL)
	{
		PostOrder(pcTreeNode->m_pcLeft);
		PostOrder(pcTreeNode->m_pcRight);
		std::cout << "Data : " << pcTreeNode->m_tData << std::endl;
	}
}

template class TreeNode<int>;
template class TreeNode<float>;




