// TestBigFac.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <iostream> 
using namespace std;

int x_tmain(int argc, char *argv[])   
{
	long i, j, c, len, temp = 0;
	int n = 1;

	cout << "请输入一个0—10000之间的整数: " << endl; 
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
				temp = a[j] * i + c;   //处理进位
				c = temp / 10;
				a[j] = temp % 10;
			}

			while (c > 0)        //按照从高位到低位的顺序放置到数组中
			{
				len = len + 1;   
				a[len - 1] = c;   
				c /= 10000;   
				a[len - 1] %= 10000;   
			}   
		}   

		cout << n << "的阶乘值：" << a[len - 1]; 
        for(i = len - 2; i >= 0; i--)       //逆序输出 
			cout << a[i];   

        cout << "\n继续计算，如果你想放弃请输入 0 " << endl;   
        delete[] a;    //释放空间   
   }   

   return 0;
}

int _tmain(int argc, char *argv[])
{
	int result[40000]; //保存结算结果的数组
	int len = 1;  //结果的最高位
	int num;  //计算阶乘的数字
	cout << "Input number: ";
	cin >> num;

	if (num != 0)
	{
		result[0] = 1;
		for(int i = 1; i <= num; i++)
		{
			int res = 0; // 进位
			for(int j = 0; j < len; j++)
			{
				int buf = result[j] * i + res; // 计算结果
				result[j] = buf % 10;  // 取当前位
				res = buf / 10;   // 计算进位 
			}

			while (res)
			{
				result[len++] = res % 10; // 取当前位
				res /= 10;   // 计算进位
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
