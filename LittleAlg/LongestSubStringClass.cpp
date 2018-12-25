#include "stdafx.h"
#include "LongestSubStringClass.h"


int LongestSubStringClass::GetLengthOfLongestSubstring(string s) {
	size_t len = 0;
	unordered_map<char, int> mapSubString;
	for (size_t i = 0; i < s.length(); i++) {
		char c = s.at(i);
		unordered_map<char, int>::iterator it = mapSubString.find(c);
		if (it != mapSubString.end()) {

			// 已存在相同的字符
			if (len < mapSubString.size()) {
				len = mapSubString.size();
			}

			mapSubString.erase(mapSubString.begin(), ++it);
		}

		// 不存在重复的字符
		mapSubString.insert(make_pair(c, i));
	}

	if (len < mapSubString.size()) {
		len = mapSubString.size();
	}

	return len;
}