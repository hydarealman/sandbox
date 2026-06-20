#include<iostream>
using namespace std;
#include"point.h"
#include"circle.h"
#include"isincircle.h"
int main() {
	point center;
	center.setm_x(10);
	center.setm_y(0);
	circle c;
	c.setm_r(10);
	c.setcenter(center);

	point p;
	p.setm_x(10);
	p.setm_y(10);

	isincircle(c, p);
	system("pause");
	return 0;
}