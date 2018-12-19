#include "stdafx.h"
#include <iostream>
#include <stdexcept>
using namespace std;
using std::out_of_range;

#include "QueueItem.h"

template<class Type> 
void Queue<Type>::copy_elems(const Queue &orig)
{
	for(QueueItem<Type> *pt = orig.head; pt; pt->next)
		push(pt->item);
}

template<class Type>
Queue<Type>& Queue<Type>::operator =(const Queue &rhs)
{
	if(this != &rhs)
	{
		destroy();
		copy_elems(rhs);
	}

	return *this;
}

//destroy elements
template<class Type> void Queue<Type>::destroy()
{
	while(!empty())
		pop();
}

template<class Type> void Queue<Type>::push(const Type &val)
{
	QueueItem<Type> *pt = new QueueItem<Type>(val);
	if(empty())
		head = tail = pt;
	else
	{
		tail->next = pt;
		tail = pt;
	}
}

template<class Type> void Queue<Type>::pop()
{
	QueueItem<Type> *p = head;
	head = head->next;
	delete p;
}

template<class Type>
ostream& operator<<(ostream& os, const Queue<Type>& Q)
{
	os << " < ";
	QueueItem<Type> *p;
	for(p = Q.head; p; p = p->next)
		os << p->item << " ";
	os << " > ";

	return os;
}