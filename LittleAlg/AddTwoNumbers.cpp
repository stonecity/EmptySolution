#include "stdafx.h"
#include "AddTwoNumbers.h"
#include <assert.h>


ListNode* AddTwoNumbersClass::AddTwoNumbers(ListNode* l1, ListNode* l2)
{
	int advanceNum = 0;
	ListNode *result = NULL, *returnRes = NULL;

	while (true)
	{
		if (l1 == NULL && l2 == NULL)
		{
			if (advanceNum == 1)
			{
				//assert(result);
				result->next = new ListNode(advanceNum);
			}

			break;
		}

		if (result == NULL)
		{
			result = new ListNode(0);
			returnRes = result;
		}
		else
		{
			result->next = new ListNode(0);
			result = result->next;
		}

		int num1 = 0;
		int num2 = 0;

		if (l1 != NULL)
		{
			num1 = l1->val;
			l1 = l1->next;
		}

		if (l2 != NULL)
		{
			num2 = l2->val;
			l2 = l2->next;
		}

		int sum = num1 + num2 + advanceNum;
		if (sum < 10)
		{
			result->val = sum;
			advanceNum = 0;
		}
		else
		{
			int curNum = sum - 10;
			result->val = curNum;
			advanceNum = 1;
		}
	}

	return returnRes;
}
