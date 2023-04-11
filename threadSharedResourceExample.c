#include <stdio.h>
#include <pthread.h>

#define THREADS_COUNT 2

int shared_var = 0;
pthread_mutex_t lock;

void* increment_thread(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock);
        shared_var++;
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[THREADS_COUNT];
    pthread_mutex_init(&lock, NULL);
    
    for (int i = 0; i < THREADS_COUNT; i++) {
        pthread_create(&threads[i], NULL, increment_thread, NULL);
    }
    
    for (int i = 0; i < THREADS_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Paylaþýlan deðiþken deðeri: %d\n", shared_var);
    
    pthread_mutex_destroy(&lock);
    
    return 0;
}

