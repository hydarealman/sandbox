#include<iostream>
using namespace std;
struct listnode {
	int val;
	listnode* next;
	listnode(int x) : val(val), next(NULL){}
};
class solution {
public:
	listnode* getintersectionnode(listnode* heada, listnode* headb) {
		listnode* cura = heada;
		listnode* curb = headb;
		int lena = 0, lenb = 0;
		while (cura != NULL) {
			lena++;
			cura = cura->next;
		}
		while (curb != NULL) {
			lenb++;
			curb = curb->next;
		}
		cura = heada;
		curb = headb;
		if (lenb > lena) {
			swap(lena, lenb);
			swap(cura, curb);
		}
		int gap = lena - lenb;
		while (gap--) {
			cura = cura->next;
		}
		while (cura != NULL) {
			if (cura == curb)
				return cura;
		}
		cura = cura->next;
		curb = curb->next;
	}
	return NULL;
};