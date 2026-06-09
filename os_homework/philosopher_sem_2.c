#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define N 5

pthread_mutex_t chopstick[N];
/*
奇偶哲学家拿筷子顺序不同
偶数编号（0,2,4）的哲学家先拿右边筷子，再拿左边
奇数编号（1,3）的哲学家先拿左边筷子，再拿右边。
*/

void *philosopher(void *arg) {
    int i = *(int *)arg;
    while (1) {
        printf("%d 号哲学家在思考...\n", i);
        sleep(rand() % 3);

        if (i % 2 == 0) {          // 偶数哲学家：先右后左
            pthread_mutex_lock(&chopstick[(i + 1) % N]);
            pthread_mutex_lock(&chopstick[i]);
        } else {                   // 奇数哲学家：先左后右
            pthread_mutex_lock(&chopstick[i]);
            pthread_mutex_lock(&chopstick[(i + 1) % N]);
        }

        printf("%d 号哲学家在进餐...\n", i);
        sleep(rand() % 3);

        pthread_mutex_unlock(&chopstick[i]);
        pthread_mutex_unlock(&chopstick[(i + 1) % N]);
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

    for (i = 0; i < N; i++)
        pthread_join(id[i], NULL);

    for (i = 0; i < N; i++)
        pthread_mutex_destroy(&chopstick[i]);

    return 0;
}