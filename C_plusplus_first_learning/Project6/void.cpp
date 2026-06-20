#include"swap.h"
#include<iostream>
using namespace std;
int swap1(int a, int b) {
	int temp = 0;
	temp = a;
	a = b;
	b = temp;
	cout << "a=" << a << "b=" << b << endl;
	return 0;
}
