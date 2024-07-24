#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 1000
#define NUM_BLOCKS 10

typedef struct {
    int size;
    int free;
} Block;

Block memory[NUM_BLOCKS];

void initialize_memory() {
	int i;
    for (i = 0; i < NUM_BLOCKS; i++) {
        memory[i].size = MEMORY_SIZE / NUM_BLOCKS;
        memory[i].free = 1;
    }
}

void print_memory() {
	int i;
    printf("Memory Blocks:\n");
    for (i = 0; i < NUM_BLOCKS; i++) {
        printf("Block %d: Size: %d, Free: %d\n", i, memory[i].size, memory[i].free);
    }
}

void allocate_first_fit(int size) {
	int i;
    for (i = 0; i < NUM_BLOCKS; i++) {
        if (memory[i].free && memory[i].size >= size) {
            memory[i].free = 0;
            printf("Allocated %d bytes in block %d using First-Fit.\n", size, i);
            return;
        }
    }
    printf("Failed to allocate %d bytes using First-Fit.\n", size);
}

void allocate_best_fit(int size) {
    int best_index = -1,i;
    for (i = 0; i < NUM_BLOCKS; i++) {
        if (memory[i].free && memory[i].size >= size) {
            if (best_index == -1 || memory[i].size < memory[best_index].size) {
                best_index = i;
            }
        }
    }
    if (best_index != -1) {
        memory[best_index].free = 0;
        printf("Allocated %d bytes in block %d using Best-Fit.\n", size, best_index);
    } else {
        printf("Failed to allocate %d bytes using Best-Fit.\n", size);
    }
}

void allocate_worst_fit(int size) {
    int worst_index = -1,i;
    for (i = 0; i < NUM_BLOCKS; i++) {
        if (memory[i].free && memory[i].size >= size) {
            if (worst_index == -1 || memory[i].size > memory[worst_index].size) {
                worst_index = i;
            }
        }
    }
    if (worst_index != -1) {
        memory[worst_index].free = 0;
        printf("Allocated %d bytes in block %d using Worst-Fit.\n", size, worst_index);
    } else {
        printf("Failed to allocate %d bytes using Worst-Fit.\n", size);
    }
}

int main() {
    initialize_memory();
    print_memory();

    allocate_first_fit(80);
    print_memory();

    allocate_best_fit(100);
    print_memory();

    allocate_worst_fit(50);
    print_memory();

    allocate_first_fit(200);
    print_memory();

    allocate_best_fit(150);
    print_memory();

    allocate_worst_fit(300);
    print_memory();

    return 0;
}

