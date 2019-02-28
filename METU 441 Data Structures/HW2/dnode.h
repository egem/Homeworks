#ifndef __DNODE_H__
#define __DNODE_H__

template <class T>
class DNode
{
	private:
		DNode<T> *m_pcPrev;
		DNode<T> *m_pcNext;

	public:
		T m_tData;

		DNode();
		DNode(const T& rtItem);

		void InsertNext(DNode<T> *pcNext);
		void InsertPrev(DNode<T> *pcPrev);

		DNode<T>* DeleteNode();

		DNode<T>* NextNodeNext() const;
		DNode<T>* NextNodePrev() const;

};


#endif
