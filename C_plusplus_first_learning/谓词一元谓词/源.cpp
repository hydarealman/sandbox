#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>
//仿函数 返回值类型是BOOL数据类型，称为谓词
class GreaterFive {
public:
	bool operator()(int val) {//谓词
		return val > 5;
	}
};
void test01() {
	vector<int> v;
	for (int i = 0; i < 10; i++) {
		v.push_back(i);
	}
	vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterFive());//传进来一个匿名的函数对象
	if (it == v.end()) {
		cout << "没找到" << endl;
	}
	else {
		cout << "找到了大于5的数字" << endl;
	}
}
int main() {

	system("pause");
	return 0;
}