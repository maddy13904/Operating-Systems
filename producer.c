#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024  // Size of the shared memory

int main() {
    key_t key = ftok("shmfile", 65); // Generate a unique key
    int shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT); // Create a shared memory segment

    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    char *data = (char*) shmat(shmid, NULL, 0); // Attach the shared memory segment to the process's address space

    if (data == (char *)(-1)) {
        perror("shmat failed");
        exit(1);
    }

    printf("Write Data: ");
    fgets(data, SHM_SIZE, stdin); // Write data to the shared memory

    shmdt(data); // Detach the shared memory segment

    return 0;
}
