#include<iostream>
using namespace std;
#include<fstream>
class person {
public:

	char m_Name[64];//最好不用c++string，会出现一些问题
	int m_Age;
};

void test01() {
	//包含头文件
	//创建流对象
	ofstream ofs;
	//打开文件
	ofs.open("person.txt", ios::out | ios::binary);
	//写文件
	person p = { "张三",18 };
	ofs.write((const char*)&p, sizeof(person));
	//关闭文件
	ofs.close();
}
void test02() {
	//包含头文件
	//创建流对象
	ifstream ifs;
	//打开文件 判断文件是否打开成功
	ifs.open("person.txt", ios::in | ios::binary);

	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}
	//读文件
	person p;
	ifs.read((char*)&p, sizeof(person));
	cout << p.m_Name << p.m_Age << endl;
	//关闭文件
	ifs.close();
}
int main() {

	test01();
	test02();
	system("pause");
	return 0;
}