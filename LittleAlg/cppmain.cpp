#include "stdafx.h"
#include "TwoSum.h"
#include <iostream>
#include <vector>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	vector<int> inputs;
	inputs.push_back(2);
	inputs.push_back(7);
	inputs.push_back(11);
	inputs.push_back(15);

	TwoSumClass *ts = new TwoSumClass;
	vector<int> result = ts->twoSum(inputs, 9);

	for (vector<int>::iterator it = result.begin(); it != result.end(); it++)
	{
		cout << *it << " ";
	}

	cout << "\n" << "End." << endl;
}