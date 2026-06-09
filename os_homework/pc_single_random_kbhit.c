#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <process.h>
#include <windows.h>

CRITICAL_SECTION g_cs;
HANDLE g_hEventBufferEmpty, g_hEventBufferFull;
int g_Buffer;
volatile int g_ProducerDone = 0;

unsigned int __stdcall ProducerThreadFun(PVOID pM) {
    while (1) {
        if (_kbhit()) {
            _getch();
            g_ProducerDone = 1;
            break;
        }
        WaitForSingleObject(g_hEventBufferEmpty, INFINITE);
        EnterCriticalSection(&g_cs);
        g_Buffer = rand() % 100 + 1;
        printf("生产者将随机数 %d 放入缓冲区\n", g_Buffer);
        LeaveCriticalSection(&g_cs);
        SetEvent(g_hEventBufferFull);
        Sleep(500);
    }
    return 0;
}

unsigned int __stdcall ConsumerThreadFun(PVOID pM) {
    while (1) {
        WaitForSingleObject(g_hEventBufferFull, INFINITE);
        EnterCriticalSection(&g_cs);
        int data = g_Buffer;
        printf("消费者取出 %d\n", data);
        if (g_ProducerDone) {
            LeaveCriticalSection(&g_cs);
            SetEvent(g_hEventBufferEmpty);
            break;
        }
        LeaveCriticalSection(&g_cs);
        SetEvent(g_hEventBufferEmpty);
        Sleep(800);
    }
    return 0;
}

int main() {
    printf("按任意键停止生产...\n");
    srand(time(NULL));
    InitializeCriticalSection(&g_cs);
    g_hEventBufferEmpty = CreateEvent(NULL, FALSE, TRUE, NULL);
    g_hEventBufferFull = CreateEvent(NULL, FALSE, FALSE, NULL);
    HANDLE hProd = (HANDLE)_beginthreadex(NULL, 0, ProducerThreadFun, NULL, 0, NULL);
    HANDLE hCons = (HANDLE)_beginthreadex(NULL, 0, ConsumerThreadFun, NULL, 0, NULL);
    WaitForSingleObject(hProd, INFINITE);
    WaitForSingleObject(hCons, INFINITE);
    CloseHandle(hProd);
    CloseHandle(hCons);
    CloseHandle(g_hEventBufferEmpty);
    CloseHandle(g_hEventBufferFull);
    DeleteCriticalSection(&g_cs);
    return 0;
}