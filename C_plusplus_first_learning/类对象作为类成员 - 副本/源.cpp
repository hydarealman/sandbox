#include<iostream>
#include<string>
using namespace std;
class phone {
public:
	phone(string name) {
		m_phonename = name;
		cout << "phone的构造" << endl;
	}
	~phone() {
		cout << "~phone析构" << endl;
	}
	string m_phonename;
};
class person {
public:
	person(string name, string pname) : m_name(name), m_phone(pname) {

	}
	void playgame() {
		cout << m_name << "使用" << m_phone.m_phonename << "牌手机！" << endl;
	}
	string m_name;
	phone m_phone;
};
void test01() {

	person p("张三", "苹果x");
	p.playgame();
}
int main() {
	test01();
}