#ifndef __TREENODE_H__
#define __TREENODE_H__

#include <iostream>

template <class T>
class TreeNode
{
	private:
		TreeNode<T> *m_pcLeft;
		TreeNode<T> *m_pcRight;

	public:

		T m_tData;

		// Constructor
		TreeNode(const T &rtItem, TreeNode<T> *pcLeft = NULL, TreeNode<T> *pcRight = NULL);

		// Access methods for pointer fields
		TreeNode<T>* Left() const;
		TreeNode<T>* Right() const;

		// Global function to dynamically allocate memory for a new object
		static TreeNode<T>* GetTreeNode(T tItem, TreeNode<T>* pcLeft= NULL, TreeNode<T>* pcRight = NULL);

		static void FreeTreeNode(TreeNode<T>* &pcTreeNode);

		static void InOrder(TreeNode<T>* pcTreeNode);

		static void PreOrder(TreeNode<T>* pcTreeNode);

		static void PostOrder(TreeNode<T>* pcTreeNode);
		
		
		
};


#endif 
