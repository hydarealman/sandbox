#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define SHM_KEY  1234

typedef struct {
    int ready;          // 0: 可写, 1: 已写未读
    char data[128];
} SharedData;

int main()
{
    int shmid;
    SharedData *p = NULL;
    
    shmid = shmget(SHM_KEY, sizeof(SharedData), IPC_CREAT|0666);
    if (shmid < 0) {
        perror("shmget fail");
        exit(1);
    }
    
    p = (SharedData *)shmat(shmid, NULL, 0);
    if (p == (SharedData *)-1) {
        perror("shmat fail");
        exit(1);
    }
    
    while (1) {
        // 等待对方写入（ready == 1）
        while (p->ready != 1) {
            usleep(1000);
        }
        
        // 打印收到的内容
        printf("读取到: %s", p->data);
        
        // 如果收到 "quit"，退出循环
        if (strncmp(p->data, "quit", 4) == 0) {
            p->ready = 0;   // 可选：清除标志
            break;
        }
        
        // 重置标志，表示已经读完，允许写入下一行
        p->ready = 0;
    }
    
    shmdt(p);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}