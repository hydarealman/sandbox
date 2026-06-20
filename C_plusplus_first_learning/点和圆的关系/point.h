#pragma once 
#include<iostream>
using namespace std;

class point {
public:
	void setm_x(int x);
	int getm_x();
	void setm_y(int y);
	int getm_y();
private:
	int m_x;
	int m_y;
};
