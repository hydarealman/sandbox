listnode reverselist(listnode* head) {
	listnode* temp;
	listnode* cur = head;
	listnode* pre = NULL;

	while (cur) {
		temp = cur->next;
		cur->next = pre;
		pre = cur;
		cur = temp;
	}
	return pre;
}