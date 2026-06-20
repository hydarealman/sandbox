#include<iostream>
using namespace std;

class person {
public:
	person() {
		cout << "person的默认构造函数调用" << endl;
	}
	person(int age) {
		m_age = age;
		cout << " person的有参构造函数的调用 " << endl;
	}
	~person() {
		cout << " person的析构函数的调用" << endl;
	}
	person(const person & p) {
		m_age = p.m_age;
		cout << " person的拷贝构造函数的调用" << endl;
	}
	int m_age;
};
//使用一个已经创建完毕的对象初始化一个新的对象
void test01() {
	person p1(20);
	person p2(p1);
	cout << "p2的年龄" << p2.m_age << endl;
}
void dowork(person p) {
	//所以这里面改数据不会影响下面的值因为值传递本质会创建一个临时的函数
}
//值传递的方式给函数参数赋值
void test02() {
	person p;
	dowork(p);//值传递本身就是调用拷贝构造函数
}
//值方式返回局部变量
person dowork2() {
	person p1;
	cout << (int*) & p1 << endl;
	return p1;
}
//以值方式返回局部对象//新版本好像不行了
void test03() {//新的版本和网课不一样
	person p = dowork2();
	cout << (int*)&p << endl;
}
void dowork() {
	
}

int main() {
	/*test01();*/
	/*test02();*/
	test03();

	system("pause");
	return 0;
}