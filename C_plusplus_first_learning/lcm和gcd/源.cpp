#include<iostream>
using namespace std;
//最大公因数
//法一
//int gcd(int a, int b) {
//	int r;
//	while (b > 0) {
//		r = a % b;
//		a = b;
//		b = r;
//	}
//	return a;
//}
//法二
//int gcd(int a, int b) {
//	return b > 0 ? gcd(b, a % b) : a;
//}
//法三
//int gcd(int a, int b) {
//	while (b ^= a ^= b ^= a %= b);
//}
//int main() {
//
//}
//求最小公倍数
//int gcd(int a, int b) {
//	return b > 0 ? gcd(b, a % b) : a;
//}
//int lcm(int a, int b) {
//	return a / gcd(a, b) * b;
//}