//以关键字_Thread_local声明一个对象时，每个线程都获得该变量的私有备份
//C语言变量四大属性：存储类，作用域，生命周期，链接属性
//关键字externextern是C语言的一个关键字，可以用来修饰函数与变量,当extern修饰一个变量或函数时时，就是在声明这个变量(函数)，告诉编译器在外部文件中已经这个变量(函数)，要通过编译。
//#include<stdio.h>
//int main() {
//	extern int a;
//	extern int b;
//	printf("%d", a + b);
//
//
//}
//#include<stdio.h>
//void report_count();
//void accumulate(int k);
//int count = 0;
//int main() {
//	int value;
//	register int i;
//	printf("enter a positive integrt (0 to quit)");
//	while (scanf_s("%d", &value) == 1 && value > 0) {
//		++count;
//		for (i = value; i >= 0; i++) {
//			accumulate(i);
//			printf("enter a positive integer");
//		}
//		report_count();
//
//		return 0;
//	}
//}
//void report_count() {
//	printf("loop executed %d times\n");
//}
//void accumulate(int k) {
//
//}
//#include<stdio.h>
//void func() {
//	
//}
//int main() {
//	register int i = 0;
//	register int j = 0;
//	for (i = 0; i < 1000; i++) {
//		for (j = 0; j < 1000; j++) {
//			func();
//		}
//	}
//}
//
