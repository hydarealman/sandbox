#include<iostream>
using namespace std;
int& test1() {
	static int a = 10;
	return a;
}
int main() {
	int& ref = test1();
	cout << ref << endl;
	cout << ref << endl;
	test1() = 1000;
	cout << ref << endl;
	cout << ref << endl;
}