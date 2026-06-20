#include<iostream>
using namespace std;
template<typename T>
void mySort(T arry[], int len) {
	for (int i = 0; i < len; i++) {
		int max = i;
		for (int j = i; j < len; j++) {
			if (arry[max] < arry[i]) {
				max = j;
			}
		}
		if (max != i) {
			T temp = arry[i];
			arry[i] = arry[max];
			arry[i] = temp;
		}
	}
}
void test01() {
	char arry[] = "bcadfe";
	int arr[] = { 2,3,6,5,4,1,0 };
	int len = sizeof(arr) / sizeof(int);
	mySort(arry , len);
	for (int i = 0; i < 6; i++) {
		cout << arry[i] << " ";
	}
	mySort(arr, 7);
	cout << endl;
	for (int i = 0; i < 7; i++) {
		cout << arr[i] << " ";
	}
}
int main() {

	test01();

	system("pause");
	return 0;
}