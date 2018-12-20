#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


vector<int> twoSum(vector<int>& nums, int target)
{
	vector<int> result;
	for (vector<int>::size_type i = 0; i < nums.size(); i++)
	{
		int ele1 = nums[i];

		for (vector<int>::size_type j = i; j < nums.size(); j++)
		{
			int ele2 = nums[j];

			if (ele1 + ele2 == target)
			{
				result.push_back(ele1);
				result.push_back(ele2);
				break;
			}
		}
	}

	return result;
}
