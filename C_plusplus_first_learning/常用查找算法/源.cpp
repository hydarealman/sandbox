//常用查找算法find
//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include<string>
//using namespace std;
//class Person {
//public:
//	Person(int age, string name) {
//		this->m_age = age;
//		this->m_name = name;
//	}
//	//重载 == 底层find知道如何对比person数据类型
//	bool operator==(const Person& p) {
//		if (this->m_age == p.m_age && this->m_name == p.m_name) {
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//	int m_age;
//	string m_name;
//};
//void test01() {
//	Person p1(10, "aaa");
//	Person p2(20, "bbb"); 
//	Person p3(30, "ccc");
//	Person p4(40, "ddd");
//	Person p5(50, "eee");
//	Person p6(60, "fff");
//	Person pp(30, "ccc");
//	vector<Person> v;
//	v.push_back(p1);
//	v.push_back(p2);
//	v.push_back(p3);
//	v.push_back(p4);
//	v.push_back(p5);
//	v.push_back(p6);
//	vector<Person>::iterator it = find(v.begin(), v.end(), pp);
//	if (it == v.end()) {
//		cout << "没找到" << endl;
//	}
//	else {
//		cout << "找到元素:" << "年龄 " << it->m_age << "姓名 " << it->m_name << endl;
//	}
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}
//常用查找算法find_if
//略
//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//void test01() {
//	vector<int>v;
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(30);
//
//	vector<int>::iterator pos = adjacent_find(v.begin(), v.end());
//	if (pos == v.end()) {
//		cout << "没找到" << endl;
//	}
//	else {
//		cout << "找到了" << *pos << endl;
//	}
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}

//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//void test01() {
//	vector<int>v;
//	for (int i = 0; i < 10; i++) {
//		v.push_back(i);
//	}
//	bool ret = binary_search(v.begin(), v.end(), 3);//二分查找必须要有序，否则有可能找不到
//	if (ret) {
//		cout << "找到了" << endl;
//	}
//	else {
//		cout << "没找到" << endl;
//	}
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}
//统计自定义数据类型
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
class Person {
public:
	Person(string name, int age) {
		this->m_name = name;
		this->m_age = age;
	}
	bool operator == (const Person& p) {//底层的时候要加const防止修改数据
		if (this->m_age == p.m_age) {
			return true;
		}
		else {
			return false;
		}
	}
	string m_name;
	int m_age;
};
void test02() {
	vector<Person>v;
	Person p1("刘备", 30);
	Person p2("刘备", 30);
	Person p3("刘备", 30);
	Person p4("刘备", 30);
	Person p5("刘备", 30);
	Person p6("刘备", 30);
	Person p7("刘备", 30);
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);
	v.push_back(p6);
	v.push_back(p7);
	Person p("刘备", 30);
	int num = count(v.begin(), v.end(),p );

	cout << "和刘备同年龄的个数" << num << endl;

}
int main() {

	test02();

	system("pause");
	return 0;
}