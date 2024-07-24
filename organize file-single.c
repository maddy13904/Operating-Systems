#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define FILENAME_LENGTH 100

typedef struct {
    char name[FILENAME_LENGTH];
    int inUse;
} File;

File directory[MAX_FILES];

void initializeDirectory() {
	int i;
    for (i = 0; i < MAX_FILES; i++) {
        directory[i].inUse = 0;
    }
}

void createFile(const char* filename) {
	int i;
    for (i = 0; i < MAX_FILES; i++) {
        if (!directory[i].inUse) {
            strncpy(directory[i].name, filename, FILENAME_LENGTH);
            directory[i].inUse = 1;
            printf("File '%s' created successfully.\n", filename);
            return;
        }
    }
    printf("Error: Directory is full.\n");
}

void listFiles() {
	int i;
    printf("Files in the directory:\n");
    for (i = 0; i < MAX_FILES; i++) {
        if (directory[i].inUse) {
            printf("%s\n", directory[i].name);
        }
    }
}

void deleteFile(const char* filename) {
	int i;
    for (i = 0; i < MAX_FILES; i++) {
        if (directory[i].inUse && strcmp(directory[i].name, filename) == 0) {
            directory[i].inUse = 0;
            printf("File '%s' deleted successfully.\n", filename);
            return;
        }
    }
    printf("Error: File '%s' not found.\n", filename);
}

int main() {
    char command[FILENAME_LENGTH];
    char filename[FILENAME_LENGTH];

    initializeDirectory();

    while (1) {
        printf("\nEnter command (create, list, delete, exit): ");
        scanf("%s", command);

        if (strcmp(command, "create") == 0) {
            printf("Enter filename: ");
            scanf("%s", filename);
            createFile(filename);
        } else if (strcmp(command, "list") == 0) {
            listFiles();
        } else if (strcmp(command, "delete") == 0) {
            printf("Enter filename: ");
            scanf("%s", filename);
            deleteFile(filename);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Invalid command. Please try again.\n");
        }
    }

    return 0;
}

