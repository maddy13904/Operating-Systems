#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100
#define RECORD_SIZE 256

typedef struct {
    char data[RECORD_SIZE];
} Record;

typedef struct {
    Record records[MAX_RECORDS];
    int record_count;
} File;

void createFile(File* file) {
    file->record_count = 0;
}

void addRecord(File* file, const char* data) {
    if (file->record_count >= MAX_RECORDS) {
        printf("File is full. Cannot add more records.\n");
        return;
    }
    strncpy(file->records[file->record_count].data, data, RECORD_SIZE);
    file->record_count++;
}

void readRecords(File* file) {
	int i;
    for (i = 0; i < file->record_count; i++) {
        printf("Record %d: %s\n", i + 1, file->records[i].data);
    }
}

void readSpecificRecord(File* file, int record_index) {
	int i;
    if (record_index < 0 || record_index >= file->record_count) {
        printf("Invalid record index.\n");
        return;
    }
    printf("Reading records up to record %d:\n", record_index + 1);
    for (i = 0; i <= record_index; i++) {
        printf("Record %d: %s\n", i + 1, file->records[i].data);
    }
}

int main() {
    File myFile;
    createFile(&myFile);

    addRecord(&myFile, "First record");
    addRecord(&myFile, "Second record");
    addRecord(&myFile, "Third record");

    printf("All records in the file:\n");
    readRecords(&myFile);

    int recordIndex;
    printf("\nEnter the index of the record you want to access (0-based index): ");
    scanf("%d", &recordIndex);

    readSpecificRecord(&myFile, recordIndex);

    return 0;
}

