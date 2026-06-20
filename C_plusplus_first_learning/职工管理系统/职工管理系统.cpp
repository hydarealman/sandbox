#include<iostream>
using namespace std;
#include"workerManager.h"
#include"worker.h"

int main() {

	//实例化管理者对象
	WorkerManager wm;

	int choice = 0;//用来存储用户的选项

	while (true) {

		//调用展示菜单成员函数
		wm.Show_Menu();

		cout << "请输入您的选择" << endl;
		cin >> choice;//接受用户的选择//为什么输入字母就会一直刷频

		switch (choice) {
		case 0://退出系统
			wm.ExitSystem();
			break;
		case 1://增加职工
			wm.Add_Emp();
			break;
		case 2://显示职工
			wm.show_Emp();
			break;
		case 3://删除职工 // switch语句如果过长需要括起来
			wm.Del_Emp();//问题每次都剩一个删不完
			break;
		case 4://修改职工
			wm.Mod_Emp();
			break;
		case 5://查找职工
			wm.find_Emp();
			break;
		case 6://排序职工
			wm.sort_Emp();
			break;
		case 7://清空文档
			wm.clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}

	

	system("pause");

	return 0;
}