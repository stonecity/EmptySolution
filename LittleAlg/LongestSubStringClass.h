#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
using namespace stdext;
using std::string;

class LongestSubStringClass
{
public:
	int GetLengthOfLongestSubstring(string s);

private:
	string formatString(string input);
};

