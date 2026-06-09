#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define N 5

/*
gcc philosopher_sem.c -o philosopher_sem -lpthread
*/

pthread_mutex_t chopstick[N];
sem_t room;    // 最多允许 N-1 个哲学家同时进餐

/*
限制同时就餐的哲学家最多为N-1
*/

void *philosopher(void *arg) {
    int i = *(int *)arg;
    while (1) {
        // 思考
        printf("%d 号哲学家在思考...\n", i);
        sleep(rand() % 3);

        sem_wait(&room);   // 申请进入餐厅（名额减1）

        // 拿起两根筷子
        pthread_mutex_lock(&chopstick[i]);
        pthread_mutex_lock(&chopstick[(i + 1) % N]);

        // 吃饭
        printf("%d 号哲学家在进餐...\n", i);
        sleep(rand() % 3);

        // 放下筷子
        pthread_mutex_unlock(&chopstick[i]);
        pthread_mutex_unlock(&chopstick[(i + 1) % N]);

        sem_post(&room);   // 离开餐厅（名额加1）
    }
    return NULL;
}

int main() {
    pthread_t id[N];
    int i, *p;

    srand(time(NULL));
    sem_init(&room, 0, N - 1);   // 初始 N-1 个名额

    for (i = 0; i < N; i++)
        pthread_mutex_init(&chopstick[i], NULL);

    for (i = 0; i < N; i++) {
        p = malloc(sizeof(int));
        *p = i;
        pthread_create(&id[i], NULL, philosopher, p);
    }

    for (i = 0; i < N; i++)
        pthread_join(id[i], NULL);   // 程序不会主动退出，按 Ctrl+C 停止

    sem_destroy(&room);
    for (i = 0; i < N; i++)
        pthread_mutex_destroy(&chopstick[i]);

    return 0;
}