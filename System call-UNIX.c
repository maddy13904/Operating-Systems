#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main() {
    int fd;
    ssize_t bytesRead, bytesWritten;
    char buffer[BUFFER_SIZE];

    // Open a file for reading and writing
    fd = open("example.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Write some data to the file
    const char *text = "Hello, UNIX system calls!\n";
    bytesWritten = write(fd, text, sizeof(char) * strlen(text));
    if (bytesWritten == -1) {
        perror("Failed to write to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Move the file pointer to the beginning of the file
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Failed to seek in file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Read the data back from the file
    bytesRead = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytesRead == -1) {
        perror("Failed to read from file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytesRead] = '\0'; // Null-terminate the string

    // Print the read data
    printf("Read from file: %s", buffer);

    // Close the file
    if (close(fd) == -1) {
        perror("Failed to close file");
        exit(EXIT_FAILURE);
    }

    return 0;
}

