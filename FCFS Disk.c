#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Function to simulate FCFS Disk Scheduling
void fcfsDiskScheduling(int requests[], int n, int head) {
	int i;
    int seek_sequence[MAX_REQUESTS];
    int seek_count = 0;
    int total_seek_time = 0;
    
    // Copy requests to seek sequence
    for (i = 0; i < n; i++) {
        seek_sequence[i] = requests[i];
    }
    
    printf("Seek Sequence is:\n");
    
    // Calculate total seek time
    for (i = 0; i < n; i++) {
        printf("%d ", seek_sequence[i]);
        total_seek_time += abs(head - seek_sequence[i]);
        head = seek_sequence[i];
    }
    
    printf("\nTotal Seek Time: %d\n", total_seek_time);
    printf("Average Seek Time: %.2f\n", (float)total_seek_time / n);
}

int main() {
    int n,i; // Number of requests
    int requests[MAX_REQUESTS]; // Array to store requests
    int head; // Initial head position
    
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    
    printf("Enter the requests (disk positions):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    
    fcfsDiskScheduling(requests, n, head);
    
    return 0;
}

