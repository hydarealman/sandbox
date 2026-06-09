#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

#define SHM_KEY  1234
#define SHM_SIZE 256   // 共享内存总大小（包含flag区域）

// 自定义结构：包含一个标志位和一个数据缓冲区
typedef struct {
    int ready;          // 0: 可写, 1: 已写未读
    char data[128];
} SharedData;

int main()
{
    int shmid;
    SharedData *p = NULL;
    
    // 创建/获取共享内存
    shmid = shmget(SHM_KEY, sizeof(SharedData), IPC_CREAT|0666);
    if (shmid < 0) {
        perror("shmget fail");
        exit(1);
    }
    
    // 映射
    p = (SharedData *)shmat(shmid, NULL, 0);
    if (p == (SharedData *)-1) {
        perror("shmat fail");
        exit(1);
    }
    
    // 初始标志：可写
    p->ready = 0;
    
    while (1) {
        // 等待对方读完（即 ready == 0）
        while (p->ready != 0) {
            usleep(1000);  // 稍作等待，避免CPU空转
        }
        
        // 从键盘读入一行（最多127字符）
        printf("输入: ");
        fgets(p->data, 127, stdin);
        // 去掉末尾换行（可选）
        // p->data[strcspn(p->data, "\n")] = '\0';
        
        // 设置标志，表示已写入，等待读取
        p->ready = 1;
        
        // 如果输入 "quit"，则退出循环
        if (strncmp(p->data, "quit", 4) == 0) {
            break;
        }
    }
    
    // 解除映射并删除共享内存
    shmdt(p);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}