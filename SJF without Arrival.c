#include <stdio.h>

int main() {
    int n, i, j, time = 0, smallest;
    int burstTime[20], waitingTime[20], turnAroundTime[20];
    float totalWaitingTime = 0, totalTurnAroundTime = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input burst time for each process
    printf("Enter burst times:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d burst time: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    // Sort burst times in ascending order (SJN)
    for (i = 0; i < n - 1; i++) {
        smallest = i;
        for (j = i + 1; j < n; j++) {
            if (burstTime[j] < burstTime[smallest]) {
                smallest = j;
            }
        }
        // Swap burst times
        int temp = burstTime[i];
        burstTime[i] = burstTime[smallest];
        burstTime[smallest] = temp;
    }

    // Calculate waiting time and turn-around time
    waitingTime[0] = 0; // First process has no waiting time
    for (i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
    }

    for (i = 0; i < n; i++) {
        turnAroundTime[i] = waitingTime[i] + burstTime[i];
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
    }

    // Display process information
    printf("\nProcess\tBurst Time\tWaiting Time\tTurn-Around Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], waitingTime[i], turnAroundTime[i]);
    }

    // Display average waiting time and turn-around time
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turn-Around Time: %.2f\n", totalTurnAroundTime / n);

    return 0;
}

