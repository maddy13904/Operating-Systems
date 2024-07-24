#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10
#define NUM_INCREMENTS 1000

int counter = 0;
pthread_mutex_t mutex;

void* incrementCounter(void* arg) {
	int i;
    for (i = 0; i < NUM_INCREMENTS; i++) {
        pthread_mutex_lock(&mutex);  // Lock the mutex
        counter++;
        pthread_mutex_unlock(&mutex);  // Unlock the mutex
    }
    return NULL;
}

int main() {
	int i;
    pthread_t threads[NUM_THREADS];

    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex initialization failed");
        return EXIT_FAILURE;
    }

    // Create threads
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, incrementCounter, NULL) != 0) {
            perror("Thread creation failed");
            return EXIT_FAILURE;
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Thread join failed");
            return EXIT_FAILURE;
        }
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Print the final counter value
    printf("Final counter value: %d\n", counter);

    return EXIT_SUCCESS;
}

