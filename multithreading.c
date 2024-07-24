#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to be executed by each thread
void* print_message(void* thread_id) {
    long tid = (long) thread_id;
    printf("Thread %ld is running\n", tid);
    pthread_exit(NULL);
}

int main() {
    int num_threads = 5;
    pthread_t threads[num_threads];
    int rc;
    long t;

    for (t = 0; t < num_threads; t++) {
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_message, (void*)t);

        if (rc) {
            printf("Error: unable to create thread, %d\n", rc);
            exit(-1);
        }
    }

    // Wait for all threads to complete
    for (t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("All threads completed\n");

    return 0;
}

