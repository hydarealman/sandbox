#include<iostream>
using namespace std;
class person {
public:
	int m_A;
	int m_B;
	//通过成员函数重载加号运算符
	/*person operator+ (person& p) {
		person temp;
		temp.m_A = this->m_A + p.m_A;
		temp.m_B = this->m_B + p.m_B;
		return temp;
	}*/
};

person operator+ (person& p1, person& p2) {
	person temp;
	temp.m_A = p1.m_A + p2.m_A;
	temp.m_B = p1.m_B + p2.m_B;
	return temp;
}
int main() {
	person p1;
	p1.m_A = 10;
	p1.m_B = 10;
	person p2;
	p2.m_A = 10;
	p2.m_B = 10;
	person p3;
	p3 = p1 + p2;
	cout << p3.m_A << endl;
	cout << p3.m_B << endl;
}