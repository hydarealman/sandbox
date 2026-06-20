#include<iostream>
#include<algorithm>
using namespace std;
//冒泡排序
void BUbbleSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (a[j] > a[j + 1]) {
				int t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
	}
}
//互质最大公约数为1的数
//最大公约数
int gcd1(long a, long b) {
	return b == 0 ? a : gcd(b, a % b);
}
bool isPrime(int n) {
	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}
//最大公约数
int gcd2(int a, int b) {
	int r;
	while (b > 0) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}
//最大公约数
int gcd(int a, int b) {
	while (b ^= a ^= b ^= a %= b);
}
//求最小公倍数
int gcd(int a, int b) {
	return b > 0 ? gcd(b, a % b) : a;
}
int lcm(int a, int b) {
	return a / gcd(a, b) * b;
}
//快速幂运算
long pow_2(int b) {
	long x = 2;
	long res = 1;
	while (b > 0) {
		if (b & 1)
		res *= x;
		b >>= 1;
		x = x * x;
	}
	return res;
}
//判断素数
bool isPrime(int n) {
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0)
			return false;
	}
	return true;
}
//全排列总结
bool check() {
	//依考试情况定
}
//



//优先队列



//数组
//二分查找
//移除元素
//双指针
//螺旋矩阵
//前缀和

int main() {

}