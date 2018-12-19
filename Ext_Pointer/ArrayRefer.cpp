#include "stdafx.h"

 int aa_main()
 {
	 // 注意 array 和 &array 的类型是不同的。array 相当于 &array[0]，
	 // 而 &array 是一个指向 int[100] 的指针，类型是 int(*)[100]
	 int array[100] = {0, 1, 2};
     typedef int (*ARRAY)[100];
     int* p1 = array;
     ARRAY p2 = &array;
     //int* p3 = &array;     //这样编译错误

     printf("p1 = 0x%08X\n", p1);
     printf("p2 = 0x%08X\n", p2);
     printf("p1[2] = %d\n", p1[2]);
     printf("p2[2] = %d\n", p2[2]);
     printf("(*p2)[2] = %d\n", (*p2)[2]);
     
     getchar();

     return 0;
 }
