#include<iostream>
using namespace std;
//void func(int &a) {
//	cout << "调用函数func(int a)" << endl;
//}
//void func(const int &a) {
//	cout << "调用函数func(const int a)" << endl;
//}
void func2(int a) {
	cout << "函数调用func2(int a)" << endl;
}
void func2(int a, int b = 10) {
	cout << "函数调用func2(int a,int b=10)" << endl;
}
int main() {
	/*int a = 10;
	func(a);*/
	func2(10);//当函数重载碰到默认参数，出现二义性,报错,尽量避免这种情况
}