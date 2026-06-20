#pragma once
//记录飞机，子弹的相关数据
#include<stdlib.h>
#include<assert.h>
//链表结点的结构体 (这个类型就是我方飞机，敌机，子弹的类型)
/*typedef*/ struct Node {
	int x;//x坐标
	int y;//y坐标
	int speed;//移动速度
	struct Node* next;//指针，用来指向下一个节点
}/*Node*/;

//链表结构的结点
typedef struct LinkList {
	struct Node* head;
	struct Node* end;
}LL;

//创建链表结点函数
Node* Node_init(int x,int y,int speed) {
	Node* temp = (Node*)malloc(sizeof(Node));
	assert(temp);
	temp->x = x;
	temp->y = y;
	temp->speed = speed;
	temp->next = NULL;
	return temp;
}
//单链表结点插入函数 尾插法
void LinkList_insert(LL* list,int x,int y,int speed) {
	if (list == NULL) {
		return;
	}
	if (list->head == NULL) {
		list->head = list->end = Node_init(x, y, speed);
	}
	else {
		list->end->next = Node_init(x, y, speed);
		list->end = list->end->next;//更新尾指针

	}
}