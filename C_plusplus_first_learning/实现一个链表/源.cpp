#include<stdio.h>
#include<stdlib.h>
struct node {
	int date;
	node* next;
};
int main() {
	int n;
	printf("请输入链表的长度");
	scanf_s("%d", &n);
	node* p = NULL, * q = NULL, * head = NULL;
	for (int i = 0; i < n; i++) {
		p = (node*)malloc(sizeof(node));
		scanf_s("%d", &(p->date));
		if (head == NULL) head = p;
		else q->next = p;
		q = p;
	}
	p->next = NULL;
	for (p = head; p != NULL; p = p->next) {
		printf("%d ", p->date);
	}
}