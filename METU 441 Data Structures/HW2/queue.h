#ifndef __QUEUE_H__
#define __QUEUE_H__

const int MAX_QUEUE_SIZE = 50;

template <class T>
class Queue
{
	private:
		T m_tQList[MAX_QUEUE_SIZE];
		
	public:
		int m_nFront, m_nRear, m_nCount;
		Queue();

		void QInsert(const T &rtData);

		T QDelete();
		void ClearQueue();
		
		T QFront() const;
		int QLength() const;
		bool QEmpty() const;
		bool QFull() const;
};
#endif
