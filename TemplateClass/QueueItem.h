////User-defined template class -- Queue
////

#ifndef QUEUEITEM_H_
#define QUEUEITEM_H_

#include <iostream>

template<class Type> class Queue;

template<class T> 
std::ostream& operator<<(std::ostream&, const Queue<T>&);

template<class Type> class QueueItem
{
	friend class Queue<Type>;
	friend std::ostream& 
		operator<< <Type> (std::ostream&, const Queue<Type>&);
public:
	QueueItem(const Type &t) : item(t), next(0){}
	Type item;
	QueueItem *next;
};

// Queue class
template<class Type> class Queue
{
public:
	Queue() : head(0), tail(0){}
	//copy elements
	Queue(const Queue& q) : head(0), tail(0)
	{
		copy_elems(q);
	}
	Queue& operator=(const Queue&);
	template<class It> Queue(It beg, It end)
	{
		copy_elems(beg, end);
	}
	template<class It> void assign(It beg, It end)
	{
		destroy();
		copy_elems(beg, end);
	}
	~Queue()
	{
		destroy();
	}
	Type& front()
	{
		return head->item;
	}
	const Type& front() const
	{
		return head->item;
	}
	void push(const Type&);
	void pop();
	bool empty() const
	{
		return (head == 0);
	}	
	QueueItem<Type> *head;		//header pointer
	QueueItem<Type> *tail;		//tail pointer

private:	
	void destroy();		/***clear Queue elements***/
	void copy_elems(const Queue&);

private:
	template<class Iter> void copy_elems(Iter beg, Iter end){
		while(beg != end)
		{
			push(*beg);
			++beg;
		}
	}
};

#endif