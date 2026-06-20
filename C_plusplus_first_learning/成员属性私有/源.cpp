//设置公有的方法对私有的属性进行控制
#include<iostream>
#include<string>
using namespace std;
class student {
private:
	string m_name;
	int m_age = 18;
	string m_idol;
public:
	void setperson(string name) {
		m_name = name;
	}
	string showperson() {
		return m_name;
	}
	int getage() {
		return m_age;
	}
	void setidol(string idol) {
		m_idol = idol;
	}
	void setage(int age) {
		if (age < 0 || age > 150) {
			cout << "输入有误，赋值运算" << endl;
			return;
		}
		m_age = age;
	}
};
int main() {
	student s1;
	s1.setperson("张三");
	cout << s1.showperson() << endl;
	s1.setage(17);
	cout << s1.getage() << endl;
	s1.setidol("赵云");
	
}