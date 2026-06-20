#include<iostream>
#include<string>
using namespace std;
class student {
public:
	string name;
	int id;
	void showstudent() {
		cout << "学生姓名为:" << name << "学生id为:" << id << endl;
	}
	void setname(string m_name) {
		name = m_name;
	}

};
int main() {
	student s1;
	s1.name = "张三 ";
	s1.setname("王五 ");
	s1.id = 1;
	s1.showstudent();

	student s2;
	s2.name = "李四 ";
	s2.id = 2;
	s2.showstudent();

	//可以通过行为给属性赋值


	system("pause");
	return 0;
}