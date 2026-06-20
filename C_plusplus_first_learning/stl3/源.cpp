//#include<iostream>
//using namespace std;
//#include<list>
//void printList(const list<int>&l1) {
//	for (list<int>::const_iterator it = l1.begin(); it != l1.end(); it++) {
//		cout << *it << " ";
//	}
//}
//void test01() {
//	list<int> l1;
//	l1.push_back(10);
//	l1.push_back(20);
//	l1.push_back(30);
//	l1.push_back(40);
//	printList(l1);
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}

//#include<iostream>
//using namespace std;
//#include<list>
//
//void printList(const list<int>& L) {
//	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++) {
//		cout << *it << " ";
//	}
//}
//bool myCompare(int v1,int v2) {
//	//降序 就让第一个数大于第二个数
//	return  v1 > v2;
//}
//void test01() {
//	list<int>L;
//	L.push_back(100);
//	L.push_back(200);
//	L.push_back(300);
//
//	L.push_front(10);
//	L.push_front(20);
//	L.push_front(30);
//
//	L.pop_front();
//	L.pop_back();
//
//	
//	/*L.insert(L.begin(), 1000);*/
//	list<int>::iterator it = L.begin();
//	L.insert(++it, 1000);
//	it = L.begin();
//	L.erase(++it);
//	for (int i = 0; i < 4; i++) {
//		L.push_back(10000);
//	}
//	L.remove(10000);
//	//L.clear();
//	//list反转和排序
//	cout << "反转前" << endl;
//	printList(L);
//	L.reverse();
//	cout << "反转后" << endl;
//	cout << "排序前" << endl;
//	printList(L);
//	/*cout << L.front() << endl;
//	cout << L.back() << endl;*/
//
//	//所有不支持随机访问迭代器的容器，不可以用标准算法
//	//不支持随机访问迭代器的容器,内部会提供对应一些算法
//	L.sort(myCompare);
//	cout << "排序后" << endl;
//	printList(L);
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}
//
////list本质是一个链表，每一个数据不是用连续线性空间存储数据,迭代器也是不支持随机访问
//

//list排序案例
//排序规则:按照年龄进行升序,如果年龄相同按照身高降序
//#include<iostream>
//using namespace std;
//#include<string>
//#include<list>
//class Person {
//public:
//	Person(string name, int age, int height) {
//		this->m_Name = name;
//		this->m_Age = age;
//		this->m_Height = height;
//	}
//	string m_Name;
//	int m_Age;
//	int m_Height;
//};
////指定排序规则
//bool comparePerson(Person &p1, Person &p2) {
//	//按照年龄做一个升序
//	if (p1.m_Age == p2.m_Age) {
//		return p1.m_Height > p2.m_Height;
//	}
//	else {
//		return p1.m_Age < p2.m_Age;
//	}
//}
//void test01() {
//	list<Person> L;
//
//	//准备数据
//	Person p1("刘备", 35, 175);
//	Person p2("曹操", 45, 180);
//	Person p3("孙权", 40, 170);
//	Person p4("赵云", 25, 190);
//	Person p5("张飞", 35, 160);
//	Person p6("关羽", 35, 200);
//	//插入数据
//	L.push_back(p1);
//	L.push_back(p2);
//	L.push_back(p3);
//	L.push_back(p4);
//	L.push_back(p5);
//	L.push_back(p6);
//	cout << "排序前" << endl;
//	for (list<Person>::iterator it = L.begin(); it != L.end(); it++) {
//		cout << "姓名:" << (*it).m_Name << "年龄" << (*it).m_Age << "身高" << (*it).m_Height << endl;
//	}
//	cout << "排序后" << endl;
//	L.sort(comparePerson);
//	for (list<Person>::iterator it = L.begin(); it != L.end(); it++) {
//		cout << "姓名:" << (*it).m_Name << "年龄" << (*it).m_Age << "身高" << (*it).m_Height << endl;
//	}
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}

//map
//#include<iostream>
//using namespace std;
//#include<set>
//
//void printSet(const set<int>s1) {
//	for (set<int>::const_iterator it = s1.begin(); it != s1.end(); it++) {
//		cout << *it << " ";
//	}
//}
//void test01() {
//	set<int> s1;
//	s1.insert(10);
//	s1.insert(20);
//	s1.insert(30);
//	s1.insert(40);
//	s1.insert(1);
//	s1.insert(30);
//	set<int>::iterator pos = s1.find(30);
//	if (pos != s1.end()) {
//		cout << "找到元素" << *pos << endl;
// 	}
//	else {
//		cout << "未找到元素" << endl;
//	}
//	int num = s1.count(30);
//	cout << num << endl;
//	//对于set而言count统计的个数要么是0要么是1
//	//遍历容器
//	//set容器特点,所有元素插入时自动排序
//	//set容器不允许插入重复值
//	//printSet(s1);
//	////set容器插入和删除操作
//	//s1.erase(20);
//	//s1.clear();
//	
//	//set容器查找和统计
//	//find查找key是否存在,若存在 ,返回该键元素迭代器,若不存在返回set.end()
//	//count统计key的元素个数
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}

//pair对组创建
//#include<iostream>
//using namespace std;
//void test01() {
//	pair<string, int>p("Tom", 20);
//	cout << "姓名" << p.first << "年龄" << p.second << endl;
//
//	pair<string, int>p2 = make_pair("Jerry", 30);
//	cout << "姓名" << p2.first << "年龄" << p2.second << endl;
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}