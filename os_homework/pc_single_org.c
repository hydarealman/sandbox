#include <stdio.h>
#include <process.h>
#include <windows.h>

const int END_PRODUCE_NUMBER = 20;
int g_Buffer;
CRITICAL_SECTION g_cs;
HANDLE g_hEventBufferEmpty, g_hEventBufferFull;

unsigned int __stdcall ProducerThreadFun(PVOID pM) {
    int i;
    for (i = 1; i <= END_PRODUCE_NUMBER; i++) {
        WaitForSingleObject(g_hEventBufferEmpty, INFINITE);
        EnterCriticalSection(&g_cs);
        g_Buffer = i;
        printf("生产者将数据%d放入缓冲区\n", i);
        LeaveCriticalSection(&g_cs);
        SetEvent(g_hEventBufferFull);
        Sleep(1000);
    }
    return 0;
}

unsigned int __stdcall ConsumerThreadFun(PVOID pM) {
    int flag = 1;
    while (flag) {
        WaitForSingleObject(g_hEventBufferFull, INFINITE);
        EnterCriticalSection(&g_cs);
        printf("消费者从缓冲区中取出数据%d\n", g_Buffer);
        if (g_Buffer == END_PRODUCE_NUMBER)
            flag = 0;
        LeaveCriticalSection(&g_cs);
        SetEvent(g_hEventBufferEmpty);
        Sleep(1000);
    }
    return 0;
}

int main() {
    printf("生产者消费者问题\n");
    InitializeCriticalSection(&g_cs);
    g_hEventBufferEmpty = CreateEvent(NULL, FALSE, TRUE, NULL);
    g_hEventBufferFull = CreateEvent(NULL, FALSE, FALSE, NULL);
    HANDLE hThread[2];
    hThread[0] = (HANDLE)_beginthreadex(NULL, 0, ProducerThreadFun, NULL, 0, NULL);
    hThread[1] = (HANDLE)_beginthreadex(NULL, 0, ConsumerThreadFun, NULL, 0, NULL);
    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
    CloseHandle(hThread[0]);
    CloseHandle(hThread[1]);
    CloseHandle(g_hEventBufferEmpty);
    CloseHandle(g_hEventBufferFull);
    DeleteCriticalSection(&g_cs);
    return 0;
}