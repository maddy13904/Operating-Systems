#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FILES 10
#define USERNAME_LENGTH 100
#define FILENAME_LENGTH 100

typedef struct {
    char name[FILENAME_LENGTH];
    int inUse;
} File;

typedef struct {
    char name[USERNAME_LENGTH];
    File files[MAX_FILES];
    int inUse;
} UserDirectory;

UserDirectory userDirectories[MAX_USERS];

void initializeDirectories() {
	int i,j;
    for (i = 0; i < MAX_USERS; i++) {
        userDirectories[i].inUse = 0;
        for (j = 0; j < MAX_FILES; j++) {
            userDirectories[i].files[j].inUse = 0;
        }
    }
}

void createUserDirectory(const char* username) {
	int i;
    for (i = 0; i < MAX_USERS; i++) {
        if (!userDirectories[i].inUse) {
            strncpy(userDirectories[i].name, username, USERNAME_LENGTH);
            userDirectories[i].inUse = 1;
            printf("User directory '%s' created successfully.\n", username);
            return;
        }
    }
    printf("Error: Maximum number of user directories reached.\n");
}

void createFile(const char* username, const char* filename) {
	int i,j;
    for (i = 0; i < MAX_USERS; i++) {
        if (userDirectories[i].inUse && strcmp(userDirectories[i].name, username) == 0) {
            for (j = 0; j < MAX_FILES; j++) {
                if (!userDirectories[i].files[j].inUse) {
                    strncpy(userDirectories[i].files[j].name, filename, FILENAME_LENGTH);
                    userDirectories[i].files[j].inUse = 1;
                    printf("File '%s' created in directory '%s' successfully.\n", filename, username);
                    return;
                }
            }
            printf("Error: User directory '%s' is full.\n", username);
            return;
        }
    }
    printf("Error: User directory '%s' not found.\n", username);
}

void listFiles(const char* username) {
	int i,j;
    for (i = 0; i < MAX_USERS; i++) {
        if (userDirectories[i].inUse && strcmp(userDirectories[i].name, username) == 0) {
            printf("Files in directory '%s':\n", username);
            for (j = 0; j < MAX_FILES; j++) {
                if (userDirectories[i].files[j].inUse) {
                    printf("%s\n", userDirectories[i].files[j].name);
                }
            }
            return;
        }
    }
    printf("Error: User directory '%s' not found.\n", username);
}

void deleteFile(const char* username, const char* filename) {
	int i,j;
    for (i = 0; i < MAX_USERS; i++) {
        if (userDirectories[i].inUse && strcmp(userDirectories[i].name, username) == 0) {
            for (j = 0; j < MAX_FILES; j++) {
                if (userDirectories[i].files[j].inUse && strcmp(userDirectories[i].files[j].name, filename) == 0) {
                    userDirectories[i].files[j].inUse = 0;
                    printf("File '%s' deleted from directory '%s' successfully.\n", filename, username);
                    return;
                }
            }
            printf("Error: File '%s' not found in directory '%s'.\n", filename, username);
            return;
        }
    }
    printf("Error: User directory '%s' not found.\n", username);
}

int main() {
    char command[FILENAME_LENGTH];
    char username[USERNAME_LENGTH];
    char filename[FILENAME_LENGTH];

    initializeDirectories();

    while (1) {
        printf("\nEnter command (createuser, createfile, listfiles, deletefile, exit): ");
        scanf("%s", command);

        if (strcmp(command, "createuser") == 0) {
            printf("Enter username: ");
            scanf("%s", username);
            createUserDirectory(username);
        } else if (strcmp(command, "createfile") == 0) {
            printf("Enter username: ");
            scanf("%s", username);
            printf("Enter filename: ");
            scanf("%s", filename);
            createFile(username, filename);
        } else if (strcmp(command, "listfiles") == 0) {
            printf("Enter username: ");
            scanf("%s", username);
            listFiles(username);
        } else if (strcmp(command, "deletefile") == 0) {
            printf("Enter username: ");
            scanf("%s", username);
            printf("Enter filename: ");
            scanf("%s", filename);
            deleteFile(username, filename);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Invalid command. Please try again.\n");
        }
    }

    return 0;
}

