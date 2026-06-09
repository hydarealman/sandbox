#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <windows.h>

#define N 8

int g_Buffer[N];            // 缓冲区
int g_in = 0, g_out = 0;    // 生产者放置位置,消费者取出位置
CRITICAL_SECTION g_cs;      // 临界区对象,保护g_in, g_out, g_Buffer 的互斥访问
HANDLE g_hEmpty, g_hFull;   // 两个信号句柄

unsigned int __stdcall Producer(PVOID p) {
    while (1) {
        int data = rand() % 100 + 1;
        WaitForSingleObject(g_hEmpty, INFINITE);
        EnterCriticalSection(&g_cs);
        g_Buffer[g_in] = data;
        printf("生产者 放入 %d 到位置 %d\n", data, g_in);
        g_in = (g_in + 1) % N;
        LeaveCriticalSection(&g_cs);
        ReleaseSemaphore(g_hFull, 1, NULL);
        Sleep(500);
    }
    return 0;
}

unsigned int __stdcall Consumer(PVOID id) {
    int me = (int)id;
    while (1) {
        WaitForSingleObject(g_hFull, INFINITE);
        EnterCriticalSection(&g_cs);
        int data = g_Buffer[g_out];
        printf("消费者 %d 取出 %d 从位置 %d\n", me, data, g_out);
        g_out = (g_out + 1) % N;
        LeaveCriticalSection(&g_cs);
        ReleaseSemaphore(g_hEmpty, 1, NULL);
        Sleep(800);
    }
    return 0;
}

int main() {
    printf("多缓冲区：一个生产者，两个消费者\n");
    srand(time(NULL));
    InitializeCriticalSection(&g_cs);
    g_hEmpty = CreateSemaphore(NULL, N, N, NULL);
    g_hFull  = CreateSemaphore(NULL, 0, N, NULL);
    HANDLE hProd = (HANDLE)_beginthreadex(NULL, 0, Producer, NULL, 0, NULL);
    HANDLE hCons1 = (HANDLE)_beginthreadex(NULL, 0, Consumer, (void*)1, 0, NULL);
    HANDLE hCons2 = (HANDLE)_beginthreadex(NULL, 0, Consumer, (void*)2, 0, NULL);
    printf("运行中，按回车键退出...\n");
    getchar();
    CloseHandle(hProd);
    CloseHandle(hCons1);
    CloseHandle(hCons2);
    CloseHandle(g_hEmpty);
    CloseHandle(g_hFull);
    DeleteCriticalSection(&g_cs);
    return 0;
}