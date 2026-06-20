#include<iostream>
#include<algorithm>
using namespace std;
int main() {
	int a[6] = { 2,5,8,9,6,3 };
	sort(a, a + 6);
	for (int i = 0; i < 6; i++) {
		cout << a[i] << " ";
	}
}