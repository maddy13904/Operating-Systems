#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];
pthread_mutex_t lock;

void think(int philosopher) {
    printf("Philosopher %d is thinking.\n", philosopher);
    sleep(rand() % 3); // Simulate thinking
}

void eat(int philosopher) {
    printf("Philosopher %d is eating.\n", philosopher);
    sleep(rand() % 3); // Simulate eating
}

void* philosopher_actions(void* num) {
    int philosopher = *((int*)num);
    free(num);

    while (1) {
        think(philosopher);

        // Pick up forks (left and right)
        pthread_mutex_lock(&lock);  // Lock the critical section
        pthread_mutex_lock(&forks[philosopher]);
        pthread_mutex_lock(&forks[(philosopher + 1) % NUM_PHILOSOPHERS]);
        pthread_mutex_unlock(&lock);  // Unlock the critical section

        eat(philosopher);

        // Put down forks (left and right)
        pthread_mutex_unlock(&forks[philosopher]);
        pthread_mutex_unlock(&forks[(philosopher + 1) % NUM_PHILOSOPHERS]);
    }

    pthread_exit(NULL);
}

int main() {
    int i;
    pthread_mutex_init(&lock, NULL);

    // Initialize the mutexes for forks
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        int* philosopher_id = malloc(sizeof(int));
        *philosopher_id = i;
        pthread_create(&philosophers[i], NULL, philosopher_actions, philosopher_id);
    }

    // Wait for all philosopher threads to finish
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy the mutexes
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}

