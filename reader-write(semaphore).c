#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t mutex;
sem_t wrt;
int read_count = 0;
int shared_data = 0;

void* reader(void* arg) {
    int reader_id = *((int*)arg);
    free(arg);
    while (1) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        // Reading section
        printf("Reader %d: read shared_data = %d\n", reader_id, shared_data);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);

        sleep(rand() % 3);  // Simulate reading time
    }
    return NULL;
}

void* writer(void* arg) {
    int writer_id = *((int*)arg);
    free(arg);
    while (1) {
        sem_wait(&wrt);

        // Writing section
        shared_data++;
        printf("Writer %d: wrote shared_data = %d\n", writer_id, shared_data);

        sem_post(&wrt);

        sleep(rand() % 3);  // Simulate writing time
    }
    return NULL;
}

int main() {
	int i;
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (i = 0; i < NUM_READERS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&readers[i], NULL, reader, id);
    }

    for (i = 0; i < NUM_WRITERS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&writers[i], NULL, writer, id);
    }

    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}

