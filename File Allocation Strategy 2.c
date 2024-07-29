#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 100
#define BLOCK_SIZE 256
#define INDEX_BLOCK_SIZE 10  // Number of blocks the index block can point to

typedef struct {
    char data[BLOCK_SIZE];
} Block;

typedef struct {
    Block blocks[MAX_BLOCKS];
    int block_count;
    int index_block[INDEX_BLOCK_SIZE];
} FileSystem;

void createFileSystem(FileSystem* fs) {
	int i;
    fs->block_count = 0;
    for (i = 0; i < INDEX_BLOCK_SIZE; i++) {
        fs->index_block[i] = -1;  // Initialize index block entries to -1 (indicating empty)
    }
}

int allocateBlock(FileSystem* fs, const char* data) {
    if (fs->block_count >= MAX_BLOCKS) {
        printf("File system is full. Cannot allocate more blocks.\n");
        return -1;
    }
    strncpy(fs->blocks[fs->block_count].data, data, BLOCK_SIZE);
    return fs->block_count++;
}

void addBlockToIndex(FileSystem* fs, int block_number) {
	int i;
    for (i = 0; i < INDEX_BLOCK_SIZE; i++) {
        if (fs->index_block[i] == -1) {
            fs->index_block[i] = block_number;
            return;
        }
    }
    printf("Index block is full. Cannot add more blocks.\n");
}

void createFile(FileSystem* fs, const char* data[], int data_count) {
	int i;
    for (i = 0; i < data_count; i++) {
        int block_number = allocateBlock(fs, data[i]);
        if (block_number != -1) {
            addBlockToIndex(fs, block_number);
        }
    }
}

void readFile(FileSystem* fs) {
	int i;
    printf("Reading file blocks:\n");
    for (i = 0; i < INDEX_BLOCK_SIZE; i++) {
        if (fs->index_block[i] != -1) {
            int block_number = fs->index_block[i];
            printf("Block %d: %s\n", block_number, fs->blocks[block_number].data);
        }
    }
}

int main() {
    FileSystem myFileSystem;
    createFileSystem(&myFileSystem);

    const char* fileData[] = {
        "Block 1 data",
        "Block 2 data",
        "Block 3 data"
    };
    int data_count = sizeof(fileData) / sizeof(fileData[0]);

    createFile(&myFileSystem, fileData, data_count);

    readFile(&myFileSystem);

    return 0;
}

