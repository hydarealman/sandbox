#include"БъЭЗ.h"
#include<iostream>
using namespace std;
int main() {
	int a = 10;
	int b = 20;
	void swap1(a, b);
	void swap2(a, b);
		system("pause");
	return 0;
}
void swap1(int a, int b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
	cout << "a=" << a << "b=" << b << endl;
}
void swap2(int a, int b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	cout << "a=" << a << "b=" << b << endl;
	system("pause");
}
