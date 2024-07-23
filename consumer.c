#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024  // Size of the shared memory

int main() {
    key_t key = ftok("shmfile", 65); // Generate a unique key
    int shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT); // Locate the shared memory segment

    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    char *data = (char*) shmat(shmid, NULL, 0); // Attach the shared memory segment to the process's address space

    if (data == (char *)(-1)) {
        perror("shmat failed");
        exit(1);
    }

    printf("Data read from shared memory: %s\n", data); // Read data from the shared memory

    shmdt(data); // Detach the shared memory segment
    shmctl(shmid, IPC_RMID, NULL); // Destroy the shared memory segment

    return 0;
}

