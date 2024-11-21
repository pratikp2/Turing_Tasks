
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int shared_counter = 0;

void* increment_counter(void *arg) {
    int i;
    for (i = 0; i < 10000; i++) {
        shared_counter++;
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value of shared_counter: %d\n", shared_counter);

    return 0;
}
