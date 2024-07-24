#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100;  // Produce a random item
        sem_wait(&empty);  // Wait for an empty slot
        pthread_mutex_lock(&mutex);  // Lock the buffer

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&full);  // Signal that there is a new item

        sleep(1);  // Simulate time taken to produce an item
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);  // Wait for a full slot
        pthread_mutex_lock(&mutex);  // Lock the buffer

        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&empty);  // Signal that there is an empty slot

        sleep(1);  // Simulate time taken to consume an item
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize the semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create the producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for the threads to finish (they won't in this example)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

