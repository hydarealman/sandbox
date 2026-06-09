#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#define MYFIFO "myfifo"

int main()
{
   int fd;
   int nread;
   int line_count = 0;   // 统计接收到的行数

   if (access(MYFIFO, F_OK) == -1)
   {
       if ((mkfifo(MYFIFO, 0666) < 0) && (errno != EEXIST))
       {	       
           printf("Cannot create fifo file\n");
           exit(1);
       }
   }   
   fd = open(MYFIFO, O_RDONLY);
   if (fd == -1)
   {   
     printf("open fifo file error.\n");
     exit(1);
   }      
   while (1)
   { 
     char buff[128] = {0};
     int n = read(fd, buff, 127);	   
     if (n == 0)
     {
       printf("对方已关闭!\n");
       printf("一共接收了 %d 行信息。\n", line_count);
       break;
     }
     line_count++;
     printf("read(n=%d): %s", n, buff);
   }
   close(fd);
   exit(0);
}