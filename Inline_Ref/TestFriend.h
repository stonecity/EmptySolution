#pragma once
#include <iostream>

class Point//声明
{
public:
	Point(double xx, double yy) 
	{ 
		x=xx; 
		y=yy; 
	}//默认构造函数

	void Getxy();//公有成员函数

	friend double Distance(Point &a, Point &b);//友元函数

private:
	double x, y;
};
