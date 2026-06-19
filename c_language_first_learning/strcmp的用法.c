#include<stdio.h>
#include<string.h>

int main()
{
	char str1[] = "apple";
	char str2[] = "banana";
	
	int ret = strcmp(str1,str2);
	if (ret == 0)
	    printf('str1和str2相等\n');
	else if (ret > 0)
	    printf("str1大于str2\n");
	else
	    printf("str1小于str2\n");
	    
	    return 0;
}
