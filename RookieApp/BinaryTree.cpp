// BinaryTree.cpp : �������̨Ӧ�ó������ڵ㡣
//
// ʹ�ö�������� -- �ؼ�����ƽ��: ���������������ĸ߶�֮��֮��ľ���ֵ������1.

#include "stdafx.h"
#include <tchar.h>
#include <iostream>
using namespace std;

struct Node
{
	int id;
	int height;

	Node *left; // ���ӽڵ�
	Node *right; // ���ӽڵ�
};

// ǰ�����
void PrePrint(Node *node)
{
	if (NULL != node)
	{
		cout << node->id << " ";
		PrePrint(node->left);
		PrePrint(node->right);
	}
}

// �������
void InPrint(Node *node)
{
	if (NULL != node)
	{
		InPrint(node->left);
		cout << node->id << " ";
		InPrint(node->right);
	}
}

// �������
void PostPrint(Node *node)
{
	if (NULL != node)
	{
		PostPrint(node->left);
		PostPrint(node->right);
		cout << node->id << " ";
	}
}

// Find the Min
Node* FindMin(Node *node)
{
	if (NULL == node)
	{
		return NULL;
	}
	
	if (node->left == NULL)
	{
		return node;
	}

	return FindMin(node->left);
}

// Insert -- �ڶ���������ϲ���ڵ㣬��Ҫ��������ƽ��
Node* Insert(int value, Node *node)
{
	if (NULL == node)	// ���������Ե�ǰ�ڵ���Ϊ���ĸ��ڵ�
	{
		Node *newNode = new Node();
		newNode->id = value;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	else if (value < node->id)		// С�ڵ�ǰ���ĸ��ڵ��ֵ�����뵽��ǰ�������
	{
		node->left = Insert(value, node->left);
	}
	else if (value > node->id)		// ���ڵ�ǰ���ĸ��ڵ��ֵ�����뵽��ǰ�����ұ�
	{
		node->right = Insert(value, node->right);
	}

	return node;	// ���ص�ǰ��
}

// Delete -- ����������Ľڵ�ɾ����ɾ���������������BST����ƽ������
Node* Delete(int value, Node* node)
{
	Node *tmpNode;
	if (NULL == node)
	{
		return NULL;
	}
	else if (value < node->id)	
	{
		// �����ӽڵ㿪ʼ��
		node->left = Delete(value, node->left);
	}
	else if (value > node->id)
	{
		// �����ӽڵ㿪ʼ��
		node->right = Delete(value, node->right);
	}
	else if (NULL != node->left && NULL != node->right)	
	{
		// ֵ�����ҽڵ�ֵ���
		// ��ǰ�ڵ������ӽڵ�����ӽڵ�����
		// �������ӽڵ��滻Ҫɾ���Ľڵ�
		tmpNode = FindMin(node->right);  // �ҵ������ӽڵ�
		node->id = tmpNode->id;
		node->right = Delete(node->id, node->right);
	}
	else
	{
		// ɾ���ڵ㣬�ýڵ������1���ӽڵ�
		tmpNode = node;

		if (NULL == tmpNode->left)
		{
			node = node->right;
		}
		else if (NULL == tmpNode->right)
		{
			node = node->left;
		}

		delete tmpNode;
	}

	return node;
}

int Max(int a, int b)
{
	return (a > b) ? a : b;
}

int GetHeight(Node *node)
{
	if (NULL == node)
	{
		return 0;
	}

	int leftNode = GetHeight(node->left);
	int rightNode = GetHeight(node->right);
	return Max(leftNode, rightNode) + 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Binary Search Tree: ���ӽڵ��ֵ����ȸ��ڵ��ֵС�����ӽڵ��ֵ����ȸ��ڵ��ֵ��
	//				7
	//			   / \
	//            2   8
	//           / \   
	//          1   4
	//             / \
	//            3   5
	Node *bst = new Node();
	bst->id = 7;
	Node *node2 = new Node();
	node2->id = 2;
	Node *node3 = new Node();
	node3->id = 8;
	Node *node4 = new Node();
	node4->id = 1;
	Node *node5 = new Node();
	node5->id = 4;
	Node *node6 = new Node();
	node6->id = 3;
	Node *node7 = new Node();
	node7->id = 5;

	bst->left = node2;
	bst->right = node3;
	node2->left = node4;
	node2->right = node5;
	node5->left = node6;
	node5->right = node7;
	
	int h = GetHeight(bst);
	cout << h << endl;

	// ǰ�����
	PrePrint(bst);
	cout << endl;

	// �������
	InPrint(bst);
	cout << endl;
	
	// �������
	PostPrint(bst);
	cout << endl;

	// ����ֵΪ6�Ľڵ�
	Insert(6, bst);

	// ɾ��ֵΪ4�Ľڵ�
	Delete(4, bst);
	
	int h1 = GetHeight(bst);
	cout << h1 << endl;

	return 0;
}