#include<iostream>
using namespace std;
void showvalue(const int& a) {
	a = 1000; //会报错因为const 让a不可修改
	cout << a << endl;
}
int main() {
	//const int& a = 10;//加上const 编译器会将代码修改为int temmp = 10; int & a = temp;
	const int a = 10;
	showvalue(a);
	cout << a << endl;
}