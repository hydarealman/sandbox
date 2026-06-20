#include<iostream>
using namespace std;
//普通实现页面
//class Java {
//public:
//	void header() {
//		cout << "首页，狗开课，登陆，注册...(公共头部）" << endl;
//	}
//	void footer() {
//		cout << "帮助中心，交流合作，站内地图。。。（公共底部" << endl;
//	}
//	void left() {
//		cout << "Java,Python,C++,...(公共分类列表)" << endl;  
//	}
//	void content() {
//		cout << "Java学科视频" << endl;
//	}
//};
//class Python {
//public:
//	void header() {
//		cout << "首页，狗开课，登陆，注册...(公共头部）" << endl;
//	}
//	void footer() {
//		cout << "帮助中心，交流合作，站内地图。。。（公共底部" << endl;
//	}
//	void left() {
//		cout << "Java,Python,C++,...(公共分类列表)" << endl;
//	}
//	void content() {
//		cout << "Python学科视频" << endl;
//	}
//};
class BasePage {
public:
	void header() {
		cout << "首页，狗开课，登陆，注册...(公共头部）" << endl;
	}
	void footer() {
		cout << "帮助中心，交流合作，站内地图。。。（公共底部" << endl;
	}
	void left() {
		cout << "Java,Python,C++,...(公共分类列表)" << endl;
	}
	void content() {
		cout << "Python学科视频" << endl;
	}
};
//Java页面
class Java : public BasePage {
public:
	void content() {
		cout << "Java学科视频" << endl;
	}
};
//Python页面
class Python : public BasePage {
public:
	void content() {
		cout << "Python学科视频" << endl;
	}
};
//C++页面
class CPP : public BasePage {
public:
	void content() {
		cout << "Cpp学科视频" << endl;
	}
};
void test01() {
	cout << "Java的页面如下" << endl;
	Java ja;
	ja.header();
	ja.footer();
	ja.left();
	ja.content();
	cout << "----------------------------------------------" << endl;
	cout << "Python的页面如下" << endl;
	Python py;
	py.header();
	py.footer();
	py.left();
	py.content();
}
int main() {
	test01();
	system("pause");
	
	return 0;
}
//继承的好处
//语法 ： class子类 ： 继承方式 父类
//子类 也称为派生类
//父类 也成为基类