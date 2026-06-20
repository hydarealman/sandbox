#include<iostream>
using namespace std;
class person {
public:
	int m_a;
	int m_b;
	int m_c;
	person(int a, int b, int c) : m_a(a), m_b(b), m_c(c) {

	}
	/*person(int a, int b, int c) {
		m_a = a;
		m_b = b;
		m_c = c;
	}*/
};
int main() {
	person p(10,20,30);
	cout << p.m_a << p.m_b << p.m_c << endl;
}