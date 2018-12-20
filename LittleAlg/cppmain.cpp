#include "stdafx.h"
#include "TwoSum.h"
#include <iostream>
using namespace std;

int _tmain()
{
	vector<int> inputs;
	inputs.push_back(2);
	inputs.push_back(7);
	inputs.push_back(11);
	inputs.push_back(15);

	TwoSum *ts = new TwoSum;
	vector<int> result = ts->twoSum(inputs, 9);

	for (vector<int>::iterator it = result.begin(); it != result.end(); it++)
	{
		cout << *it << endl;
	}
}