#pragma once
#include <iostream>

class Point//����
{
public:
	Point(double xx, double yy) 
	{ 
		x=xx; 
		y=yy; 
	}//Ĭ�Ϲ��캯��

	void Getxy();//���г�Ա����

	friend double Distance(Point &a, Point &b);//��Ԫ����

private:
	double x, y;
};
