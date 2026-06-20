#include<iostream>
using namespace std;
//如果函数模板和普通函数都可以调用，优先调用普通函数
//通过空模板参数列表可以强制调用模板函数
//函数模板也可以发生函数重载
//如果函数模板可以产生更好的匹配优先调用函数模板
void myPrint(int a, int b) {
	cout << "调用的普通函数" << endl;
}
template<typename T>
void myPrint(T a, T b) {
	cout << "调用的模板函数1" << endl;
}
template<typename T>
void myPrint(T a, T b,T c) {
	cout << "调用的模板函数2" << endl;
}
void test01() {
	int a = 10;
	int b = 20;
	int c = 30;
	myPrint(a, b);
	myPrint<>(a, b);
	myPrint(a, b, c);
	char c1 = 'a';
	char c2 = 'b';
	myPrint(c1, c2);
}
int main() {

	test01();

	system("pause");

	return 0;
}
//既然提供函数模板，最好不要提供普通函数，否则容易出现二义性