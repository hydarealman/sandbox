//#include<stdio.h>
//int main() {
//	int a = 0;
//	int b = 0;
//	unsigned int c = 0;
//	unsigned int d = 0;
//	float e = 0.0;
//	float f = 0.0;
//	double g = 0.0;
//	double h = 0.0;
//	char i = '0';
//	char j = '0';
//	long k = 11111111;
//	long l = 11111111;
//	printf("%-10d", a);
//	printf("%-10d", b);
//    printf("%10.2d",f);
//	printf("%15.3e", e);
//	printf("\n");
//	printf("请输入一个数字");
//	scanf_s("%d", &a);
//	printf("%d", a);
//}
//#include<stdio.h>
//void main()
//{
//	int a, b;
//	float x, y;
//	char c1, c2;
//	scanf_s("%d%d", &a, &b);
//	scanf_s("%f%f", &x, &y);
//	getchar();
//	scanf_s(" %c", &c1);
//	getchar();
//	scanf_s(" %c", &c2);
//	printf("a:%d\tb:%d\tx:%f\ty:%e\tc1:%c\tc2:%c", a, b, x, y, c1, c2);
//}
//#include<stdio.h>
//int main() {
//	int x, y;
//	scanf_s("%d%d", &x, &y);
//	int z = x + y;
//	printf("%d + %d = %d", x, y, z);
//}
//#include<stdio.h>
//int main() {
//	char letter;
//	scanf_s("%c", &letter);
//	printf("%c", letter - 32);
//}
//#include<stdio.h>
//int main() {
//	int temperature;
//	scanf_s("%d", &temperature);
//	float f = (5 / 9.0) * (temperature - 32);
//	printf("%.2f", f);
//}
//#include<iostream>
//#define PI 3.14159
//using namespace std;
//class column {
//private:
//	float r;
//	float h;
//public:
//	float getr() {
//		cin >> r;
//		return r;
//	}
//	float geth() {
//		cin >> h;
//		return h;
//	}
//	float calculate_l() {
//		float m_l = 2 * PI * r;
//		return m_l;
//	}
//	float calculat_v() {
//		float m_v = PI * r * r * h;
//		return m_v;
//	}
//	float calculate_s() {
//		float m_s = PI * r * r;
//		return m_s;
//	}
//};
//int main() {
//	column c1;
//	c1.getr();
//	c1.geth();
//	cout << c1.calculate_l() << endl;
//	cout << c1.calculate_s() << endl;
//	cout << c1.calculat_v() << endl;
//
//}
#include<stdio.h>
#include<math.h>
int main() {
	int a, b, c;
	scanf_s("%d%d%d", &a, &b, &c);
	float area;
	float s;
	s = (a + b + c) / 2;
	float temp = s * (s - a) * (s - b) * (s - c);
	area = pow(temp, 0.5);
	printf("%.3f", area);
}
