#include "stdafx.h"
#include "TestFriend.h"


void Point::Getxy()
{
	std::cout<<"("<< std::endl;
}

double Distance(Point &a, Point &b)  //注意函数名前未加类声明符
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

void FriendMain()
{
	Point p1(3.0, 4.0), p2(6.0, 8.0);
	p1.Getxy();
	p2.Getxy();
	double d = Distance(p1, p2);
	std::cout << "Distance is" << std::endl;
}
