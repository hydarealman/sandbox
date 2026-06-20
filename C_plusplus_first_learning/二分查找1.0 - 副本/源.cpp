#include<iostream>
#include<string>
using namespace std;

int findmiddle(int right,int target,int left,int sums[]) {

	while (left <= right) {
		int middle = left + ((right + left) / 2);
		if (sums[middle] > target) {
			right = middle - 1;
		}
		else if (sums[middle] < target) {
			left = middle + 1;
		}
		else
			return middle;
	}
}
int main() {
	int sums[] = { 1,2,5,9,11,44,75,103 };
	int left = 0;
	int target = 9;
	int right = sizeof(sums)/sizeof(sums[0]) - 1;
	cout << findmiddle(right,target,left,sums) << endl;
	
	return 0;
}