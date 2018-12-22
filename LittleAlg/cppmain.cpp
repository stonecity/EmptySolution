#include "stdafx.h"
#include "TwoSum.h"
#include "AddTwoNumbers.h"
#include <iostream>
#include <vector>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	// ***** Add Two Numbers
	ListNode *l1 = new ListNode(2);
	l1->next = new ListNode(4);
	l1->next->next = new ListNode(3);

	ListNode *l2 = new ListNode(5);
	l2->next = new ListNode(6);
	l2->next->next = new ListNode(4);

	AddTwoNumbersClass *atn = new AddTwoNumbersClass;
	ListNode *atnResult = atn->AddTwoNumbers(l1, l2);
	if (atnResult != NULL) 
	{
		while (atnResult != NULL)
		{
			cout << atnResult->val;
			atnResult = atnResult->next;
		}
	}

	cout << "\n==========End==========" << endl;

	// ***** Two Sum
	vector<int> inputs;
	inputs.push_back(3);
	inputs.push_back(2);
	inputs.push_back(4);
	//inputs.push_back(15);

	TwoSumClass *ts = new TwoSumClass;
	vector<int> result = ts->twoSum(inputs, 6);

	for (vector<int>::iterator it = result.begin(); it != result.end(); it++)
	{
		cout << *it << " ";
	}

	cout << "\n" << "==========End==========" << endl;
}