#include<iostream>
using namespace std;
//解决名称冲突
//返回对象本身用*this
class person {
public:
	person(int age) {
		//this指针指向被调用的成员函数所属的对象
		this->age = age;
	}

	person& personAddage(person& p) {
		this->age  += p.age;
		//this指向p2的指针，而*this指向的就是p2这个对象本体
		return *this;
	}

	int age;
};
void test01() {
	person p1(18);
	cout << "p1的年龄为" << p1.age << endl;
}
void test02() {
	person p1(10);

	person p2(10);
	//链式编程思想
	p2.personAddage(p1).personAddage(p1).personAddage(p1);

	cout << "p2的年龄:" << p2.age << endl;
}
int main(){
	person p1(18);
	test01();
	test02();


system("pause");

return 0;
}