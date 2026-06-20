#include<iostream>
#include<string>
#define MAX 1000
using namespace std;

struct person {
	string m_name;
	int m_sex;
	int m_age;
	string m_phone;
	string m_addr;
};

struct addresbooks {
	struct person personarray[MAX];
	int m_size;

};

int isexit(addresbooks* abs, string name) {//abs在这里声明已经变成指针了
	for (int i = 0; i < abs->m_size; i++) {
		if (abs->personarray[i].m_name == name)
			return i;
	}
	return -1;
}

void clearperson(addresbooks* abs) {
	abs->m_size = 0;
	cout << "通讯录已清空" << endl;
	system("pause");
	system("cls");
}

void modifyperson(addresbooks* abs) {
	cout << "请输入需要修改的联系人" << endl;
	string name;
	cin >> name;

	int ret = isexit(abs, name);
	if (ret != -1) {
		//姓名：
		cout << "请输入联系人姓名:" << endl;
		cin >> name;
		abs->personarray[ret].m_name = name;
		//年龄
		cout << "请输入联系人年龄" << endl;
		int age;
		cin >> age;
		abs->personarray[ret].m_age = age;
		//性别
		int sex;
		cout << "请输入性别" << endl;
		cout << "男--1" << endl;
		cout << "女--2" << endl;
		cin >> sex;
		while (true) {
			cout << "输入有误请重新输入" << endl;
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personarray[ret].m_sex = sex;
				break;
			}
				
		}
		//电话
		cout << "请输入电话" << endl;
		string phone;
		cin >> phone;
		abs->personarray[ret].m_phone = phone;
		//地址
		cout << "请输入地址" << endl;
		string addr;
		cin >> addr;
		abs->personarray[ret].m_addr = addr;
	}
	else
		cout << "查无此人" << endl;
	system("pause");
	system("cls");
}

void findperson(addresbooks* abs) {
	cout << "请输入你要查找的联系人" << endl;
	string name;
	cin >> name;
	int ret = isexit(abs, name);
	if (ret != -1) {
		cout << "找到此人：" << endl;
		cout << "姓名：" << abs->personarray[ret].m_name << "\t" ;
		cout << "性别：" << abs->personarray[ret].m_sex << "\t" ;
		cout <<"年龄"<< abs->personarray[ret].m_age << "\t" ;
		cout <<"电话："<< abs->personarray[ret].m_phone << "\t";
		cout <<"地址"<< abs->personarray[ret].m_addr << "\t" ;
	}
	else {
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}

void deleteperson(addresbooks* abs) {
	string name;

	cout << "输入你要删除的联系人" << endl;

	cin >> name;
	int ret = isexit(abs, name);
	if(ret != -1){
		for (int i = ret; i < abs->m_size; i++) {
			abs->personarray[i] = abs->personarray[i + 1];
	}
		abs->m_size--;
		cout << "删除成功" << endl;
	}
	else {
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}


void addperson(addresbooks* abs) {
	if (abs->m_size == MAX) {
		cout << "通讯录已满,无法添加!" << endl;
		return;
	}
	else {
		//添加联系人

		//姓名
		string name;
		cout << "请输入联系人姓名" << endl;
		cin >> name;
		abs->personarray[abs->m_size].m_name = name;
		//性别
		
		while (true) {
			int sex = 0;
			cout << "请输入性别" << endl;
			cout << "男---1" << endl;
			cout << "女---2" << endl;
			cin >> sex;
			if (sex == 1 || sex == 2) {
				abs->personarray[abs->m_size].m_sex = sex;
				break;
			}
				cout << "输入有误请重新输入" << endl;
		}
		//年龄
		int age = 0;
		cout << "请输入年龄" << endl;
		cin >> age;
		abs->personarray[abs->m_size].m_age = age;
		//电话
		string phone;
		cout << "请输入电话号码" << endl;
		cin >> phone;
		abs->personarray[abs->m_size].m_phone = phone;
		//地址
		cout << "请输入地址" << endl;
		string addr;
		cin >> addr;
		abs->personarray[abs->m_size].m_addr = addr;

		//更新通讯录人数
		abs->m_size++;
		cout << "你添加成功了" << endl;
		system("pause");
		system("cls");
	}
}

void showperson(addresbooks* abs) {
	if (abs->m_size == 0) {
		cout << "当前记录为空" << endl;
	}
	else {
		for (int i = 0; i < abs->m_size; i++) {
			cout << "姓名" << abs->personarray[i].m_name << "\t";
			cout << "年龄" << abs->personarray[i].m_age << "\t";
			cout << "性别" << abs->personarray[i].m_sex << "\t";
			cout << "电话号码" << abs->personarray[i].m_phone << endl;
			cout << "地址" << abs->personarray[i].m_addr << endl;
			system("pause");
			system("cls");
		}
	}

}

void showmenu() {
	cout << "**********************" << endl;
	cout << "**** 1.添加联系人 ****" << endl;
	cout << "**** 2,显示联系人 ****" << endl;
	cout << "**** 3,删除联系人 ****" << endl;
	cout << "**** 4,查找联系人 ****" << endl;
	cout << "**** 5,修改联系人 ****" << endl;
	cout << "**** 6,清空联系人 ****" << endl;
	cout << "**** 0,退出通讯录 ****" << endl;
	cout << "**********************" << endl;
}
int main() {
	
	addresbooks abs;
	abs.m_size = 0;
	
	while (true) {

		showmenu();
		int select;
		cin >> select;

		switch (select) {
		case 1:
			addperson(&abs);
			break;
		case 2:
			showperson(&abs);
			break;
		case 3:
			deleteperson(&abs);
			break;
		case 4:
			findperson(&abs);
			break;
		case 5:
			modifyperson(&abs);
			break;
		case 6:
			clearperson(&abs);
			break;
		case 0:
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
			cout << "你输入的选项有误，请重新输入" << endl;
		}

	}

	system("pause");
	return 0;
}