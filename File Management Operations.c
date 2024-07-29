#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }
    printf("File '%s' created successfully.\n", filename);
    fclose(file);
}

void writeFile(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", content);
    printf("Content written to file '%s' successfully.\n", filename);
    fclose(file);
}

void readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    printf("Reading from file '%s':\n", filename);
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}

void deleteFile(const char *filename) {
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Failed to delete file");
    }
}

void copyFile(const char *source, const char *destination) {
    FILE *srcFile = fopen(source, "r");
    if (srcFile == NULL) {
        perror("Failed to open source file");
        exit(EXIT_FAILURE);
    }
    FILE *destFile = fopen(destination, "w");
    if (destFile == NULL) {
        perror("Failed to open destination file");
        fclose(srcFile);
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
        fwrite(buffer, 1, bytes, destFile);
    }
    printf("File copied from '%s' to '%s' successfully.\n", source, destination);
    fclose(srcFile);
    fclose(destFile);
}

void moveFile(const char *source, const char *destination) {
    if (rename(source, destination) == 0) {
        printf("File moved from '%s' to '%s' successfully.\n", source, destination);
    } else {
        perror("Failed to move file");
    }
}

int main() {
    const char *filename = "example.txt";
    const char *copyFilename = "copy_example.txt";
    const char *moveFilename = "moved_example.txt";

    // Create a file
    createFile(filename);

    // Write to the file
    writeFile(filename, "Hello, this is a test file.\nThis file contains sample text.");

    // Read from the file
    readFile(filename);

    // Copy the file
    copyFile(filename, copyFilename);

    // Move the file
    moveFile(copyFilename, moveFilename);

    // Read from the moved file
    readFile(moveFilename);

    // Delete the original and moved files
    deleteFile(filename);
    deleteFile(moveFilename);

    return 0;
}

