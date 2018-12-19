
//
// 使用链表进行内存管理
//
#pragma once
#include "stdafx.h"
#include "LinkList_Mem.h"


//内容链表
Herror hlink_empty(HLink& link)
{
	link.header = 0;
	link.tail = 0;

	return 1;
}

Herror hlink_push_back(HLink& link, HNode* newNode)
{
	newNode->last = link.tail;
	newNode->next = 0;

	if (link.tail == 0)
	{
		link.tail = link.header = newNode;
	}
	else
	{
		link.tail->next = newNode;
		link.tail = newNode;
	}

	return 1;
}

Herror hlink_push_front(HLink& link, HNode* newNode)
{
	newNode->last = 0;
	newNode->next = link.header;

	if (0 == link.header)
	{
		link.header = link.tail = newNode;
	}
	else
	{
		link.header->last = newNode;
		link.header = newNode;
	}

	return 1;
}

Herror hlink_insert(HLink& link, void* data1, HNode* newNode)
{
	bool find = false;
	HNode* node = link.header;
	HNode* next;
	while (0 != node)
	{
		next = node->next;
		if (node->data == data1)
		{
			find = true;
			newNode->last = node;
			newNode->next = node->next;

			node->next = newNode;
			if (0 == next)
			{
				link.tail = newNode;
			}
			else
			{
				node->next->last = newNode;
			}
			break;
		}

		node = next;
	}

	if (find)
		return 1;

	return 0;
}

Herror hlink_delete(HLink& link, void* data, HNode* &nodeDel)
{
	HNode* node = link.header;
	HNode* next;
	bool find = false;
	while (0 != node)
	{
		next = node->next;
		if (data == node->data)
		{
			find = true;
			nodeDel = node;

			if (0 == next && 0 == node->last)
			{
				link.header = link.tail = 0;
			}
			else if (0 == next && 0 != node->last)
			{
				node->last->next = 0;
				link.tail = node->last;
			}
			else if (0 != next && 0 == node->last)
			{
				node->next->last = 0;
				link.header = node->next;
			}
			else
			{
				next->last = node->last;
				node->last->next = next;
			}

			break;
		}

		node = next;
	}

	return 1;
}

Herror hlink_find(HLink& link, void* data, HNode* &nodeFind)
{
	bool find = false;
	HNode* node = link.header;
	HNode* next;

	while (0 != node)
	{
		next = node->next;
		if (data == node->data)
		{
			nodeFind = node;
			find = true;
			break;
		}

		node = next;
	}

	if (find)
		return 1;

	return 0;
}

//删除链表
Herror hlinkdel_empty(HLinkDel& linkdel, unsigned int size, int nBuf)
{
	hlink_empty(linkdel.del);
	linkdel.size = size;
	linkdel.nBuf = nBuf;
	linkdel.index = -1;

	linkdel.buf = new HNode*[nBuf];
	for (int i = 0; i < nBuf; i++)
	{
		linkdel.buf[i] = 0;
	}

	hlinkdel_alloc(linkdel);
	return 1;
}

Herror hlinkdel_alloc(HLinkDel& linkdel)
{
	linkdel.index++;
	int n = linkdel.index;
	unsigned int len = linkdel.size * (1 << n);
	linkdel.buf[n] = new HNode[len];

	HNode* p;
	for (unsigned int i = 0; i < len; i++)
	{
		p = linkdel.buf[n] + i;
		p->data = 0;
		p->next = p + 1;
		p->last = p - 1;
	}

	p = linkdel.buf[n];
	p[len - 1].next = p[0].last = 0;
	linkdel.del.header = p;
	linkdel.del.tail = p + len - 1;

	return 1;
}

Herror hlinkdel_clear(HLinkDel& linkdel)
{
	for (int i = 0; i < linkdel.nBuf; i++)
	{
		delete[]linkdel.buf[i];
	}

	delete[]linkdel.buf;
	linkdel.buf = 0;
	hlink_empty(linkdel.del);
	linkdel.index = -1;
	linkdel.nBuf = 0;
	linkdel.size = 0;

	return 1;
}

Herror hlinkdel_pop(HLinkDel& linkdel, HNode* &node)
{
	HLink& del = linkdel.del;
	if (del.header != 0)
	{
		node = del.header;

		if (del.tail == node)
		{
			hlinkdel_alloc(linkdel);
		}
		else
		{
			del.header->next->last = 0;
			del.header = del.header->next;
		}
	}
	else if (del.header == 0)
	{
		hlinkdel_alloc(linkdel);
		hlinkdel_pop(linkdel, node);
	}

	return 1;
}

Herror hlinkdel_push(HLinkDel& linkdel, HNode* node)
{
	node->last = linkdel.del.tail;
	node->next = 0;
	linkdel.del.tail->next = node;
	linkdel.del.tail = node;

	return 1;
}

//链表管理
Herror hlist_emtpy(HList& list)
{
	hlink_empty(list.link);
	hlinkdel_empty(list.link_del);
	return 1;
}

Herror hlist_clear(HList& list)
{
	hlinkdel_clear(list.link_del);
	return 1;
}

Herror hlist_push_back(HList& list, void* data)
{
	HNode* newNode;
	hlinkdel_pop(list.link_del, newNode);
	newNode->data = data;
	hlink_push_back(list.link, newNode);
	return 1;
}

Herror hlist_push_front(HList& list, void* data)
{
	HNode* newNode;
	hlinkdel_pop(list.link_del, newNode);
	newNode->data = data;
	hlink_push_front(list.link, newNode);
	return 1;
}

Herror hlist_insert(HList& list, void* data1, void* data2)
{
	//产生新节点
	HNode* newNode;
	hlinkdel_pop(list.link_del, newNode);
	newNode->data = data2;

	//插入新节点
	hlink_insert(list.link, data1, newNode);
	return 1;
}

Herror hlist_delete(HList& list, void* data)
{
	//在内容链表中删除此节点
	HNode* nodeDel = 0;
	hlink_delete(list.link, data, nodeDel);

	//在删除链表中加入此节点
	if (nodeDel != 0)
	{
		hlinkdel_push(list.link_del, nodeDel);
	}
	else
	{
		return 0;
	}

	return 1;
}