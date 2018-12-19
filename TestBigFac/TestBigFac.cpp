// TestBigFac.cpp : �������̨Ӧ�ó������ڵ㡣

#include "stdafx.h"
#include <iostream> 
using namespace std;

int x_tmain(int argc, char *argv[])   
{
	long i, j, c, len, temp = 0;
	int n = 1;

	cout << "������һ��0��10000֮�������: " << endl; 
	while (cin >> n && (n > 0 && n <= 10000))   
	{
		long *a = new long[3 * n];
        a[0] = 1;
		len = 1;   
        for (i = 1; i <= n; i++)   
        {
			c = 0;   
			for (j = 0; j < len; j++)   
			{
				temp = a[j] * i + c;   //�����λ
				c = temp / 10;
				a[j] = temp % 10;
			}

			while (c > 0)        //���մӸ�λ����λ��˳����õ�������
			{
				len = len + 1;   
				a[len - 1] = c;   
				c /= 10000;   
				a[len - 1] %= 10000;   
			}   
		}   

		cout << n << "�Ľ׳�ֵ��" << a[len - 1]; 
        for(i = len - 2; i >= 0; i--)       //������� 
			cout << a[i];   

        cout << "\n�������㣬���������������� 0 " << endl;   
        delete[] a;    //�ͷſռ�   
   }   

   return 0;
}

int _tmain(int argc, char *argv[])
{
	int result[40000]; //���������������
	int len = 1;  //��������λ
	int num;  //����׳˵�����
	cout << "Input number: ";
	cin >> num;

	if (num != 0)
	{
		result[0] = 1;
		for(int i = 1; i <= num; i++)
		{
			int res = 0; // ��λ
			for(int j = 0; j < len; j++)
			{
				int buf = result[j] * i + res; // ������
				result[j] = buf % 10;  // ȡ��ǰλ
				res = buf / 10;   // �����λ 
			}

			while (res)
			{
				result[len++] = res % 10; // ȡ��ǰλ
				res /= 10;   // �����λ
			}
		}

		cout << num << "'s factorial is: ";
		for (int k = len - 1; k >= 0; k--)
		{
			cout << result[k];
		}

		cout << "\nLength=" << len <<endl;
	}

	return 0;
}
