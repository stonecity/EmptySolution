#include "stdafx.h"
#include <iostream>
#include <assert.h>
using namespace std;

// 插入排序
void insertion_sort(int* arr)
{
	assert(arr != NULL);

	// 计算数组的长度	
	int len = 6;

	for (int i = 1; i < len; i++)
	{
		int key = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] < key)
		{
			arr[j + 1] = arr[j];
			j -= 1;
		}

		arr[j + 1] = key;
	}
}

uint8_t BitConst[8] = { 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF };

uint32_t get_nbits(uint8_t* pBytes, uint32_t size, uint32_t bitPos, uint32_t nBits)
{
    uint32_t rBitPos = bitPos % 8;

    uint8_t* ptr = pBytes + (bitPos / 8);

    uint32_t i = 0;
    uint32_t nMoveHigh = 0;
    uint32_t result = 0;

    while (nBits > 0)
    {
        uint8_t value = *(ptr + i);
        if (i == 0)
        {
            if (nBits < 8 - rBitPos)
            {
                uint32_t a = ((uint32_t)value >> rBitPos) & BitConst[nBits - 1];
                result += a;

                nBits = 0;
            }
            else
            {
                uint32_t a = (uint32_t)value >> rBitPos;
                result += a;

                nBits -= (8 - rBitPos);
            }
        }
        else if (nBits / 8 <= 1)
        {
            rBitPos = nBits % 8;
            uint8_t nMove = 8 - rBitPos;
            uint32_t a = ((uint32_t)value & BitConst[rBitPos - 1]); //(0xFF >> nMove));

            result += ((uint32_t)a << nMoveHigh);
            nBits -= rBitPos;
        }
        else
        {
            result += ((uint32_t)value << nMoveHigh);
            nBits -= 8;
        }

        nMoveHigh += (8 - rBitPos);

        i++;
    }

    return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
    uint8_t pBytes[8] = { 0xC4, 0xA8, 0x78, 0x9F, 0x57, 0x00, 0x01, 0x00 };
    uint32_t s1 = get_nbits(pBytes, 16, 0, 9);
    printf("s1: %d \n", s1);

    uint32_t s2 = get_nbits(pBytes, 16, 9, 4);
    printf("s2: %d \n", s2);

    uint32_t s3 = get_nbits(pBytes, 16, 13, 10);
    printf("s3: %d \n", s3);

    uint32_t s4 = get_nbits(pBytes, 16, 23, 1);
    printf("s4: %d \n", s4);

    uint32_t s5 = get_nbits(pBytes, 16, 24, 1);
    printf("s5: %d \n", s5);

    uint32_t s6 = get_nbits(pBytes, 16, 25, 4);
    printf("s6: %d \n", s6);


	int arr[6] = { 5, 2, 4, 6, 3, 1 };

	// 使用插入排序算法对数组进行排序
	insertion_sort(arr);

	// Print result
	for (int i = 0; i < 6; i++)
	{
		cout << arr[i] << " ";
	}

	cout << endl;
	system("pause");

	return 0;
}