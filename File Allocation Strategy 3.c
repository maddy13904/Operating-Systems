#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 256
#define MAX_BLOCKS 100

typedef struct Block {
    char data[BLOCK_SIZE];
    int next;
} Block;

typedef struct File {
    int start;
    int end;
} File;

typedef struct FileSystem {
    Block blocks[MAX_BLOCKS];
    int free_list[MAX_BLOCKS];
    int free_count;
} FileSystem;

void initFileSystem(FileSystem* fs) {
	int i;
    for (i = 0; i < MAX_BLOCKS; i++) {
        fs->free_list[i] = i;
    }
    fs->free_count = MAX_BLOCKS;
}

int allocateBlock(FileSystem* fs) {
    if (fs->free_count == 0) {
        printf("File system is full. Cannot allocate more blocks.\n");
        return -1;
    }
    int block_num = fs->free_list[--fs->free_count];
    fs->blocks[block_num].next = -1;
    return block_num;
}

void createFile(FileSystem* fs, File* file, const char* data[], int data_count) {
	int i;
    if (data_count == 0) return;

    file->start = allocateBlock(fs);
    if (file->start == -1) return;

    int current = file->start;
    strncpy(fs->blocks[current].data, data[0], BLOCK_SIZE);

    for (i = 1; i < data_count; i++) {
        int next = allocateBlock(fs);
        if (next == -1) return;

        fs->blocks[current].next = next;
        current = next;
        strncpy(fs->blocks[current].data, data[i], BLOCK_SIZE);
    }
    file->end = current;
}

void readFile(FileSystem* fs, File* file) {
    int current = file->start;
    int block_num = 1;

    while (current != -1) {
        printf("Block %d: %s\n", block_num++, fs->blocks[current].data);
        current = fs->blocks[current].next;
    }
}

int main() {
    FileSystem myFileSystem;
    initFileSystem(&myFileSystem);

    File myFile;
    const char* fileData[] = {
        "Block 1 data",
        "Block 2 data",
        "Block 3 data"
    };
    int data_count = sizeof(fileData) / sizeof(fileData[0]);

    createFile(&myFileSystem, &myFile, fileData, data_count);

    printf("Reading file blocks:\n");
    readFile(&myFileSystem, &myFile);

    return 0;
}

