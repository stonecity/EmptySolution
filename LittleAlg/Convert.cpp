
#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;
using std::vector;

char *entry, letter, choice[2];
int ascii, len, binary[8], total;

typedef char TestChartArr[4];

/* 
*将字符数组中的每个字符转换成二进制格式, 
*只限于ASCII字符 
*/
void ConvertCharToHex()
{
	entry = new char[501];
	cout << "Enter string to convert(up to 500 chars)." << endl;
	cin.getline(entry, 500);
	len = strlen(entry);

	for (int i = 0; i < len; i++)
	{
		total = 0;
		letter = entry[i];
		ascii = letter;
		while (ascii > 0)
		{
			if (ascii % 2 == 0)
			{
				binary[total] = 0;
				ascii = ascii >> 1;
				total++;
			}
			else
			{
				binary[total] = 1;
				ascii = ascii >> 1;
				total++;
			}
		}

		total--;
		
		while (total >= 0)
		{
			cout << binary[total];
			if (total % 4 == 0)
			{
				cout << " ";
			}
			
			total--;
		}
	}

	delete[] entry;

	cout << "\nDo again(y, n)?：";
	cin.getline(choice, 3);
	
	char cin = choice[0];
	if (cin == 'y' || cin == 'Y')
		ConvertCharToHex();
	else
		exit(1);
}

int aa_tmain(int argc, _TCHAR* argv[])
{
	TestChartArr x = { 'A', 'B' };
	unsigned char a = -1;
	std::cout << a;

	long b = -1;
	if (b < sizeof(b))
	{
		std::cout << "<" << std::endl;
	}
	else
	{
		std::cout << ">=" << std::endl;
	}

	if (false)
	{
		ConvertCharToHex();
	}

	vector<int> ivec(10, 1); // vector is a template, not a type.
	for (size_t i = 0; i < 10; i++)
	{
		ivec.push_back(i);
	}

	for (auto &j : ivec)
	{
		j *= j;
	}

	vector<bool> vecbool = { true, false, true };
	vector<unsigned> scores(11, 0);
	vector<unsigned> grades{ 42, 65, 95, 100, 39, 67, 95, 76, 88, 76, 83, 92, 76, 93 };
	for (auto grade : grades)
	{
		if (grade <= 100)
		{
			++scores[grade / 10];
		}
	}

	return 0;
}

