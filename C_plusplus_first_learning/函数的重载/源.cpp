#include<iostream>
using namespace std;
void func(int a) {
	cout << "函数(int a) 的调用" << endl;
}
void func() {
	cout << "函数的调用" << endl;
}
//无法重载仅按返回类型区分的函数
int main() {
	func(10);
	func();
}
//类型不同，顺序不同，个数不同都可以作为返回条件