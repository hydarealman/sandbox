#include<iostream>
using namespace std;
int main() {
	int a = 10;
	int& b = a;
	int c = 100;
	b = c;
	cout << a << endl;
	cout << b << endl;
	printf("%d\n", a);
	printf("%d\n", b);
}