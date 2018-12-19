// BinaryTree.cpp : 定义控制台应用程序的入口点。
//
// 使用二叉查找树 -- 关键在于平衡: 左子树和右子树的高度之差之差的绝对值不超过1.

#include "stdafx.h"
#include <tchar.h>
#include <iostream>
using namespace std;

struct Node
{
	int id;
	int height;

	Node *left; // 左子节点
	Node *right; // 右子节点
};

// 前序遍历
void PrePrint(Node *node)
{
	if (NULL != node)
	{
		cout << node->id << " ";
		PrePrint(node->left);
		PrePrint(node->right);
	}
}

// 中序遍历
void InPrint(Node *node)
{
	if (NULL != node)
	{
		InPrint(node->left);
		cout << node->id << " ";
		InPrint(node->right);
	}
}

// 后序遍历
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

// Insert -- 在二叉查找树上插入节点，需要保持树的平衡
Node* Insert(int value, Node *node)
{
	if (NULL == node)	// 空树，则以当前节点作为树的根节点
	{
		Node *newNode = new Node();
		newNode->id = value;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	else if (value < node->id)		// 小于当前树的根节点的值，插入到当前树的左边
	{
		node->left = Insert(value, node->left);
	}
	else if (value > node->id)		// 大于当前树的根节点的值，插入到当前树的右边
	{
		node->right = Insert(value, node->right);
	}

	return node;	// 返回当前树
}

// Delete -- 二叉查找树的节点删除，删除后的树必须满足BST的树平衡特性
Node* Delete(int value, Node* node)
{
	Node *tmpNode;
	if (NULL == node)
	{
		return NULL;
	}
	else if (value < node->id)	
	{
		// 往左子节点开始找
		node->left = Delete(value, node->left);
	}
	else if (value > node->id)
	{
		// 往右子节点开始找
		node->right = Delete(value, node->right);
	}
	else if (NULL != node->left && NULL != node->right)	
	{
		// 值与左右节点值相等
		// 当前节点有左子节点和右子节点的情况
		// 将最右子节点替换要删除的节点
		tmpNode = FindMin(node->right);  // 找到最右子节点
		node->id = tmpNode->id;
		node->right = Delete(node->id, node->right);
	}
	else
	{
		// 删除节点，该节点零个或1个子节点
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
	// Binary Search Tree: 左子节点的值必须比父节点的值小，右子节点的值必须比父节点的值大。
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

	// 前序遍历
	PrePrint(bst);
	cout << endl;

	// 中序遍历
	InPrint(bst);
	cout << endl;
	
	// 后序遍历
	PostPrint(bst);
	cout << endl;

	// 插入值为6的节点
	Insert(6, bst);

	// 删除值为4的节点
	Delete(4, bst);
	
	int h1 = GetHeight(bst);
	cout << h1 << endl;

	return 0;
}