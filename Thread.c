#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Thread function
void* threadFunction(void* arg) {
    int thread_num = *(int*)arg;
    printf("Thread %d started.\n", thread_num);
    sleep(2);  // Simulate some work
    printf("Thread %d exiting.\n", thread_num);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int thread_num1 = 1;
    int thread_num2 = 2;
    int ret;

    // Create threads
    ret = pthread_create(&thread1, NULL, threadFunction, &thread_num1);
    if (ret != 0) {
        fprintf(stderr, "Error creating thread 1: %s\n", strerror(ret));
        exit(EXIT_FAILURE);
    }
    
    ret = pthread_create(&thread2, NULL, threadFunction, &thread_num2);
    if (ret != 0) {
        fprintf(stderr, "Error creating thread 2: %s\n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    // Join threads
    ret = pthread_join(thread1, NULL);
    if (ret != 0) {
        fprintf(stderr, "Error joining thread 1: %s\n", strerror(ret));
        exit(EXIT_FAILURE);
    }
    
    ret = pthread_join(thread2, NULL);
    if (ret != 0) {
        fprintf(stderr, "Error joining thread 2: %s\n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    // Check if threads are equal (this is not directly possible with pthreads, but we can demonstrate with IDs)
    if (pthread_equal(thread1, thread2)) {
        printf("Thread 1 and Thread 2 are the same.\n");
    } else {
        printf("Thread 1 and Thread 2 are different.\n");
    }

    printf("Main thread exiting.\n");
    return 0;
}

