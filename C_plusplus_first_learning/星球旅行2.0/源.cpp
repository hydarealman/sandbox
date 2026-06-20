#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
#define NUM 10
using namespace std;
void calculateNumber(int num, vector<long long>* result) {
	for (int i = 0; i < num; i++)
		for (int j = 0; j < num; j++)
			for (int x = 0; x < num; x++) {
				result->push_back(pow(3, i) * pow(5, j) * pow(7, x));
			}
	return;
}
int binarySearch(vector<long long> result, long long target) {
	int left = 0;
	int right = result.size() - 1;
	while (left <= right) {
		int middle = (left + right) / 2;
		if (result[middle] < target) {
			left = middle + 1;
		}
		else if (result[middle] > target) {
			right = middle - 1;
		}
		else if(result[middle] == target) {
			return middle;
		}
		else {
			return -1;
		}
	}
}
int main() {
	long long n;
	scanf_s("%lld", &n);
	vector<long long> result(10000);
	calculateNumber(NUM, &result);
	sort(result.begin(), result.end());
	result.erase(unique(result.begin(), result.end()), result.end());
	printf("%d", binarySearch(result, n));
}