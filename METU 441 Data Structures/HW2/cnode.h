#ifndef __CNODE_H__
#define __CNODE_H__

template <class T>
class CNode
{
	private:
		CNode<T> *m_pcNext;

	public: 
		T m_tData;

		// Constructors
		CNode();
		CNode(const T& rtItem);

		void InsertAfter(CNode<T> *pcNode);
		CNode<T>* DeleteAfter();

		CNode<T>* NextNode() const;
	
	
};

#endif
