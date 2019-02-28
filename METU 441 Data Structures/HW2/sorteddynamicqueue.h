#ifndef __SORTEDDYNAMICQUEUE_H__
#define __SORTEDDYNAMICQUEUE_H__

#include "enode.h"
#include <iostream>
#include <stdlib.h>
#include "eecapsule.h"



class SortedDynamicQueue
{
	private:
		ENode *m_pcFront;
		ENode *m_pcRear;
		int m_nCount;
		
	public:
		SortedDynamicQueue();
		SortedDynamicQueue(EECapsule* pcItem);

		~SortedDynamicQueue();
		
		void QInsert(EECapsule* pcItem);

		EECapsule* QDelete();
		void ClearQueue();
		
		EECapsule* QFront() const;
		int QLength() const;
		bool QEmpty() const;

		void PrintValues() const;

		
};


#endif



