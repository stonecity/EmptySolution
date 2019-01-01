#pragma once
#include "stdafx.h"

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {
	}
};

class AddTwoNumbersClass
{
public:
	ListNode* AddTwoNumbers(ListNode* l1, ListNode* l2);
};

