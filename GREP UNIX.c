#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void grep(const char *filename, const char *pattern) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        if (strstr(line, pattern) != NULL) {
            printf("Line %d: %s", line_number, line);
            found = 1;
        }
    }

    if (!found) {
        printf("No lines matching pattern '%s' found.\n", pattern);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <filename> <pattern>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    const char *pattern = argv[2];

    grep(filename, pattern);

    return 0;
}

