//#include<iostream>
//#include<string>
//using namespace std;
////查找
//void test01() {
//	string str1 = "abcdefg";
//
//	int pos = str1.find("de");
//	int pos2 = str1.find("df");
//	cout << pos2 << endl;
//	cout << pos << endl;
//}
////rfind从右往左查找find从左往右查找
////替换
//void test02() {
//	string str1 = "abcdefg";
//	str1.replace(1, 3, "1");
//	cout << str1 << endl;
//}
//int main() {
//
//	test01();
//	test02();
//
//	system("pause");
//	return 0;
//}

//字符串比较
//#include<iostream>
//using namespace std;
//#include<string>
//void test01() {
//	string str1 = "xello";
//	string str2 = "hello";
//	if (str1.compare(str2) == 0) {
//		cout << "str1 == str2" << endl;
//	}
//	else if (str1.compare(str2) > 0) {
//		cout << "str1 大于 str2" << endl;
//		cout << str1.compare(str2) << endl;
//	}
//	else {
//		cout << "str1 小于 str2" << endl;
//	}
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}

//string 字符存取
//#include<iostream>
//using namespace std;
//void test01() {
//	string str = "hello";
//	str.at(0) = 'x';
//	cout << str << endl;
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
//#include<string>
//
//void test01() {
//	string str = "hello";
//
//	str.insert(1, "111");
//	cout << str << endl;
//
//	str.erase(1,3);
//	cout << str << endl;
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}
//子串获取
//#include<iostream>
//#include<string>
//using namespace std;
//
//void test01() {
//	string str1 = "abcdefg";
//
//	string subStr = str1.substr(0, 3);
//
//	cout << subStr << endl;
//}
////实用操作
////截取用户名
//void test02() {
//	string email = "hello@sina.com" ;
//
//	int pos = email.find("@");
//	string subStr = email.substr(0, pos);
//
//	cout << subStr << endl;
//
//}
//int main() {
//
//	test01();
//
//	test02();
//
//	system("pause");
//	return 0;
//}
//string容器
//赋值=
//拼接append
//替换replace
//查找find
//插入insert
//删除erase
//比较compare
//截取字串subsr
//存取at||[]



//vector
//赋值操作
//#include<iostream>
//using namespace std;
//#include<vector>
//
//void printVector(vector<int>& v) {
//	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
//		cout << *it << " ";
//	}
//	cout << endl;
//}
//void test01() {
//	vector<int> v1;
//	for (int i = 0; i < 10; i++) {
//		v1.push_back(i);
//	}
//	printVector(v1);
//
//	//赋值
//	vector<int> v2;
//	v2 = v1;
//	printVector(v2);
//
//	//assign
//	vector<int>v3;
//	v3.assign(v1.begin(), v1.end());
//	printVector(v3);
//
//	vector<int> v4;
//	v4.assign(10, 100);
//	printVector(v4);
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
//#include<vector>
//void printVector(vector<int>& v) {
//	for (vector<int>::iterator it = v.begin(); it != v.end();  it++) {
//		cout << *it << " ";
//	}
//	cout << endl;
//}
//void test01() {
//	vector<int>v1;
//	for (int i = 0; i < 10; i++) {
//		v1.push_back(i);
//	}
//	printVector(v1);
//
//	if (v1.empty()) {
//		cout << "v1为空" << endl;
//	}
//	else {
//		cout << "不为空" << endl;
//		cout << "v1的容量为" << v1.capacity() << endl;
//		cout << "v1的大小" << v1.size() << endl;
//	}
//	//重新指定大小
//	v1.resize(15,100);
//	cout << v1.capacity() << endl;
//	cout << v1.size() << endl;
//	printVector(v1);
//
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}

//vector的插入和删除
//#include<iostream>
//using namespace std;
//#include<vector>
//void printVector(vector<int>& v) {
//	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
//		cout << *it << " ";
//	}
//	cout << endl;
//}
//void test01() {
//	vector<int> v1;
//	for (int i = 0; i < 10; i++) {
//		v1.push_back(i);
//	}
//	//第一个参数是迭代器
//	v1.insert(v1.begin() + 1, 666);
//	v1.erase(v1.begin() + 1);
//
//
//
//	printVector(v1);
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}

//vector数据存储
//#include<iostream>
//using namespace std;
//#include<vector>
//
//void test01() {
//	vector<int>v1;
//	for (int i = 0; i < 10; i++) {
//		v1.push_back(i);
//	}
//	for (int i = 0; i < v1.size(); i++) {
//		cout << v1[i] << " ";
//	}
//	cout << endl;
//	for (int i = 0; i < v1.size(); i++) {
//		cout << v1.at(i) << " ";
//	}
//	cout << endl;
//	cout << v1.front() << endl;
//	cout << v1.back() << endl;
//}
//
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}
//#include<iostream>
//using namespace std;
//#include<vector>
//
//void printVector(vector<int>& v) {
//	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
//		cout << *it << " ";
//	}
//}
//void test01() {
//	vector<int> v1;
//	for (int i = 0; i < 10; i++) {
//		v1.push_back(i);
//	}
//	printVector(v1);
//	cout << endl;
//	vector<int> v2;
//	for (int i = 10; i > 0; i--) {
//		v2.push_back(i);
//	}
//	printVector(v2);
//
//	cout << "交换后" << endl;
//	v1.swap(v2);
//	printVector(v1);
//	cout << endl;
//	printVector(v2);
//}
////2.实际用途
////巧用swap可以收缩内存空间
//void test02() {
//	vector<int>v;
//	for (int i = 0; i < 100000; i++) {
//		v.push_back(i);
//	}
//	v.resize(3);
//	cout << "v的容量" << v.capacity() << endl;
//	cout << "v的大小" << v.size() << endl;
//
//	//巧用swap收缩内存
//	vector<int>(v).swap(v);//匿名对象内存系统回收
//	cout << "v的容量" << v.capacity() << endl;
//	cout << "v的大小" << v.size() << endl;
//}
//int main() {
//
//	/*test01();*/
//	test02();
//	system("pause");
//	return 0;
//}

//预留空间
//#include<vector>
//#include<iostream>
//using namespace std;
//int main() {
//
//	vector<int>v;
//	v.reserve(100000);
//	int num = 0;
//	int* p = NULL;
//	for (int i = 0; i < 100000; i++) {
//		v.push_back(i);
//		if (p != &v[0]) {
//			p = &v[0];
//			num++;
//		}
//	}
//	cout << num << endl;
//}