#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"
using namespace std;
class SpeechManager {
public:
	//构造函数
	SpeechManager();
	//清空记录
	void clearRecord();
	//显示往届得分
	void showRecord();
	//读取记录
	void loadRecord();
	//保存记录
	void saveRecord();
	//显示分数
	void show_Score();
	//比赛
	void speechContest();
	//抽签
	void speechDraw();

	//开始比赛   比赛流程控制
	void startSpeech();

	//创建选手
	void creatSpeaker();

	//初始化成员属性
	void initSpeech();

	//菜单功能
	void show_menu();

	//退出功能
	void exitSystem();

	//析构函数
	~SpeechManager();

	//成员属性
	//保存第一轮选手的属性
	vector<int> v1;
	//第一轮选手晋级容器
	vector<int> v2;
	//胜出选手晋级容器
	vector<int> vVictory;
	//存放编号
	map<int, Speaker> m_Speaker;
	//存放比赛轮数
	int m_Index;
	//文件为空的标志
	bool filesEmpty;
	//往届记录
	map<int, vector<string>> m_Record;
};