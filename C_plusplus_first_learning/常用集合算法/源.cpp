//求两容器的交集set_intersection
//求两个容器的并集set_union
//求两个容器的差集
//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//void myPrint(int val) {
//	cout << val << " ";
//}
//void test01() {
//	vector<int>v1;
//	vector<int>v2;
//	for (int i = 0; i < 10; i++) {
//		v1.push_back(i);
//		v2.push_back(i + 5);
//	}
//	vector<int>vTarget;
//	vTarget.resize(min(v1.size(), v2.size()));
//	//两个集合必须是有序序列
//	//目标容器开辟空间需要从两个容器取最小值
//	//返回目标容器的最后一个元素的迭代器地址
//	vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());
//	for_each(vTarget.begin(), itEnd,myPrint);
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}


#include<iostream>
#include<vector>
using namespace std;
#include<algorithm>
void myPrint(int val) {
	cout << val << " ";
}
void test01() {
	vector<int>v1;
	vector<int>v2;
	for (int i = 0; i < 10; i++) {
		v1.push_back(i);
		v2.push_back(i + 5);
	}
	vector<int>vTarget;
	vector<int>vTarget2;
	vector<int>vTarget3;
	vTarget2.resize(max(v1.size(), v2.size()));
	vTarget.resize(v1.size()+v2.size());
	vTarget3.resize(max(v1.size(), v2.size()));
	vector<int>::iterator itEnd = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());
	vector<int>::iterator itEnd2 = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget2.begin());
	vector<int>::iterator itEnd3 = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), vTarget3.begin());
	for_each(vTarget.begin(), itEnd, myPrint);
	cout << endl;
	for_each(vTarget2.begin(), itEnd2, myPrint);
	cout << endl;
	for_each(vTarget3.begin(), itEnd3, myPrint);
}
int main() {

	test01();

}