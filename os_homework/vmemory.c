#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define TRUE 1
#define FALSE 0
#define INVALID -1
#define total_instruction 640
#define total_vp 64
#define clear_period 50

// 页表结构
typedef struct {
    int pn;       // 页号
    int pfn;      // 内存页框号
    int counter;  // 一段时间内访问该页的次数
    int time;     // 最近访问时间
} page_type;

page_type p1[total_vp];

// 页框控制结构
typedef struct pfc_struct {
    int pn;                     // 页号
    int pfn;                    // 页框号
    struct pfc_struct *next;
} pfc_type;

pfc_type pfc[total_vp];         // 用户内存页框控制结构
pfc_type *freepf_head;          // 空闲页框头指针
pfc_type *busypf_head;          // 忙页框头指针
pfc_type *busypf_tail;          // 忙页框尾指针

int diseffect;                  // 缺页次数
int a[total_instruction];       // 指令序列（逻辑地址）
int page[total_instruction];    // 页号序列
int offset[total_instruction];  // 页内偏移

// 函数声明（带参数）
void initialize(int total_pf);
void FIFO(int total_pf);
void LRU(int total_pf);
void OPT(int total_pf);

int main()
{
    int s, i, j;

    srand((unsigned int)time(NULL));
    s = rand() % 160;

    // 生成 320 条指令的序列（符合 50%顺序、25%前部、25%后部）
    for (i = 0; i < total_instruction; i += 4)
    {
        a[i] = s;
        a[i + 1] = a[i] + 1;
        a[i + 2] = 160 + rand() % 160;
        a[i + 3] = a[i + 2] + 1;
        s = rand() % 160;
    }

    // 将指令序列转换为页号和偏移（每页 10 条指令）
    for (i = 0; i < total_instruction; i++)
    {
        page[i] = a[i] / 10;
        offset[i] = a[i] % 10;
    }

    // 测试不同内存容量：4 页到 32 页
    for (i = 4; i <= 32; i++)
    {
        printf("%2d page frames", i);
        FIFO(i);
        LRU(i);
        OPT(i);
        printf("\n");
    }

    return 0;
}

// 初始化：重置页表、空闲页框链表，缺页次数清零
void initialize(int total_pf)
{
    int i;
    diseffect = 0;

    // 初始化页表
    for (i = 0; i < total_vp; i++)
    {
        p1[i].pn = i;
        p1[i].pfn = INVALID;
        p1[i].counter = 0;
        p1[i].time = -1;
    }

    // 初始化空闲页框链表（页框号 0 ~ total_pf-1）
    for (i = 0; i < total_pf - 1; i++)
    {
        pfc[i].next = &pfc[i + 1];
        pfc[i].pfn = i;
    }
    pfc[total_pf - 1].next = NULL;
    pfc[total_pf - 1].pfn = total_pf - 1;
    freepf_head = &pfc[0];
}

// 先进先出页面置换算法
void FIFO(int total_pf)
{
    initialize(total_pf);               // 重置状态（缺页次数清零）

    // 模拟内存中的页面（数组下标为页框号，值为存放的页号）
    int *mem_pages = (int *)malloc(total_pf * sizeof(int));
    for (int i = 0; i < total_pf; i++)
        mem_pages[i] = -1;

    int pointer = 0;          // FIFO 指针（下一个要替换的页框）
    int allocated = 0;        // 当前已分配的页框数

    for (int i = 0; i < total_instruction; i++)
    {
        int pg = page[i];     // 当前需要访问的页面号

        if (p1[pg].pfn == INVALID)   // 缺页
        {
            diseffect++;

            if (allocated < total_pf)   // 内存尚未占满
            {
                int pfn = allocated;          // 新页框号
                p1[pg].pfn = pfn;
                mem_pages[pfn] = pg;
                allocated++;
            }
            else   // 内存已满，需要淘汰
            {
                int out_pfn = pointer;
                int out_page = mem_pages[out_pfn];

                // 淘汰旧页面
                p1[out_page].pfn = INVALID;

                // 装入新页面
                p1[pg].pfn = out_pfn;
                mem_pages[out_pfn] = pg;

                // FIFO 指针后移
                pointer = (pointer + 1) % total_pf;
            }
        }
        // 命中：什么都不做
    }

    free(mem_pages);
    printf(" FIFO:%6.4f ", 1 - (float)diseffect / total_instruction);
}

// 最近最少使用算法（LRU）
void LRU(int total_pf)
{
    int min, minj, i, j, present_time;
    initialize(total_pf);
    present_time = 0;

    for (i = 0; i < total_instruction; i++)
    {
        if (p1[page[i]].pfn == INVALID)   // 缺页
        {
            diseffect++;

            if (freepf_head == NULL)      // 无空闲页框
            {
                min = 32767;
                for (j = 0; j < total_vp; j++)
                {
                    if (min > p1[j].time && p1[j].pfn != INVALID)
                    {
                        min = p1[j].time;
                        minj = j;
                    }
                }
                freepf_head = &pfc[p1[minj].pfn];  // 移出一个页框
                p1[minj].pfn = INVALID;
                freepf_head->next = NULL;
            }
            // 有空闲页框或已淘汰出空闲页框
            p1[page[i]].pfn = freepf_head->pfn;
            p1[page[i]].time = present_time;
            freepf_head = freepf_head->next;
        }
        else
        {
            p1[page[i]].time = present_time;   // 命中，更新访问时间
        }
        present_time++;
    }
    printf("LRU:%6.4f ", 1 - (float)diseffect / total_instruction);
}

// 最优置换算法（OPT）
void OPT(int total_pf)
{
    int i, j, max, maxpage, d, dist[total_vp];
    pfc_type *t;
    initialize(total_pf);

    for (i = 0; i < total_instruction; i++)
    {
        if (p1[page[i]].pfn == INVALID)   // 缺页
        {
            diseffect++;

            if (freepf_head == NULL)      // 无空闲页框，需要选择未来最远使用的页面淘汰
            {
                // 计算每个页面的下一次访问距离（初始为一个大数）
                for (j = 0; j < total_vp; j++)
                {
                    if (p1[j].pfn != INVALID)
                        dist[j] = 32767;
                    else
                        dist[j] = 0;
                }
                d = 1;
                for (j = i + 1; j < total_instruction; j++)
                {
                    if (p1[page[j]].pfn != INVALID && dist[page[j]] == 32767)
                        dist[page[j]] = d;
                    d++;
                }
                max = 1;
                for (j = 0; j < total_vp; j++)
                {
                    if (max < dist[j])
                    {
                        max = dist[j];
                        maxpage = j;
                    }
                }
                freepf_head = &pfc[p1[maxpage].pfn];
                freepf_head->next = NULL;
                p1[maxpage].pfn = INVALID;
            }
            // 有空闲页框或已淘汰
            p1[page[i]].pfn = freepf_head->pfn;
            freepf_head = freepf_head->next;
        }
    }
    printf("OPT:%6.4f ", 1 - (float)diseffect / total_instruction);
}