#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Shared resources
pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t print_mutex;

// Function to simulate a philosopher's activity
void* philosopher(void* num) {
    int phil = *(int*)num;
    int left = phil;
    int right = (phil + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Thinking
        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d is thinking.\n", phil);
        pthread_mutex_unlock(&print_mutex);
        sleep(rand() % 3);

        // Picking up forks
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        // Eating
        pthread_mutex_lock(&print_mutex);
        printf("Philosopher %d is eating.\n", phil);
        pthread_mutex_unlock(&print_mutex);
        sleep(rand() % 3);

        // Putting down forks
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
    }
}

int main() {
	int i;
    pthread_t threads[NUM_PHILOSOPHERS];
    int phil_numbers[NUM_PHILOSOPHERS];

    // Initialize mutexes
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    pthread_mutex_init(&print_mutex, NULL);

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        phil_numbers[i] = i;
        if (pthread_create(&threads[i], NULL, philosopher, &phil_numbers[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Join philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutexes
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&print_mutex);

    return 0;
}

