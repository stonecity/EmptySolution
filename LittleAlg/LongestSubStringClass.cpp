#include "stdafx.h"
#include "LongestSubStringClass.h"


int LongestSubStringClass::GetLengthOfLongestSubstring(string s) {
	size_t len = 0;
	unordered_map<char, int> mapSubString;
	for (size_t i = 0; i < s.length(); i++) {
		char c = s.at(i);
		unordered_map<char, int>::iterator it = mapSubString.find(c);
		if (it != mapSubString.end()) {

			// �Ѵ�����ͬ���ַ�
			if (len < mapSubString.size()) {
				len = mapSubString.size();
			}

			mapSubString.erase(mapSubString.begin(), ++it);
		}

		// �������ظ����ַ�
		mapSubString.insert(make_pair(c, i));
	}

	if (len < mapSubString.size()) {
		len = mapSubString.size();
	}

	return len;
}