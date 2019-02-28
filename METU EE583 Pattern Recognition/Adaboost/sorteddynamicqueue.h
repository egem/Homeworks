#ifndef __SORTEDDYNAMICQUEUE_H__
#define __SORTEDDYNAMICQUEUE_H__

#include "enode.h"
#include <iostream>
#include <stdlib.h>



class SortedDynamicQueue
{
	private:
		ENode *m_pcFront;
		ENode *m_pcRear;
		int m_nCount;
		
	public:
		SortedDynamicQueue();
		SortedDynamicQueue(int pcItem);

		~SortedDynamicQueue();
		
		void QInsert(int pcItem);

		int QDelete();
		void ClearQueue();
		
		int QFront() const;
		int QLength() const;
		bool QEmpty() const;

		void PrintValues() const;

		
};


#endif



