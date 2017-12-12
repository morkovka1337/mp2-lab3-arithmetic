// ���������� � ���������� ���������� �����
// ���� ������������ ��������: 
// - ������� ��������, 
// - ���������� ��������, 
// - �������� �������� �������� (��� ��������)
// - �������� �� �������, 
// - ��������� ���������� ��������� � �����
// - ������� �����
// ��� ������� � ������ ���� ������ �������������� ������

#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 1000;

// ������ �����
template <class ValType>
class Stack
{
protected:
	ValType *pMem;
	int top;
	int Elements; // ���������� ��������� � �����
public:
	Stack(int s = 1000);
	~Stack() { delete[] pMem; };
	int GetElements();
	void Push(ValType d);
	int GetSize(){ return top; }
	ValType Eject();
	ValType Top();
	void Clean();
	bool IsEmpty();
	bool IsFull();
};

template <class ValType>
Stack<ValType>::Stack(int s = 1000)
{
	if (s<0 || s>MAX_VECTOR_SIZE)
		throw "error"; 
	Elements = s; 
	pMem = new ValType[s]; 
	top = 0; 
}

template <class ValType>
bool Stack<ValType>::IsFull()
{
	bool k = (top == Elements) ? true : false;
	return k;
}

template <class ValType>
bool Stack<ValType>::IsEmpty()
{
	return (top == 0);
}

template <class ValType>
void Stack<ValType>::Clean()
{
	top = 0;
}

template <class ValType>
ValType Stack<ValType>::Top()
{ 
	if (IsEmpty()) throw "stack is empty";
	return pMem[top - 1];
}
template <class ValType>
int Stack<ValType>::GetElements()
{
	return Elements;
}
template <class ValType>
ValType Stack<ValType>::Eject()
{
	ValType temp;
	if (IsEmpty()) throw "stack is empty";
	if (!IsEmpty())
	{
		temp = pMem[top - 1];
		top -= 1;
	}
	return temp;
}

template <class ValType>
void Stack<ValType>::Push(ValType d)
{
	if (IsFull())
	{
		ValType *temp;
		temp = new ValType[Elements + MAX_VECTOR_SIZE];
		for (int i = 0; i < Elements; i++)
			temp[i] = pMem[i];
		delete[] pMem;
		pMem = temp;
		Elements += MAX_VECTOR_SIZE;
	}
	pMem[top] = d;
	top += 1;
}
#endif




