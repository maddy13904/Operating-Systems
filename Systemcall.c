#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) 
{
    int sourceFile, destFile;
    ssize_t bytesRead, bytesWritten;
    char buffer[BUFFER_SIZE];

    if (argc != 3) 
	{
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the source file
    sourceFile = open(argv[1], O_RDONLY);
    if (sourceFile < 0) 
	{
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open/Create the destination file
    destFile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (destFile < 0) 
	{
        perror("Error opening/creating destination file");
        close(sourceFile);
        exit(EXIT_FAILURE);
    }

    // Read from source and write to destination
    while ((bytesRead = read(sourceFile, buffer, BUFFER_SIZE)) > 0) 
	{
        bytesWritten = write(destFile, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Error writing to destination file");
            close(sourceFile);
            close(destFile);
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRead < 0) 
	{
        perror("Error reading from source file");
    }

    // Close the files
    close(sourceFile);
    close(destFile);

    printf("File copied successfully.\n");

    return 0;
}
