#include<iostream>
#include<string>
using namespace std;

class person {
public:
	string m_name = "张三";
protected:
	string m_car = "拖拉机";
private:
	int password = 56789;
public:
	void func() {
		m_name = "李四";
		m_car = "奔驰";
		password = 123456;
	}
};
int main() {
	person p1;
	p1.m_name;
	p1.m_car;//保护权限
	p1.password;//私有权限
	p1.func();
}