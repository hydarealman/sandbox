#include<iostream>
using namespace std;
void bubblesort(int* arr, int len);
int main() {
	int arr[] = { 6,5,2,3,6,9,8,5,4,1,2,2,8,7,3 };
int len = sizeof(arr) / sizeof(arr[0]);

for (int i = 0; i < len; i++)
	cout << arr[i] << "";
cout << endl;

 bubblesort( arr, len);
system("pause");

}
void bubblesort(int* arr, int len) {
	for (int i = 0; i < len - 1; i++){
		int temp = 0;
		for (int j = 0; j < len - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = arr[j];
			}
		}
		}
	for (int i = 0; i < len; i++)
		cout << arr[i] << "";
}
