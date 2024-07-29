#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

void demo_fcntl(const char *filename) {
    int fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Set a new file descriptor flag (FD_CLOEXEC)
    int flags = fcntl(fd, F_GETFD);
    if (flags == -1) {
        perror("fcntl");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) == -1) {
        perror("fcntl");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("File descriptor flags set successfully.\n");
    close(fd);
}

void demo_lseek(const char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Move the file offset to 10 bytes from the beginning
    off_t offset = lseek(fd, 10, SEEK_SET);
    if (offset == -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("File offset moved to: %ld\n", (long)offset);
    close(fd);
}

void demo_stat(const char *filename) {
    struct stat statbuf;

    if (stat(filename, &statbuf) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("File: %s\n", filename);
    printf("Size: %lld bytes\n", (long long)statbuf.st_size);
    printf("Permissions: %o\n", statbuf.st_mode & 0777);
    printf("Last modified: %lld\n", (long long)statbuf.st_mtime);
}

void demo_opendir_readdir(const char *dirpath) {
    DIR *dir = opendir(dirpath);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Entry: %s\n", entry->d_name);
    }

    closedir(dir);
}

int main() {
    const char *filename = "example.txt";
    const char *dirpath = ".";

    // Create and write to the file for demo purposes
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    const char *text = "This is a test file.\n";
    write(fd, text, strlen(text));
    close(fd);

    printf("Demonstrating fcntl...\n");
    demo_fcntl(filename);

    printf("\nDemonstrating lseek...\n");
    demo_lseek(filename);

    printf("\nDemonstrating stat...\n");
    demo_stat(filename);

    printf("\nDemonstrating opendir and readdir...\n");
    demo_opendir_readdir(dirpath);

    return 0;
}

