#include<iostream>
using namespace std;
class person {
public:
	bool operator== (person& p) {
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age) {
			return true;
		}
		return false;
	}
	bool operator!= (person& p) {
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age) {
			return false;
		}
		return true;
	}
	person(string name, int age) {
		m_Name = name;
		m_Age = age;
	}
	string m_Name;
	int m_Age;
};
void test01() {
	person p1("Tom", 18);

	person p2("Jerry", 18);
	if (p1 != p2) {
		cout << "p1 != p2" << endl;
	}
	else {
		cout << "p1 == p2" << endl;
	}
	if (p1 == p2) {
		cout << "p1 == p2" << endl;
	}
	else {
		cout << "p1 != p2" << endl;
	}
}
int main() {
	test01();


	system("pause");

	return 0;
}