#include<iostream>
using namespace std;
class Base {
public:
	static int m_A;
	
	static void func() {
		cout << "Base - static void func()" << endl;
	}
};
int Base::m_A = 100;

class Son :public Base {
public:
	static int m_A;
};
int Son::m_A = 200;

//同名静态成员属性
void test01() {
	//1.通过对象访问
	cout << "通过对象访问" << endl;
	Son s;
	cout << "Son下m_A = " << s.m_A << endl;
	cout << "Base下m_A = " << s.Base::m_A << endl;
	//2.通过类名访问
	cout << "通过类名访问" << endl;
	cout << "Son下 m_A = " << Son::m_A << endl;
	//第一个::代表通过类名方式访问  第二个::代表访问父类作用域下
	cout << "Base下 m_A = " << Son::Base::m_A << endl;
}
//静态成员可以通过类名访问
void test02() {
	Son s;
	s.func();
	s.Base::func();
	Son::Base::func();
	Son::func();
}
int main() {

	/*test01();*/
	test02();
	system("pause");
	return 0;
}