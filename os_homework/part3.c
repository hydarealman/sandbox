#include "stdio.h" 
#include <stdlib.h> 
#define getpch(type) (type*)malloc(sizeof(type)) 

/*进程控制块PCB*/
struct pcb { 
  char name[10];    // 进程名
  char state;       // 进程状态: W - 就绪态 R 运行态
  int nice;         // 优先级(数值越大优先级越高)
  int ntime;        // 需要运行的总时间
  int rtime;        // 已经运行的时间
  struct pcb* link; // 指向下一个PCB(后一个就绪进程)
}*ready=NULL,*p; 
typedef struct pcb PCB; 

/*将当前进程 p 按优先级插入就绪队列(降序,优先级高的在前面)*/
void sort() 
{ 
  PCB *first, *second; 
  int insert=0; 
  if((ready==NULL)||((p->nice)>(ready->nice)))/*优先级比队首高,插到队首*/
  { 
    p->link=ready; 
    ready=p; 
  } 
  else /* 找到合适位置插入*/ 
  { 
    first=ready; 
    second=first->link; 
    while(second!=NULL) 
    { 
      if((p->nice)>(second->nice)) /*比当前节点优先级高,插入到前面*/ 
      { 
        p->link=second; 
        first->link=p; 
        second=NULL; 
        insert=1; 
      } 
      else /* 继续往后找*/ 
      { 
        first=first->link; 
        second=second->link; 
      } 
    } 
    if(insert==0) first->link=p; /*插到队尾*/
  } 
} 

/*输入进程信息,创建多个进程并加入就绪队列*/
void input()  
{ 
  int i,num; 
  printf("\n 请输入被调度的进程数目"); 
  scanf("%d",&num); 
  for(i=0;i<num;i++) 
  { 
    printf("\n 进程号No.%d:",i); 
    p=getpch(PCB); 
    printf("\n 请输入进程名:"); 
    scanf("%s",p->name); 
    printf(" 请输入进程优先级:"); 
    scanf("%d",&p->nice); 
    printf(" 请输入进程需要运行的时间:"); 
    scanf("%d",&p->ntime); 
    printf("\n"); 
    p->rtime=0;
    p->state='W'; 
    p->link=NULL; 
    sort(); /* 按优先级插入就绪队列*/ 
  } 
} 

/*统计就绪列队的进程个数*/
int space() 
{ 
  int l=0; PCB* pr=ready; 
  while(pr!=NULL) 
  { 
    l++; 
    pr=pr->link; 
  } 
  return(l); 
} 

/*显示单个进程的信息*/
void disp(PCB * pr) 
{ 
  printf("\n 进程名 状态 优先级 需要运行时间 已经运行时间 \n"); 
  printf(" %s\t",pr->name); 
  printf("%3c\t",pr->state); 
  printf("%3d\t",pr->nice); 
  printf("%d\t\t",pr->ntime); 
  printf("%d\t",pr->rtime); 
  printf("\n"); 
}

/*查看当前运行进程和就绪队列中的进程*/
void check()  
{ 
  PCB* pr; 
  printf("\n **** 当前正在运行的进程是 :%s",p->name); /* 显示当前运行进程 */
  disp(p); 
  pr=ready; 
  if (pr!=NULL) 
    printf("\n **** 当前就绪队列状态为 :"); 
  else 
    printf("\n **** 当前就绪队列状态为: 空\n"); 
  while(pr!=NULL) 
  { 
    disp(pr); 
    pr=pr->link; 
  } 
} 

/*进程结束,释放其PCB*/
void destroy()  
{ 
  printf(" 进程 [%s] 已完成.\n",p->name); 
  free(p); 
}
 
/*运行当前进程一个时间片*/
void running()
{ 
  (p->rtime)++;             // 已运行时间加1
  if(p->rtime==p->ntime)    // 如果总时间已用完,则销毁进程
    destroy();                
  else                      // 否则降低优先级,重新插入就绪队列
  { 
    (p->nice)--;            // 优先级减 1
    p->state='W'; 
    sort();                 // 重新插入就绪队列(按新优先级排序)
  } 
} 

/*主函数: 调度循环*/
int main() 
{ 
  int len,h=0; 
  char ch; 
  input();                          // 输入所有进程
  len=space();                      // 初始就绪队列长度
  while((len!=0)&&(ready!=NULL)) 
  { 
    ch=getchar();                   // 吸收回车
    h++; 
    printf("\n The execute number:%d \n",h); // 调度次数
    p=ready;                                 // 取出队首进程运行
    ready=p->link; 
    p->link=NULL; 
    p->state='R';                            // 变为运行态
    check();                                 // 显示当前运行进程和就绪队列
    running();                               // 运行一个时间片(可能降低优先级并重排队列)
    printf("\n 按任意键继续......"); 
   // ch=getchar(); 
  } 
  printf("\n\n 所有进程已经全部完成! \n"); 
  ch=getchar(); 
  return 0;
}

