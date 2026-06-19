#include<iostream>
#include<string>
using namespace std;
int main() {
	int num[] = {2,6,3,5,8,9,6,4,2,2,5,2};
	int val = 2;
	int len = sizeof(num) / 4;
	int left = 0;
	for (int right = 0; right < len; right++) {
		if (num[left] != num[right]) {
			num[left] = num[right];
			left++;
		}
		return left;

	}
	for (int i = 0; i < 11; i++) {
		cout << num[i] << "";
	}
}
