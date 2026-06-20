#include<iostream>
using namespace std;
//继承方式

//公共方式

class Base1 {
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};
class Son1 : public Base1 {
public:
	void func() {
		m_A = 10; //父类公共权限成员，到子类中依然是公共权限
		m_B = 10; //父类的保护权限成员，到子类中依然是保护权限
	}   //父类中的私有权限成员 子类访问不到
};
void test01() {
	Son1 s1;
	s1.m_A = 100;//保护权限类内可以访问，类外访问不到
}
class Base2 {
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};
class Son2 : protected Base2 {
public:
	void func() {
		m_A = 100;//父类中公共成员，到子类中变为保护权限
		m_B = 100;//父类中保护成员，到子类中变为保护权限
		//父类中私有成员，子类访问不到
	}
};
class Son3 :private Base2 {
public:
	void func() {
		m_A = 100;
		m_B = 100;
	}
};
class GrandSon3 : private Son3 {
public:
	void func() {
		/*m_A = 100;*///子类私有继承父类，孙子访问不到
	}
};
void test02() {
	Son2 s1;
}
int main() {

	system("pause");
	return 0;
}