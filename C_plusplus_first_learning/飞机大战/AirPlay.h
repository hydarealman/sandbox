#pragma once
#include<easyx.h>
//图形窗口的大小
#define BGWEIGHT 400
#define BGHEIGHT 600
//我方飞机的大小
#define MYAIRWEIGHT 25
#define MYAIRHEIGHT 40
//敌机的大小
#define ENEMYPANEWEIGHT 25
#define ENEMYPANEHEIGHT 25
//子弹的大小
#define BulletWeight 8
#define BulletHeight 8
//1.打开窗口，加载图片，链表结构实现，变量的定义
//2.生成我方飞机，我方飞机的移动
//3.子弹的生成，发射，释放

IMAGE img[4];//图片数组

//初始化函数
void init() {
	//加载图片
	loadimage(&img[0],"res\\黑猴背景.png",BGWEIGHT, BGHEIGHT);
	loadimage(&img[1], "res\\无敌战神奶龙.png", MYAIRWEIGHT, MYAIRHEIGHT);
	loadimage(&img[2], "res\\奶龙大哭.png", ENEMYPANEWEIGHT, ENEMYPANEHEIGHT);
	loadimage(&img[3], "res\\狗头.png", BulletWeight, BulletHeight);
}

//我们所有的功能，都从这个函数开始
void start() {
	initgraph(BGWEIGHT, BGHEIGHT);

	//初始化

	while (1) {
		
	};

	closegraph();
}