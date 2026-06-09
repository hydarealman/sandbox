#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#define MYFIFO "myfifo"

int main(int argc, char *argv[])
{
   int fd;      
   fd = open(MYFIFO, O_WRONLY);
   if (fd == -1)
   {   
     printf("open fifo file error.\n");
     exit(1);
   } 
   while(1)
   {  
      char buff[128] = {0};
      fgets(buff, 128, stdin);
      if (strncmp(buff, "end", 3) == 0)
         break;
      write(fd, buff, strlen(buff));
   }   
   close(fd);
   exit(0);
}