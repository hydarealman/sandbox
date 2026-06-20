#pragma once
#include"point.h"
class circle {
public:
	void setm_r(int r);
	int getm_r();
	void setcenter(point center);
	point getcenter();
	int m_r;
	point m_center;

};

