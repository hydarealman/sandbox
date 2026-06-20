//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include<functional>
//using namespace std;
//void myprint(int val) {
//	cout << val << " ";
//}
//void test01() {
//	vector<int>v;
//	v.push_back(10);
//	v.push_back(30);
//	v.push_back(20);
//	v.push_back(40);
//	for_each(v.begin(), v.end(), myprint);
//	cout << endl;
//	sort(v.begin(), v.end());
//	for_each(v.begin(), v.end(), myprint);
//	cout << endl;
//	sort(v.begin(), v.end(), greater<int>());
//	for_each(v.begin(), v.end(), myprint);
//	cout << endl;
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}
//洗牌算法random_shuffle
//#include<iostream>
//using namespace std;
//#include<vector>
//#include<algorithm>
//#include<climits>
//void myPrint(int val) {
//	cout << val << " ";
//}
//void test01() {
//	vector<int>v;
//	for (int i = 0; i < 10; i++) {
//		v.push_back(i);
//	}
//	for_each(v.begin(), v.end(),myPrint);
//	cout << endl;
//	random_shuffle(v.begin(), v.end());
//	for_each(v.begin(), v.end(),myPrint);
//}
//int main() {
//	srand((unsigned int)time(NULL));
//	test01();
//
//	system("pause");
//	return 0;
//}//记得加随机数种子

//merge两个容器合并,并存储到另一个容器中
//#include<iostream>
//using namespace std;
//#include<vector>
//#include<algorithm>
//void myPrint(int val) {
//	cout << val << " ";
//}
//void test01() {
//	vector<int>v1;
//	vector<int>v2;
//
//	for (int i = 0; i < 10; i++) {
//		v1.push_back(i);
//		v2.push_back(i+1);//一致升降序
//	}
//	vector<int>vTarget;
//	vTarget.resize(v1.size() + v2.size());
//	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vTarget.begin());
//	for_each(vTarget.begin(), vTarget.end(), myPrint);
//	cout << endl;
//}
//int main() {
//
//	test01();
//
//	system("pause");
//	return 0;
//}

//reverse反转
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
void myPrint(int val) {
	cout << val << " ";
}
void test01() {
	vector<int> v;
	for (int i = 0; i < 10; i++) {
		v.push_back(i);
	}
	for_each(v.begin(), v.end(), myPrint);
	cout << endl;
	reverse(v.begin(), v.end());
	for_each(v.begin(), v.end(), myPrint);
}
int main() {

	test01();

	system("pause");
	return 0;
}