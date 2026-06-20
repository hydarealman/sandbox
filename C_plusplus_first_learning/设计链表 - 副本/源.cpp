#include<iostream>
using namespace std;

struct linkednode {
	int val;
	linkednode* next;
	linkednode(int val):val(val),next(nullptr){}
};


int get(int index) {
	if (index < 0 || index >= size) {
		return -1;
	}
	listnode* cur = head;
	for (int i = 0; i <= index; i++) {
		cur = cur->next; 
	}
	return cur->val;
}
mylinkedlist() {
	_dummyhead = new linkednode(0);
	_size = 0;
}

void addathead(int val) {
	linkednode* newnode = new linkednode(val);
	linkednode* cur = _dummyhead->next
}
void addatindex(int index, int val) {
	if (index > _size) return;
	if (idex < 0) index = 0;
	linkednode* newnode = new linkednode(val);
	linkednode* cur = _dummyheead;
	while (index--) {
		cur = cur->next;
	}
	linkednode->next = cur->next;
	cur->next = newnode;
	_size++;
}
void deleteatindex(int index) {
	if (index >= size || index < 0) {
		return;
	}
	linkednode* cur = _dummyhead;
	while (index--) {
		cur = cur->next;
	}
	linkednode* tmp = cur->next;
	cur->next = cur->next->next;
	delete tmp;
	tmp = nullptr;
	_size++;
}
void printlinkedlist() {
	linkednode* cur = _dummyhead;
	while (cur->next != nullptr) {
		cout << cur->next->val << "";
		cur = cur->next;
	}
	cout << endl;
private:
	int size;
	listnode* head;



	