#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

// Function to format and print the file details
void printFileDetails(const char *path, const char *filename) {
    char fullpath[1024];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, filename);

    struct stat fileStat;
    if (stat(fullpath, &fileStat) == -1) {
        perror("stat");
        return;
    }

    // File type
    char fileType = S_ISDIR(fileStat.st_mode) ? 'd' : '-';

    // File permissions
    char permissions[10];
    permissions[0] = fileType;
    permissions[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
    permissions[10] = '\0';

    // Print file details
    printf("%s %10ld %s %s\n", permissions, fileStat.st_size, ctime(&fileStat.st_mtime), filename);
}

// Function to list directory contents
void listDirectory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printFileDetails(path, entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *path = "."; // Default to current directory

    if (argc > 1) {
        path = argv[1];
    }

    listDirectory(path);

    return 0;
}

