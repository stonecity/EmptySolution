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

	//����һ�����
	pNode CreateNode(Data DataTemp, CList& FreeListObj);

	//����
	void LinkNode(pNode pNodeTemp);

	//������ƻ� �ڴ��
	void RemoveNode(pNode pNodeTemp, CList& FreeListObj);

	//���ڴ����������ȡ���
	pNode AllocateNode();

	//���ս��
	bool RecycleNode(pNode pNodeTemp);

	bool TravelList();

private:
	pNode m_pHead;
	pNode m_pTail;
	int m_iNodeCount;

};

//����һ����㣬����Ϊ���ݵĽṹ�壬�ڴ����������ã�ָ�룩
pNode CList::CreateNode(Data DataTemp, CList& FreeListObj)
{
	pNode pNodeTemp = NULL;        //����һ������ָ��

	int iNodeCount = FreeListObj.GetNodeCount();
	//�ж��ڴ�����������ڴ���

	//����ڴ�ص��д��ڽ�㣬��ôֱ�Ӵ��ڴ������ȡ������ֱ���ã�
	if (iNodeCount > 0)
	{
		pNodeTemp =	FreeListObj.AllocateNode();

		cout << "FreeList" << endl;
	}
	else
	{
		//����ڴ��Ҳ�ǿյģ���ô�����µĽ��
		pNodeTemp = new Node;

		cout << "New" << endl;
	}

	//�������ɹ����ߴ��ڴ����ȡ�ɹ�
	if (pNodeTemp != NULL)
	{
		pNodeTemp->DataTemp = DataTemp;

		pNodeTemp->pNext = NULL;

		return pNodeTemp;
	}
	else
	{
		//������ɹ�
		return NULL;
	}
}

//��������
void CList::LinkNode(pNode pNodeTemp)
{
	//���ͷ����ǿգ�˵���ý���ǵ�һ��㣬��ôͷβָ�����¸�ֵ
	if (m_pHead == NULL)
	{
		m_pHead = m_pTail = pNodeTemp;
	}
	else
	{
		m_pTail->pNext = pNodeTemp;

		m_pTail = pNodeTemp;
	}

	//��������ͳ��
	m_iNodeCount++;
}


//������ƻ� �ڴ��  ����: ���ָ�룬�ڴ�����ã�ָ�룩
//�������Ƴ���ͬʱ�����Ƴ��Ľ�������ڴ����
void CList::RemoveNode(pNode pNodeTemp, CList& FreeListObj)
{
	//ͷ��㴦��: ͷ������Ƽ���
	if (pNodeTemp == m_pHead)
	{
		m_pHead = m_pHead->pNext;
	}
	else if (pNodeTemp == m_pTail)
	{
		//β��㴦��: ͨ��ͷȥ�ң��ҵ�β����ǰһ����㣬
		//��������Ϊβ��㲢��pNext����Ϊ��
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
		//һ���������
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

	//���ս��
	//�������Ƴ���ͬʱ�����Ƴ��Ľ�������ڴ����
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

//���ڴ����������ȡһ�����
//ǰ��:�ڴ�����н�㣬���ǰ����жϣ���������û����
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

//���ս�㵽�ڴ��
//ֱ�Ӳ��뵽�ڴ�أ�����ս��
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