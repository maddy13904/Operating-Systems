#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void sortRequests(int requests[], int n) {
	int i,j;
    // Simple bubble sort to sort the requests array
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (requests[j] > requests[j+1]) {
                int temp = requests[j];
                requests[j] = requests[j+1];
                requests[j+1] = temp;
            }
        }
    }
}

void cscanDiskScheduling(int requests[], int n, int head, int disk_size) {
	int i;
    int seek_sequence[MAX_REQUESTS];
    int seek_count = 0;
    int total_seek_time = 0;
    int distance, current_track;

    // Sort the request array
    sortRequests(requests, n);

    int position = 0;
    while (position < n && requests[position] < head) {
        position++;
    }

    int index = 0;

    // Move towards the end of the disk
    for (i = position; i < n; i++) {
        seek_sequence[index++] = requests[i];
        distance = abs(requests[i] - head);
        total_seek_time += distance;
        head = requests[i];
    }

    // Move to the end of the disk
    if (position < n) {
        seek_sequence[index++] = disk_size - 1;
        total_seek_time += abs((disk_size - 1) - head);
        head = 0;
        total_seek_time += disk_size - 1; // Move to the start of the disk
    }

    // Move from the start of the disk
    for (i = 0; i < position; i++) {
        seek_sequence[index++] = requests[i];
        distance = abs(requests[i] - head);
        total_seek_time += distance;
        head = requests[i];
    }

    printf("Seek Sequence is:\n");
    for (i = 0; i < index; i++) {
        printf("%d ", seek_sequence[i]);
    }
    printf("\nTotal Seek Time: %d\n", total_seek_time);
    printf("Average Seek Time: %.2f\n", (float)total_seek_time / n);
}

int main() {
    int n,i; // Number of requests
    int requests[MAX_REQUESTS]; // Array to store requests
    int head; // Initial head position
    int disk_size; // Disk size

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the requests (disk positions):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the disk size: ");
    scanf("%d", &disk_size);

    cscanDiskScheduling(requests, n, head, disk_size);

    return 0;
}

