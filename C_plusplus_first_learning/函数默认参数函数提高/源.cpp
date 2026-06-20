#include<iostream>
using namespace std;
int func(int a=20, int b=30, int c=40) {
	return a + b + c;
}
int func2(int a = 10, int b = 10);
int main() {
	cout << func(10, 10) << endl;
	cout << func2() << endl;
}
int func2(int a , int b ) {
	return a + b;
}