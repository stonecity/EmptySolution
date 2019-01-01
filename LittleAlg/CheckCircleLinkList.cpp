// CheckCircleLink.cpp : �������̨Ӧ�ó������ڵ㡣
// ��������Ƿ��ǻ�

#include "stdafx.h"
#include <iostream>
using namespace std;

struct Node
{
	int obj;
	Node *next;
};

bool CheckCircle(Node *node)
{
	Node *slow, *fast;
	slow = node;  // ��һ��
	fast = node->next; // �ڶ���
	while (fast->next != NULL)
	{
		// ����ǻ���������һ��Node���տ϶���͵ڶ���Node����
		if (fast == slow)
		{
			return true;
		}

		// �������Ľڵ㣬�������NULL��˵�����ǻ�������
		if ((fast = fast->next) == NULL)
		{
			return false;
		}
	}

	return false;
}

Node* ReverseLinklist(Node *node)
{
	Node *p1 = node->next;
	Node *p2 = node->next->next;
	node->next = NULL;
	p1->next = node;
	while (p2)
	{
		Node *temp = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = temp;
	}

	return p1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Node *node1 = new Node;
	node1->obj = 1;
	Node *node2 = new Node;
	node2->obj = 2;
	node1->next = node2;
	Node *node3 = new Node;
	node3->obj = 3;
	node2->next = node3;
	Node *node4 = new Node;
	node4->obj = 4;
	node4->next = NULL;
	node3->next = node4;

	Node* newLink = ReverseLinklist(node1);

	// Create Linklist
	Node *link = new Node;  // first
	if (link == NULL)
	{
		cout << "NULL" << endl;
	}

	link->next = new Node;	   // second
	link->next->next = new Node;	 // third	
	link->next = link;

	// determination
	if (CheckCircle(link))
		cout << "it is a circle" << endl;
	else
		cout << "not a circle" << endl;

	return 0;
}

