#include<iostream>
using namespace std;
class person {
public:
	//this指针的本质 是指针常量 指针的指向是不可以修改的
	//this指针指向的值是可以修改的
	//const person* const this
	//在成员函数后面加const，修饰的是this指针，让指针指向的值也不可以修改
	void showPerson() const {
		/*m_A = 100;
		this = NULL;*/
		this->m_B = 100;
	}

	void func() {

	}

	int m_A;
	mutable int m_B;//特殊变量，即使在常函数中，也可以修改这个值，加关键字mutable
};

void test01() {
	person p;
	p.showPerson();
}

void test02(){
	const person p;
	p.m_B = 100;
	p.showPerson();
	//常对象只能调用常函数，不能调用普通函数
	/*p.func();*/
}

int main() {
	test01();
	test02();
	system("pause");
	return 0;
}