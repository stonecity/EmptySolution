#include "stdafx.h"

 int aa_main()
 {
	 // ע�� array �� &array �������ǲ�ͬ�ġ�array �൱�� &array[0]��
	 // �� &array ��һ��ָ�� int[100] ��ָ�룬������ int(*)[100]
	 int array[100] = {0, 1, 2};
     typedef int (*ARRAY)[100];
     int* p1 = array;
     ARRAY p2 = &array;
     //int* p3 = &array;     //�����������

     printf("p1 = 0x%08X\n", p1);
     printf("p2 = 0x%08X\n", p2);
     printf("p1[2] = %d\n", p1[2]);
     printf("p2[2] = %d\n", p2[2]);
     printf("(*p2)[2] = %d\n", (*p2)[2]);
     
     getchar();

     return 0;
 }
