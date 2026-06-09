#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

// 遍历并显示系统中所有运行的进程信息
int main() {
    // 创建一个系统快照
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    // 如果快照创建失败,打印错误并退出
    if (hSnap == INVALID_HANDLE_VALUE) {
        printf("快照失败\n");
        return 1;
    }
    
    
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(pe);
    
    if (Process32First(hSnap, &pe)) {
        printf("进程名\t\t\tPID\t线程数\t父PID\n");
        do {
            printf("%-30s %-6d %-6d %-6d\n", pe.szExeFile, pe.th32ProcessID,
                   pe.cntThreads, pe.th32ParentProcessID);
        } while (Process32Next(hSnap, &pe)); // 从进程快照句柄hSnap中获取下一个进程的信息,并将信息填充到pe结构体中
    }
    
    // 关闭快照句柄,释放资源
    CloseHandle(hSnap);
    system("pause");
    return 0;
}