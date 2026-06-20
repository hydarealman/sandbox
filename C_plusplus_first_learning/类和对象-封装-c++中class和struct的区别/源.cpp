#include<iostream>
#include<string>
using namespace std;
struct student1 {
	string name = "张三 ";
};
class student2 {
	string name = "张三 ";
};
int main() {
	student1 s1;
	student2 s2;//class和struct的区别
	s1.name = "张三 ";//struct 默认权限公共
	s2.name = "李四 ";//class 默认权限私有

}