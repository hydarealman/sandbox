#include<iostream>
using namespace std;
#include<fstream>
#include<string>

void test01() {
	ofstream ofs;
	ofs.open("test.txt", ios::out);
	ofs << "姓名:张三" << endl;
	ofs << "性别男" << endl;
	ofs << "年龄18" << endl;
	ofs.close();
}
void test02() {
	ifstream ifs;
	ifs.open("test.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}
	//4.读数据
	/*char buf[1024] = { 0 };
	while (ifs >> buf) {
		cout << buf << endl;
	}
	ifs.close();*/

	/*char buf[1024] = { 0 };
	while (ifs.getline(buf, sizeof(buf))) {
		cout << buf << endl;
	}*/

	/*string buf;
	while (getline(ifs, buf)) {
		cout << buf << endl;
	}*/

	char c;//不推荐使用
	while ((c = ifs.get()) !=EOF) {//赋值运算符从右往左
		cout << c;
	}
	ifs.close();
}
int main() {
	
	test02();

	system("pause");
	return 0;
}