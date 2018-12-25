#include "stdafx.h"
#include "LongestSubStringClass.h"


int LongestSubStringClass::GetLengthOfLongestSubstring(string s) {
	//int len = 0;
	//unordered_map<char, int> mapSubString;
	//for (int i = 0; i < s.length(); i++) {
	//	char c = s.at(i);

	//	unordered_map<char, int>::iterator it = mapSubString.find(c);
	//	if (it != mapSubString.end()) {

	//		// 已存在相同的字符
	//		if (len < mapSubString.size()) {
	//			len = mapSubString.size();
	//		}

	//		mapSubString.erase(mapSubString.begin(), it);
	//	}

	//	// 不存在重复的字符
	//	mapSubString.insert(make_pair(c, i));
	//}

	//if (len < mapSubString.size()) {
	//	len = mapSubString.size();
	//}

	//return len;

	size_t strLen = s.length();
	size_t answer = 0;
	size_t index[128] = { 0 };

	for (size_t j = 0, i = 0; j < strLen; j++)
	{
		char c = s.at(j);
		if (index[c] > i) 
		{
			i = index[c];
		}

		if (answer < j - i + 1) 
		{
			answer = j - i + 1;
		}

		index[c] = j + 1;
	}

	return answer;
}

string LongestSubStringClass::formatString(string input) {
	assert(input.length() < 2);
	string result;
	for (size_t i = 1; i < input.length() - 1; i++) {
		char currentChar = input[i];
		if (input[i] == '\\') {
			char nextChar = input[i + 1];
			switch (nextChar) {
			case '\"': result.push_back('\"'); break;
			case '/': result.push_back('/'); break;
			case '\\': result.push_back('\\'); break;
			case 'b': result.push_back('\b'); break;
			case 'f': result.push_back('\f'); break;
			case 'r': result.push_back('\r'); break;
			case 'n': result.push_back('\n'); break;
			case 't': result.push_back('\t'); break;
			default: break;
			}

			i++;
		}
		else {
			result.push_back(currentChar);
		}
	}

	return result;
}