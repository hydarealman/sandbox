#include<stdio.h>

int main()
{   const int N = 3;
    int score[N];
	for(int i = 0; i < 3 ; i++)
	scanf("%d", &score[i]);
	
	printf("average:%f", (score[0] + score[1] + score[2]) / (float) N );
}
	


