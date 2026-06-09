#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define N 5

pthread_mutex_t chopstick[N];


/*
这段代码会导致死锁的原因是循环等待：每个哲学家先拿左边的筷子，
再拿右边的筷子。当所有哲学家同时拿起左边的筷子后，
每个人都在等待右边的筷子，而右边的筷子正被下一个哲学家拿着，
形成环路，导致永远无法继续执行
*/

void *philosopher(void *arg) {
    int i = *(int *)arg;
    while (1) {
        // 思考
        printf("%d 号哲学家正在思考...\n", i);
        sleep(rand() % 3 + 1);   // 随机思考 1~3 秒

        // 拿起左边筷子
        printf("%d 号哲学家拿起了左边筷子 %d\n", i, i);
        pthread_mutex_lock(&chopstick[i]);

        // 故意延迟，增加所有哲学家同时拿起左边筷子的概率
        sleep(rand() % 2);       // 延迟 0 或 1 秒

        // 拿起右边筷子
        printf("%d 号哲学家试图拿右边筷子 %d\n", i, (i+1)%N);
        pthread_mutex_lock(&chopstick[(i+1)%N]);

        // 吃饭
        printf("%d 号哲学家正在进餐...\n", i);
        sleep(rand() % 3 + 1);   // 吃饭 1~3 秒

        // 放下筷子
        pthread_mutex_unlock(&chopstick[i]);
        pthread_mutex_unlock(&chopstick[(i+1)%N]);
    }
    return NULL;
}

int main() {
    pthread_t id[N];
    int i, *p;

    srand(time(NULL));

    for (i = 0; i < N; i++)
        pthread_mutex_init(&chopstick[i], NULL);

    for (i = 0; i < N; i++) {
        p = malloc(sizeof(int));
        *p = i;
        pthread_create(&id[i], NULL, philosopher, p);
    }

    // 主线程等待所有哲学家线程（永远不会主动退出，按 Ctrl+C 终止）
    for (i = 0; i < N; i++)
        pthread_join(id[i], NULL);

    for (i = 0; i < N; i++)
        pthread_mutex_destroy(&chopstick[i]);

    return 0;
}