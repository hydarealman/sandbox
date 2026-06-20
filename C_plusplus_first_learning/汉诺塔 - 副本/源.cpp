//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//void move(int n, vector<int>& A, vector<int>& B, vector<int>& C) {
//	if (n == 1) {
//		C.push_back(A.back());
//		A.pop_back();
//		return;
//	}
//	move(n - 1, A, C, B);
//	C.push_back(A.back());
//	A.pop_back();
//	move(n - 1, B, A, C);
//}
//void myPrint(int val) {
//	cout << val << endl;
//}
//int main() {
//	vector<int>A;
//	vector<int>B;
//	vector<int>C;
//	for (int i = 0; i < 4; i++) {
//		A.push_back(i);
//	}
//	move(A.size(), A, B, C);
//	for_each(C.begin(), C.end(), myPrint);
//}