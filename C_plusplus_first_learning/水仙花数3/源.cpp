#include<stdio.h>
#include<math.h>
int main() {
	int T;
	scanf_s("%d", &T);
	while(T--) {//测试组数
		int N;
		scanf_s("%d", &N);
		
		for (int i = 2; i < pow(10,N); i++) {
			int selectnumber = i;//防止处理数据时改变循环，保护循环数据
			int sum = 0;
			for (int j = 0; j < N; j++) {
				sum += pow(selectnumber%10, N);//计算个水仙花位数N次方
				selectnumber /= 10;
			}
			if (sum == i) {
				printf("%d\n", i);//输出水仙花数
			}
		}
	}

	return 0;
}