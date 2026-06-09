#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

/*
gcc prod_cons.c -o prod_cons -lpthread
*/

#define N 4          // 生产者/消费者线程数
#define M 20         // 缓冲区大小

int in = 0, out = 0;
char buff[M];
int producter_id = 0, consumer_id = 0;

// 同步互斥变量
sem_t empty_sem;      // 空位计数
sem_t full_sem;       // 产品计数
pthread_mutex_t mutex;

void print() {
    int i;
    for (i = 0; i < M; i++)
        printf("%c ", buff[i]);
    printf("\n");
}

void *producter(void *arg) {
    int id = ++producter_id;
    while (1) {
        sleep(2);          // 可改为 1, 3 或 rand()%3+1
        char data = rand() % 26 + 'A';

        sem_wait(&empty_sem);

        pthread_mutex_lock(&mutex);
        in = in % M;
        printf("生产者%d 在%2d 位置放 %c: ", id, in, data);
        buff[in] = data;
        print();
        in++;
        pthread_mutex_unlock(&mutex);

        sem_post(&full_sem);
    }
    return NULL;
}

void *consumer(void *arg) {
    int id = ++consumer_id;
    while (1) {
        sleep(1);          // 可改为 2, 3 或 rand()%3+1

        sem_wait(&full_sem);

        pthread_mutex_lock(&mutex);
        out = out % M;
        char data = buff[out];
        printf("消费者%d 在%2d 位置取 %c: ", id, out, data);
        buff[out] = '*';
        print();
        out++;
        pthread_mutex_unlock(&mutex);

        sem_post(&empty_sem);
    }
    return NULL;
}

int main() {
    pthread_t p[N], c[N];
    int i;

    for (i = 0; i < M; i++) buff[i] = '*';
    srand(time(NULL));

    sem_init(&empty_sem, 0, M); // 当前有多少个空闲位置可以放产品
    sem_init(&full_sem, 0, 0);  // 当前缓冲区中有多少个产品可供消费
    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < N; i++) {
        pthread_create(&p[i], NULL, producter, NULL);
        pthread_create(&c[i], NULL, consumer, NULL);
    }

    // 主线程等待所有生产者和消费者线程结束
    for (i = 0; i < N; i++) {
        pthread_join(p[i], NULL);
        pthread_join(c[i], NULL);
    }

    sem_destroy(&empty_sem);
    sem_destroy(&full_sem);
    pthread_mutex_destroy(&mutex);
    return 0;
}