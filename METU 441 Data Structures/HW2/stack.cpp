#include "stack.h"

#include <iostream>
#include <stdlib.h>
#include <cstring>

template <class T>
Stack<T>::Stack()
{
	m_nTop = -1;
}

template <class T>
void Stack<T>::Push(const T &tItem)
{
	if(!StackFull())
	{
		m_tStackList[++m_nTop] = tItem;
	}
	else
	{
		std::cerr << "Stack OverFlow! " << std::endl;
	}
}

template <class T>
T Stack<T>::Pop()
{
	if(!StackEmpty())
	{
		T tTempValue = m_tStackList[m_nTop--];
		return tTempValue;
	}
	else
	{
		std::cerr << "Stack is empty! " << std::endl;
		exit(1);
	}
}

template <class T>
void Stack<T>::ClearStack()
{
	m_nTop = -1;
}

template <class T>
T Stack<T>::Peek() const
{
	if(!StackEmpty())
	{
		return m_tStackList[m_nTop];
	}
	else
	{
		std::cerr << "Stack is empty!" << std::endl;
		exit(1);
	}
}

template <class T>
bool Stack<T>::StackEmpty() const
{
	if(m_nTop == -1)
		return true;
	else
		return false;
}

template <class T>
bool Stack<T>::StackFull() const
{
	if(m_nTop == MAX_STACK_SIZE -1)
		return true;
	else
		return false;
}

template <class T>
int Stack<T>::StackLength() const
{
	return (m_nTop+1);
}


template class Stack<int>;
template class Stack<float>;
template class Stack<double>;
template class Stack<char>;
template class Stack<std::string>;
template class Stack<int*>;
template class Stack<float*>;
template class Stack<double*>;
template class Stack<char*>;
template class Stack<std::string*>;











