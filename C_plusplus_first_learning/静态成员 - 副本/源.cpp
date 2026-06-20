//#include<iostream>//静态成员变量
//using namespace std;
//class person {
//public:
//
//	static int m_A;
//	
//};
////类外访问不到静态私有变量
//int person::m_A = 100;
//int main() {
//	person p;
//	cout << p.m_A << endl;
//	person p2;
//	p2.m_A = 200;
//	cout << p.m_A << endl;
//	cout << person::m_A << endl;
//}
#include<iostream>
using namespace std;
//静态成员函数
//所有对象共享同一个函数
//静态成员函数只能访问静态成员变量
class person {
public:

	static void func() {
		m_A = 100;
		m_B = 100;//静态成员函数不可以访问非静态成员变量，因为无法区分到底是哪个对象的成员
		cout << "static void func调用" << endl;
	}
	static int m_A;
	int m_B;
};

int person::m_A = 0;

void test01() {
	person p;
	p.func();

	person::func();
}
int main() {
	test01();

	system("pause");

	return 0;
}