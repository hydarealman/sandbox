//不会利用成员函数重载左移运算符，因为无法实现cout在左侧
//链式编程思想
#include<iostream>
using namespace std;
class person {
public:
	int m_A;
	int m_B;

};
ostream& operator<< (ostream& cout, person p) {
	cout << p.m_A << " " << p.m_B;
	return cout;
}
int main() {
	person p1;
	p1.m_A = 10;
	p1.m_B = 10;
	cout << p1;
}
//重载运算符配合友员可以实现输出自定义数据类型