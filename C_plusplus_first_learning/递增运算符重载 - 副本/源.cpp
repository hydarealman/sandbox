#include<iostream>
using namespace std;
class myInteger {
	friend ostream& operator<< (ostream& cout,const myInteger& p);
public:
	myInteger() {
		m_Num = 10;
	}
	myInteger& operator++ () {
		m_Num++;
		return *this;
	}
	myInteger operator++ (int) {
		myInteger temp = *this;
		m_Num++;
		return temp;
	}
private:
	int m_Num;
};
ostream& operator<< (ostream& cout, const myInteger& p) {
	cout << p.m_Num;
	return cout;
}
void test01() {
	myInteger myint;
	cout << ++myint << endl;
}
void test02() {
	myInteger myint;
	cout << myint++ << endl;
	cout << myint << endl;
}
int main() {
	test01();
	test02();
}