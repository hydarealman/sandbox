#include<iostream>
using namespace std;
class person {
public:
	person(int age) {
		m_Age = new int(age);
	}
	~person() {
		//堆区内存重复释放程序崩溃,解决方案深拷贝
		if (m_Age != NULL) {
			delete m_Age;
			m_Age = NULL;
		}
	}
	person& operator= (person &p) {
		//编译器提供浅拷贝
		//m_Age = p.m_Age;

		//应该先判断先判断是否有属性在堆区，如果有先释放干净，然后再深拷贝
		if (m_Age != NULL) {
			delete m_Age;
			m_Age = NULL;
		}
		m_Age = new int(*p.m_Age);

		//返回对象本身，链式编程思想
		return *this;
	}
	
	int* m_Age;
};
void test01() {
	person p1(18);

	person p2(20);

	person p3(30);
	p3 = p2 = p1;
	cout << "p1的年龄为" << *p1.m_Age << endl;
	cout << "p2的年龄为" << *p2.m_Age << endl;
	cout << "p3的年龄为" << *p3.m_Age << endl;
}
int main() {
	test01();
	int a = 10;
	int b = 20;
	int c = 30;
	c = b = a;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
}