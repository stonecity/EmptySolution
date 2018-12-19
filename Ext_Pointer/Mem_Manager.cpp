#include "stdafx.h"

#include <iostream>
#include <string.h>
using namespace std;

typedef struct _DATA_
{
	char szName[20];
	int iAge;
}Data, *pData;


typedef struct _NODE_
{
	Data DataTemp;
	_NODE_* pNext;
}Node, *pNode;


class CList
{
public:
	CList()
	{
		m_pHead = m_pTail = NULL;
	}

	~CList()
	{
	}

	pNode GetNode(Data DataTemp);
	int GetNodeCount();

	//创建一个结点
	pNode CreateNode(Data DataTemp, CList& FreeListObj);

	//连接
	void LinkNode(pNode pNodeTemp);

	//将结点移回 内存池
	void RemoveNode(pNode pNodeTemp, CList& FreeListObj);

	//从内存池链表中提取结点
	pNode AllocateNode();

	//回收结点
	bool RecycleNode(pNode pNodeTemp);

	bool TravelList();

private:
	pNode m_pHead;
	pNode m_pTail;
	int m_iNodeCount;

};

//创建一个结点，参数为数据的结构体，内存池链表的引用（指针）
pNode CList::CreateNode(Data DataTemp, CList& FreeListObj)
{
	pNode pNodeTemp = NULL;        //申请一个结点的指针

	int iNodeCount = FreeListObj.GetNodeCount();
	//判断内存池链表有无内存结点

	//如果内存池当中存在结点，那么直接从内存池中提取出来（直接用）
	if (iNodeCount > 0)
	{
		pNodeTemp =	FreeListObj.AllocateNode();

		cout << "FreeList" << endl;
	}
	else
	{
		//如果内存池也是空的，那么申请新的结点
		pNodeTemp = new Node;

		cout << "New" << endl;
	}

	//如果申请成功或者从内存池提取成功
	if (pNodeTemp != NULL)
	{
		pNodeTemp->DataTemp = DataTemp;

		pNodeTemp->pNext = NULL;

		return pNodeTemp;
	}
	else
	{
		//如果不成功
		return NULL;
	}
}

//结点的连接
void CList::LinkNode(pNode pNodeTemp)
{
	//如果头结点是空，说明该结点是第一结点，那么头尾指针如下赋值
	if (m_pHead == NULL)
	{
		m_pHead = m_pTail = pNodeTemp;
	}
	else
	{
		m_pTail->pNext = pNodeTemp;

		m_pTail = pNodeTemp;
	}

	//结点的数量统计
	m_iNodeCount++;
}


//将结点移回 内存池  参数: 结点指针，内存池引用（指针）
//链表中移除的同时，将移除的结点送入内存池中
void CList::RemoveNode(pNode pNodeTemp, CList& FreeListObj)
{
	//头结点处理: 头结点下移即可
	if (pNodeTemp == m_pHead)
	{
		m_pHead = m_pHead->pNext;
	}
	else if (pNodeTemp == m_pTail)
	{
		//尾结点处理: 通过头去找，找到尾结点的前一个结点，
		//将其设置为尾结点并将pNext设置为空
		pNode pNodePre = m_pHead;
		while (pNodePre->pNext != pNodeTemp)
		{
			pNodePre = pNodePre->pNext;
		}

		pNodePre->pNext = NULL;

		m_pTail = pNodePre;
	}
	else
	{
		//一般情况处理
		pNode pNodePre = m_pHead;
		while (pNodePre->pNext != pNodeTemp)
		{
			pNodePre = pNodePre->pNext;
		}

		pNodePre->pNext = pNodeTemp->pNext;
	}

	m_iNodeCount--;

	if (m_iNodeCount == 0)
	{
		m_pTail = NULL;
	}

	//回收结点
	//链表中移除的同时，将移除的结点送入内存池中
	if (!FreeListObj.RecycleNode(pNodeTemp))
	{
		cout << "Error" << endl;
	}
}

int CList::GetNodeCount()
{
	if (m_pHead == NULL)
	{
		return 0;
	}
	else
	{
		return m_iNodeCount;
	}
}

pNode CList::GetNode(Data DataTemp)
{
	pNode pNodeTemp = m_pHead;
	while (pNodeTemp != NULL)
	{
		if (strcmp(pNodeTemp->DataTemp.szName, DataTemp.szName) == 0)
		{
			return pNodeTemp;
		}

		pNodeTemp = pNodeTemp->pNext;
	}

	return NULL;
}

//从内存池链表中提取一个结点
//前提:内存池中有结点，这个前面会判断，所以这里没问题
pNode CList::AllocateNode()
{
	if (m_pHead == m_pTail)
	{
		m_pTail = NULL;
	}

	pNode pNodeTemp = m_pHead;

	m_pHead = m_pHead->pNext;

	pNodeTemp->pNext = NULL;

	m_iNodeCount--;

	return pNodeTemp;
}

//回收结点到内存池
//直接插入到内存池，结束战斗
bool CList::RecycleNode(pNode pNodeTemp)
{
	if (pNodeTemp != NULL)
	{
		pNodeTemp->pNext = m_pHead;

		m_pHead = pNodeTemp;

		m_iNodeCount++;

		return true;
	}

	return false;
}

bool CList::TravelList()
{
	if (m_pHead == NULL)
	{
		return false;
	}

	pNode pNodeTemp = m_pHead;

	while (pNodeTemp != NULL)
	{
		cout << pNodeTemp->DataTemp.szName << "  "
			<< pNodeTemp->DataTemp.iAge << endl;

		pNodeTemp = pNodeTemp->pNext;
	}

	return true;
}

int a_main()
{
	CList CurrentList;
	CList FreeList;

	int iNum = 0;

	Data DataTemp = { 0 };

	pNode pNodeTemp = NULL;

	cout << "Input Num" << endl;
	cin >> iNum;

	while (iNum)
	{
		cout << "Input Name Age" << endl;

		cin >> DataTemp.szName;
		cin >> DataTemp.iAge;

		pNodeTemp = CurrentList.CreateNode(DataTemp, FreeList);

		CurrentList.LinkNode(pNodeTemp);

		iNum--;
	}

	CurrentList.TravelList();

	bool bOk = true;
	int iMethod;

	while (bOk)
	{
		cout << "1.  Insert" << endl;
		cout << "2.  Remove" << endl;
		cout << "30.  Exit" << endl;

		cin >> iMethod;

		switch (iMethod)
		{
		case 1:
			cout << "Input Name Age" << endl;

			cin >> DataTemp.szName;
			cin >> DataTemp.iAge;

			pNodeTemp = CurrentList.CreateNode(DataTemp, FreeList);
			CurrentList.LinkNode(pNodeTemp);

			CurrentList.TravelList();

			break;
		case 2:
			cout << "Input DataTemp To Remove" << endl;

			cin >> DataTemp.szName;
			cin >> DataTemp.iAge;

			pNodeTemp = CurrentList.GetNode(DataTemp);

			if (pNodeTemp == NULL)
			{
				cout << "No Data." << endl;
			}
			else
			{
				CurrentList.RemoveNode(pNodeTemp, FreeList);
			}

			CurrentList.TravelList();
			break;

		case 30:
			bOk = false;
			break;
		}
	}

	return 0;
}