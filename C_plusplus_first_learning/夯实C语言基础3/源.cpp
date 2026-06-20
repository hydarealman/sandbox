//#include<stdio.h>
//#define MSG "I am a string constant."
//#define MAXLENGTH 81
//int main() {
//	char words[MAXLENGTH] = "I am a string in an arry.";
//	const char* pt1 = "Something is pointing at me.";
//	puts("Here are some strings");
//	puts(MSG);
//	puts(words);
//	puts(pt1);
//	words[8] = 'p';
//	puts(words);
//
//
//	printf("\"helloworld\"");
//	return 0;
//}

//#include<stdio.h>
//int main() {
//	printf("%s,%p,&c\n", "We", "are", *"space farers");
//}
//#include<stdio.h>
//int main() {
//	const char* p1 = "hello world";
//}

//指针数组
//字符数组
//#include<stdio.h>
//#define SLEN 40
//#define LIM 5
//int main() {
//	const char* mytelents[LIM] = {
//	"adding numbers swiftly"
//	};
//	char yourtelents[LIM][SLEN] = {
//		"hello world"
//	};
//
//	return 0;
//}
//#include<stdio.h>
//int main() {
//	const char* mesg = "Don't be a ffool";
//	const char* copy;
//
//	copy = mesg;
//	printf("%s\n", copy);
//	printf("mesg = %s; &mesg = %p; value = %p\n",mesg,&mesg,mesg);
//	printf("copy = %s; &copy = %p; value = %p\n",copy,&copy,copy);
//
//}
//#include<stdio.h>
//#define STELEN 81
//int main() {
//	char words[STELEN];
//
//	puts("enter a string please");
//	gets(words);//c11已经将gets函数移除了
//}

//#include<stdio.h>
//#define STLEN 14
//int main() {
//	char words[STLEN];
//	puts("Entsr a string ,please.");
//	fgets(words, STLEN, stdin);
//	printf("your string twice (puts(),then fputs()):\n");
//	puts(words);
//	fputs(words, stdout);
//	puts("Done.");
//
//	return 0;
//}

//#include<stdio.h>
//int main() {
//	char name1[11], name2[11];
//	int count;
//
//	printf("please enter 2 name.\n");
//	count = scanf_s("%5s %10s ", name1, name2);
//	printf("I read the %d names %s and %s.\n",count,name1,name2);
//
//	return 0;
//}