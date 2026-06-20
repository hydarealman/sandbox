#include<iostream>
using namespace std;
int g_a;
int g_b;

const int c_a = 10;
const int c_b = 10;

static int s_g_a = 10;
static int s_g_b = 10;

int main() {
	int a=10;
	int b=10;

	const int c_l_a = 10;
	const int c_l_b = 10;

	static int s_a = 10;
	static int s_b = 10;
	
	

	cout << "全局变量数据g_a的地址" << (int)&g_a << endl;
	cout << "全局变量数据g_b的地址" << (int)&g_b << endl;

	cout << "静态局部变量数据s_a的地址" << (int)&s_a << endl;
	cout << "静态局部变量数据s_b的地址" << (int)&s_b << endl;

	cout << "字符串常量的地址为" << (int)&"hello world" << endl;

	cout << "全局常量的地址为" << (int) & c_a << endl;

	cout << "全局静态变量s_g_a的地址为" << (int)&s_g_a << endl;
	cout << "全局静态变量s_g_b的地址为" << (int)&s_g_b << endl;

	cout << "局部变量数据a的地址" << (int)&a << endl;
	cout << "局部变量数据b的地址" << (int)&b << endl;

	cout << "局部常量c_l_a的地址" << (int)&c_l_a << endl;
	cout << "局部常量c_l_b的地址" << (int)&c_l_b << endl;

	system("pause");

	return 0;
}