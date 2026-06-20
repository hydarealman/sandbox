#include<iostream>
using namespace std;

const double PI = 3.14;
class Circle {
	public:

	int m_r;
	int m_t;
	double calculatecircle(int a,int b) {
		cout << m_t << endl;
		cout << b << endl;
		return 2 * PI * m_r;
	}
};

int main() {
	//通过类来创建对象
	//实例化
	Circle c1;
	c1.m_r = 10;
	c1.m_t = 20;
	cout << c1.calculatecircle(10,20) << endl;
	system("pause");
	return 0;
}