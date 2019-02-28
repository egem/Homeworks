#ifndef __STACK_H__
#define __STACK_H__

const int MAX_STACK_SIZE = 50;

template <class T>
class Stack
{
	private:
		
		T m_tStackList[MAX_STACK_SIZE];
		int m_nTop;

	public:
		Stack();
		void Push(const T &tItem);
		T Pop();

		void ClearStack();
		T Peek() const;

		int StackLength() const;
		bool StackEmpty() const;
		bool StackFull() const;
		
		
	
};

#endif
