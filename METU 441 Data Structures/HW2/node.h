#ifndef __NODE_H__
#define __NODE_H__

// Decleration of the node class

template <class T>
class Node
{
	private:
		Node <T> *m_pcNext;
		
	
	public:

		T m_tData;

		// Constructor
		Node(const T &rtItem, Node<T>* pcNext = 0);

		// List modification
		void InsertAfter(Node<T> *pcNode);
		Node<T>* DeleteAfter();

		// Access to pointers
		Node<T>* NextNode() const;

		static Node<T>* GetNode(const T& rtItem, Node<T>* pcNext = 0);

};

#endif
