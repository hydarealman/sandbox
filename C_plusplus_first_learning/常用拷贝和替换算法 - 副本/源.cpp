//replace
#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
void myPrint(int val) {
	cout << val << " ";
}
class myCompare {
public:
	bool operator()(int val) {
		return val > 5;
	}
};
void test01() {
	vector<int> v1;
	for (int i = 0; i < 10; i++) {
		v1.push_back(i);
	}
	vector<int> v2;
	v2.resize(v1.size());
	copy(v1.begin(), v1.end(), v2.begin());//用copy前记得提前开辟空间
	//replace(v2.begin(), v2.end(), 2, 20000);//将所有2都替换成20000
	cout << "替换前" << endl;
	for_each(v2.begin(), v2.end(), myPrint);
	replace_if(v2.begin(), v2.end(), myCompare(),50);
	cout << endl;
	swap(v1, v2);//注意交换的容器为同种类型
	cout << "替换后" << endl;
	for_each(v2.begin(), v2.end(), myPrint);
}
int main() {

	test01();


}
//replace_if
