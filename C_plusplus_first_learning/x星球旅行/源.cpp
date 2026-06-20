#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
#define NUM 10
using namespace std;
void calculateNumber(int num ,vector<long long>* result) {
	for (int i = 1; i < num; i++)
		for (int j = 1; j < num; j++)
			for (int x = 1; x < num; x++) {
				result->push_back(static_cast<long long>(pow(3, i)) * static_cast<long long>(pow(5, j)) * static_cast<long long>(pow(7, x)));
			}
	return;
}
int binarySearch(vector<long long> result , long long target) {
	int left = 0;
	int right = result.size() - 1;
	while (left <= right) {
		int middle = (left + right)/2;
		if (result[middle] < target) {
			left = middle + 1;
		}
		else if (result[middle] > target) {
			right = middle - 1;
		}
		else  {
			return middle;
		}
	}
}
int main() {
	long long n;
	scanf_s("%lld", &n);
	vector<long long> result;
	calculateNumber(NUM, &result);
	sort(result.begin(), result.end());
	result.erase(unique(result.begin(), result.end()),result.end());
	printf("%d", binarySearch(result,n));
}