#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int counter = 0;

sem_t mutex;
sem_t full;
sem_t empty;

void *producer(void *arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[counter++] = i;
        printf("Produced: %d\n", i);
        sem_post(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        int item = buffer[--counter];
        printf("Consumed: %d\n", item);
        sem_post(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    return 0;
}
